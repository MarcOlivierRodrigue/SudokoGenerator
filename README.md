# SudokoGenerator
The overall goal of this project is to make a Sudoku puzzle generator. There's a few subgoals that I have set for myself:
1. Each board generated needs to have only one solution
2. Use Gtest for unit testing
3. Being able to generate boards of 4x4, 6x6, 9x9, 16x16 and 25x25(this one might take a bit to generate)

- In this project, I make use of different algorithms:
    - Regular Backtrace
    - Backtrace with bitmaps

Sources:
 - Shout out to this paper by Andrew C. Stuart for starting me on the right path: https://www.sudokuwiki.org/Sudoku_Creation_and_Grading.pdf 
 - https://www.geeksforgeeks.org/program-sudoku-generator/
 - https://www.geeksforgeeks.org/sudoku-backtracking-7/