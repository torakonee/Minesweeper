#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

#include "board.hpp"
#include "Config/Config.hpp"
#include "ConfigAnalysis.hpp"
#include "CoordinateAnalysis.hpp"
#include "Visual/Render.hpp"
#include "Status.hpp"

namespace ms {

    namespace {

        int mineCount(const std::string& diff) {
            static const std::unordered_map<std::string, int> minesDiff{
                {"easy", 10},
                {"Easy", 10},
                {"normal", 40},
                {"Normal", 40},
                {"hard", 99},
                {"Hard", 99}
            };

            auto i = minesDiff.find(diff);
            if (i != minesDiff.end()) {
                return i->second;
            }
            return 0;
        }

        bool DiffCon(Config& conf) {

            ConfigAnalysis pass;

            std::string inp;

            std::cout << "Choose difficulty (Easy/Normal/Hard)" << std::endl;

            std::cout << "Enter for default" << std::endl;

            while (std::getline(std::cin, inp)) {

                if (inp.empty()) {
                    return true;
                }

                bool wd = false;

                InputAnalysis::Input pss = pass.check(inp);

                std::visit(
                    [&](const auto& val) {

                        using T = std::decay_t<decltype(val)>;

                        if constexpr (std::is_same_v<T, InputAnalysis::DifficultyIn>) {
                            switch (val.difficulty) {
                            case InputAnalysis::Difficulty::Easy:
                                conf.setMines(10);
                                wd = true;
                                break;
                            case InputAnalysis::Difficulty::Normal:
                                conf.setMines(40);
                                wd = true;
                                break;
                            case InputAnalysis::Difficulty::Hard:
                                conf.setMines(99);
                                wd = true;
                                break;
                            }
                        }

                    },
                    pss
                );

                if (wd == 1) {
                    return true;
                }

                std::cout << "Invalid difficulty :(" << std::endl << "Try again?";
            }

            return false;
        }

        bool SzCon(Config& conf) {
            ConfigAnalysis pass;
            std::string inp;

            std::cout << "Enter your square board size (Enter for default): ";

            while (std::getline(std::cin, inp)) {
                if (inp.empty()) {
                    return true;
                }

                bool wd = false;

                InputAnalysis::Input pss = pass.check(inp);

                std::visit(
                    [&](const auto& val) {
                        using T = std::decay_t<decltype(val)>;

                        if constexpr (std::is_same_v<T, InputAnalysis::SizeIn>) {
                            conf.setWidth(val.size1);
                            conf.setHeight(val.size1);
                            wd = true;
                        }
                    },
                    pss
                );

                if (wd == 1) {
                    if (conf.getMines() >= conf.getWidth() * conf.getHeight()) {
                        std::cout << "Too many mines for this board size :(" << std::endl << "Try again?" << std::endl;
                        continue;
                    }
                    return true;
                }

                std::cout << "Invalid size :(" << std::endl << "Try again?";
            }

            return false;
        }

    }

}

int main() {

    using namespace ms;

    auto conf = std::make_shared<Config>();

    if (!DiffCon(*conf)) {
        return 0;
    }

    if (!SzCon(*conf)) {
        return 0;
    }

    Board board(conf->getWidth(), conf->getHeight(), conf->getMines());
    Render render;
    Status status(conf);
    CoordinateAnalysis movep;
    std::string inp;
    while (true) {
        render.drawField(board);
        status.print();
        if (board.isGameOver()) {
            status.gameOver();
            render.drawField(board);
            status.print();
            break;
        }
        if (board.isWin()) {
            status.victory();
            render.drawField(board);
            status.print();
            break;
        }
        std::cout << "Your move (example: B3 or f B3): ";
        if (!std::getline(std::cin, inp)) {
            break;
        }
        InputAnalysis::Input psm = movep.check(inp);
        std::visit(
            [&](const auto& pss) {
                using T = std::decay_t<decltype(pss)>;
                if constexpr (std::is_same_v<T, InputAnalysis::CoordinateIn>) {
                    if (pss.isFlag) {
                        board.toggleFlag(pss.x, pss.y);
                        status.newFlag();
                    }
                    else {
                        board.openCell(pss.x, pss.y);
                        status.plusMove();
                    }
                }
                else {
                    std::cout << "Invalid input :(" << std::endl;
                }
            }, psm
        );
    }
}
