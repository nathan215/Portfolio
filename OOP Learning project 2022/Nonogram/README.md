During each round, the game interface displays a menu asking the user to select an action:
  - p (print) - print the current board
  - m (modify) - user set/unset (color/leave blank) a certain cell
  - c (check) - check if the current board is a valid solution
  - s (solve) - invoke Nonogram solver to solve the game
  - q (quit) - quit the game and ends the program

Solver 
USING DFS TO SOLVE NONOGRAM PUZZLE

- Task 1: This function asks user to input the board size and constraints, check if the constraints are valid, 
store the information in global variables and finally initialize the board.  
- Task 2: This function prints the board and the constraints for each row and column.
- Task 3: This function will be called when user choose to set/unset a cell.
          It will:
              1. Ask user to input which cell he/she wants to modify. The user will need to first enter the column index, followed
                 by a space, and then the row index. For example, "A 2".
              2. Check if the user input is a valid cell
              3. Set / unset (color / leave blank) the cell. If the cell was set before, then unset it, and vice versa.
