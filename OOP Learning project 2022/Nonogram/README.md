# NONOGRAM

## Discription
During each round, the game interface displays a menu asking the user to select an action:
  - p (print) - print the current board
  - m (modify) - user set/unset (color/leave blank) a certain cell
  - c (check) - check if the current board is a valid solution
  - s (solve) - invoke Nonogram solver to solve the game
  - q (quit) - quit the game and ends the program  
Solver  
USING DFS TO SOLVE NONOGRAM PUZZLE  

## TASK
### Part I: Initialize the board.
- Task 1: This function asks user to input the board size and constraints, check if the constraints are valid, 
store the information in global variables and finally initialize the board.  
- Task 2: This function prints the board and the constraints for each row and column.
### Part II: User play on board.
- Task 3: This function will be called when user choose to set/unset a cell.
          It will:  
              1. Ask user to input which cell he/she wants to modify. The user will need to first enter the column index, followed
                 by a space, and then the row index. For example, "A 2".  
              2. Check if the user input is a valid cell  
              3. Set / unset (color / leave blank) the cell. If the cell was set before, then unset it, and vice versa.
- Task 4: This function will be called after user finish filling the whole board. Check whether his/her solution is correct, i.e., satisfy all constraints.  
### Part III: A nonogram solver.
- Task 5: This function coverts a position vector of a row into a real row.  
- Task 6: This function checks if the given block on given row can be shifted to the right for one cell.  
- Task 7: This function gets all valid permutations for a row, and store all results in global variables row_perms and num_row_perms.  
- Task 8: This function checks if current state is valid, after we finish filling num_complete_rows rows. For example, if num_complete_rows = 2, it will only check
if the first two rows (with index 0 and 1) do not break column constraints.
- Task 9: This function will solve the board, and store the solution into global variable board directly.You may assume there are only one solution for the board given.
