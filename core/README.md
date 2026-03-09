BRIEF SUMMARY OF WORK ON CELL AND BOARD CLASSES

1. WHAT WAS DONE
----------------

Two key classes for the "Minesweeper" game were developed:

Cell Class:
- Represents a single cell on the game board
- Stores state (closed/opened/flagged)
- Stores information about mine presence and number of adjacent mines
- Implements methods for opening, flag toggling, and reset

Board Class:
- Manages the game board
- Creates and stores a grid of cells using std::unique_ptr
- Provides safe access to cells via std::optional
- Implements cell opening logic and empty region expansion
- Checks win/loss conditions

2. DIFFICULTIES AND SOLUTIONS
-----------------------------

Difficulty: Memory management for cells
Solution: Used std::vector of std::unique_ptr<Cell>
         (automatic memory deallocation, RAII)

Difficulty: Safe access to cells by coordinates
Solution: getCell() method returns std::optional
         (explicitly shows possibility of cell absence)

Difficulty: Recursive opening of empty regions
Solution: Replaced recursion with iterative stack-based algorithm
         (safer, no stack overflow risk)

Difficulty: Handling invalid parameters
Solution: Board constructor throws BoardException
         (for invalid board dimensions)

Difficulty: Modern C++ style
Solution: Used constexpr for simple methods
         enum class for type safety
         noexcept where appropriate

3. COMPLIANCE WITH TECHNICAL REQUIREMENTS
----------------------------------------

 C++23 - code uses modern standards
 Two classes - Cell and Board fully implemented
 RAII - smart pointers manage memory
 std::unique_ptr - storing polymorphic objects
 std::optional - safe value return
 Exceptions - BoardException for errors
 constexpr - isValidCoord methods and getters
