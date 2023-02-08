#include <iostream>
using namespace std;

// some constraints for board
const int MAX_ROW = 15, MAX_COL = 15;
const int MAX_CONSTRAINT_NUM = 15; // constraint cannot exceed MAX_ROW/MAX_COL

// board and its size
int num_rows = 0, num_cols = 0;
char board[MAX_ROW][MAX_COL] = {{0}};

// constraints and their sizes
int num_row_constraints[MAX_ROW] = {0}, num_col_constraints[MAX_COL] = {0};
int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM] = {{0}};
int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};

// Part 1: Initialize the board

/*
 * Task 1
 * This function reads the board size and constraints from user input,
 * store the information in global variables and init the board.
 */
void get_input_board()
{

    cout << "Enter the number of rows: ";
    cin >> num_rows;
    cout << "Enter the number of columns: ";
    cin >> num_cols;

    // set board
    for (int i = 0; i < num_rows; ++i)
    {
        for (int k = 0; k < num_cols; ++k)
            board[i][k] = '.';
    }

    // row constraints
    for (int i = 0; i < num_rows; ++i)
    {
        cout << "Enter the number of constraints for row " << i << " (end with -1): ";
        int m[MAX_CONSTRAINT_NUM] = {};
        for (int k = 0; k < MAX_CONSTRAINT_NUM; ++k)
        {
            cin >> m[k];
            if (m[k] == -1)
            {
                num_row_constraints[i] = k;
                break;
            }
        }
        int constraint = 0;
        for (int k = 0; m[k] != -1; ++k)
            constraint += m[k];
        if (constraint + num_row_constraints[i] - 1 > num_rows)
        {
            cout << "Invalid row constraint, please try again." << endl;
            i--;
        }
        else
        {
            for (int k = 0; k < num_row_constraints[i]; ++k)
            {
                row_constraints[i][k] = m[k];
            }
        }
    }

    // column constraint
    for (int i = 0; i < num_cols; ++i)
    {
        cout << "Enter the number of constraints for column " << i << " (end with -1): ";
        int m[MAX_CONSTRAINT_NUM] = {};
        for (int k = 0; k < MAX_CONSTRAINT_NUM; ++k)
        {
            cin >> m[k];
            if (m[k] == -1)
            {
                num_col_constraints[i] = k;
                break;
            }
        }
        int constraint = 0;
        for (int k = 0; m[k] != -1; ++k)
        {
            constraint += m[k];
        }
        if (constraint + num_col_constraints[i] - 1 > num_cols)
        {
            cout << "Invalid column constraint, please try again." << endl;
            i--;
        }
        else
        {
            for (int k = 0; k < num_col_constraints[i]; ++k)
            {
                col_constraints[i][k] = m[k];
            }
        }
    }
}

/*
 * Task 2  
 *
 * This function prints the board and the constraints for each row and column.
 * Constraints  printed on the bottom of each column and on the left of each row.
 * 
 */
void print_board()
{
    int max_row_constraint = 0;
    for (int i = 0; i < MAX_ROW; ++i)
    {
        if (num_row_constraints[i] > max_row_constraint)
            max_row_constraint = num_row_constraints[i];
    }
    int max_col_constraint = 0;
    for (int i = 0; i < MAX_COL; ++i)
    {
        if (num_col_constraints[i] > max_col_constraint)
            max_col_constraint = num_col_constraints[i];
    }

    // print A,B,...
    for (int i = 0; i < max_row_constraint * 2 + 4; ++i)
        cout << ' ';
    for (int i = 0; i < num_cols; ++i)
        cout << ' ' << char(i + 65);
    cout << '\n';

    // print row constraint
    for (int i = 0; i < num_rows; ++i)
    {
        for (int k = 0; k < max_row_constraint - num_row_constraints[i]; ++k)
            cout << "  ";
        for (int k = 0; row_constraints[i][k] != 0; ++k)
        {
            cout << row_constraints[i][k] << ' ';
        }
        cout << "| ";
        if (i < 10)
            cout << ' ';
        cout << i;
        for (int k = 0; k < num_cols; ++k)
        {
            cout << ' ' << board[i][k];
        }
        cout << '\n';
    }

    // print column constraint
    for (int i = 0; i < max_col_constraint; ++i)
    {
        for (int i = 0; i < max_row_constraint * 2 + 4; ++i)
            cout << ' ';
        for (int k = 0; k < num_cols; ++k)
        {
            if (col_constraints[k][i] != 0)
            {
                cout << ' ' << col_constraints[k][i];
            }
            else
                cout << "  ";
        }
        cout << '\n';
    }
}

//Part 2: User play on board   


/**
 * Task 3  
 * This function will be called when user choose to set/unset a cell.
 * 1. Ask user to input which cell he/she wants to modify
 * 2. If the user input is a valid cell(i.e., it is within the board)
 *    If invalid, keep asking the user to input.
 * 3. Set/unset the cell
 * 4. Print the new board
 */
void user_operate_board()
{

    char ope_col;
    int ope_row_num;
    int ope_col_num;

    while (true)
    {

        cout << "Enter the cell you want to modify (e.g. A 2): ";
        cin >> ope_col >> ope_row_num;

        ope_col_num = int(ope_col) - 65;

        if ((ope_row_num > num_rows - 1) || (ope_row_num < 0) || (ope_col_num > num_cols - 1) || (ope_col_num < 0))
        {
            cout << "Invalid row or column. Try again." << endl;
        }
        else
        {
            if (board[ope_row_num][ope_col_num] == '.')
                board[ope_row_num][ope_col_num] = 'X';
            else
                board[ope_row_num][ope_col_num] = '.';
            break;
        }
    }
}

/**
 * Task 4  
 * This function will be called after user finish filling the whole board.
 * check whether his/her solution is correct,
 * i.e., follow all constraints.
 * Return true if his/her solution is correct; false otherwise.
 */
bool check_whole_board_valid()
{

    for (int i = 0; i < num_cols; ++i)
    {
        int col_constraints_compare[MAX_CONSTRAINT_NUM] = {};
        int col_constraints_compare_num = 0;
        for (int k = 0; k < num_rows; ++k)
        {
            int temp = 0;
            while ((board[k][i] == 'X') && (k < num_rows))
            {
                temp++;
                k++;
            }
            if (temp != 0)
            {
                col_constraints_compare[col_constraints_compare_num] = temp;
                ++col_constraints_compare_num;
            }
        }

        for (int j = 0; j < MAX_CONSTRAINT_NUM; ++j)
        {
            if (col_constraints[i][j] != col_constraints_compare[j])
                return false;
        }
    }

    for (int i = 0; i < num_rows; ++i)
    {
        int row_constraints_compare[MAX_CONSTRAINT_NUM] = {};
        int row_constraints_compare_num = 0;

        for (int k = 0; k < num_cols; ++k)
        {
            int temp = 0;
            while ((board[i][k] == 'X') && (k < num_cols))
            {
                temp++;
                k++;
            }
            if (temp != 0)
            {
                row_constraints_compare[row_constraints_compare_num] = temp;
                ++row_constraints_compare_num;
            }
        }

        for (int j = 0; j < MAX_CONSTRAINT_NUM; ++j)
        {
            if (row_constraints[i][j] != row_constraints_compare[j])
                return false;
        }
    }

    return true;
}

// Part 3: A nonogram solver 

/**
 * Task 5 
 *
 * This function coverts a position vector of a row into a real row.
 */
void positions_to_row(int row_idx, const int positions[], int num_pos, char result_row[])
{

    for (int i = 0; i < num_pos; ++i)
    {
        for (int k = 0; k < row_constraints[row_idx][i]; ++k)
        {
            result_row[positions[i] + k] = 'X';
        }
    }
    for (int i = 0; i < num_cols; ++i)
    {
        if (result_row[i] != 'X')
            result_row[i] = '.';
    }
}

/**
 * Task 6  
 *
 * This function checks if the given block on given row can be shifted right for one cell.
 * For example, if the position vector is {0, 4, 6}, num_col = 8
 * then the row is: [X X . . X . X .], and there are 3 blocks
 * then block_can_shift(row_idx, 0, {0, 4, 6}) = true,
 *      block_can_shift(row_idx, 1, {0, 4, 6}) = false, since it will hit 2nd block after shift
 *      block_can_shift(row_idx, 2, {0, 4, 6}) = true.
 */
bool block_can_shift(int row_idx, int block_idx, const int positions[], int num_pos)
{

    if (block_idx == num_pos - 1)
    {
        if (positions[block_idx] + row_constraints[row_idx][block_idx] < num_cols)
            return true;
    }
    else
    {
        if (positions[block_idx] + row_constraints[row_idx][block_idx] + 1 < positions[block_idx + 1])
            return true;
    }
    return false;
}

// this array stores all valid permutations for each row
// it's expected that num of permutations for each row should not exceed 2^(num_cols)
const int MAX_PERM = 1 << MAX_COL; // A way to calculate 2^(num_cols)
char row_perms[MAX_ROW][MAX_PERM][MAX_COL];
// this array stores num of permutations for each row
int num_row_perms[MAX_ROW] = {0};

void rec(int i, int max, int *num_ar, const int row_idx, const int num_pos, const int *perms)
{

    if (i > 0)
    {
        num_ar[i - 1] = max;
        for (int k = 0; k <= num_ar[i - 1]; ++k)
        {
            rec(i - 1, k, num_ar, row_idx, num_pos, perms);
        }
    }
    else if (max == 0)
    {
        char result_row[MAX_COL] = {};
        int positions[MAX_COL] = {};
        for (int s = 0; s < num_pos; ++s)
        {
            positions[s] = perms[s] + num_ar[s];
        }

        positions_to_row(row_idx, positions, num_pos, result_row);
        for (int g = 0; g < num_cols; ++g)
        {
            row_perms[row_idx][num_row_perms[row_idx]][g] = result_row[g];
        }

        num_row_perms[row_idx]++;
    }
}

/**
 * Task 7  
 *
 * This function gets all valid permutations for a row,
 * and store all results in global variables 'row_perms' and 'num_row_perms'.
 *
 *
 */
void get_row_perms(int row_idx)
{

    // get first permutation
    int perms[MAX_CONSTRAINT_NUM];
    int num_pos = 0;
    for (int i = 0, k = 0; row_constraints[row_idx][i] != 0; ++i)
    {
        perms[i] = i + k;
        k += row_constraints[row_idx][i];
        num_pos++;
    }

    char result_row[MAX_COL] = {};
    positions_to_row(row_idx, perms, num_pos, result_row);
    for (int g = 0; g < num_cols; ++g)
    {
        row_perms[row_idx][0][g] = result_row[g];
    }

    num_row_perms[row_idx]++;
    if (num_pos == 0)
    {
        return;
    }

    // recursion

    int shift_max = num_cols - perms[num_pos - 1] - row_constraints[row_idx][num_pos - 1];
    int shift_array[MAX_CONSTRAINT_NUM] = {};

    for (int k = shift_max; k > 0; --k)
    {
        rec(num_pos, k, shift_array, row_idx, num_pos, perms);
    }
}

/**
 * Task 8 
 *
 * This function checks if current state is valid, after
 * we finish filling 'num_complete_rows' rows.
 *
 * For example, if num_complete_rows = 2, it will only check
 * if the first two rows (with index 0 and 1) do not
 * break column constraints.
 *
 */
bool check_rows_valid(int num_complete_rows)
{

    if (num_complete_rows == num_rows)
    {
        for (int i = 0; i < num_cols; ++i)
        {
            int col_constraints_compare[MAX_CONSTRAINT_NUM] = {};
            int col_constraints_compare_num = 0;
            for (int k = 0; k < num_rows; ++k)
            {
                int temp = 0;
                while ((board[k][i] == 'X') && (k < num_rows))
                {
                    temp++;
                    k++;
                }
                if (temp != 0)
                {
                    col_constraints_compare[col_constraints_compare_num] = temp;
                    ++col_constraints_compare_num;
                }
            }
            for (int j = 0; j < MAX_CONSTRAINT_NUM; ++j)
            {
                if (col_constraints[i][j] != col_constraints_compare[j])
                    return false;
            }
        }
    }
    else
    {
        for (int i = 0; i < num_cols; ++i)
        {
            int col_constraints_compare[MAX_CONSTRAINT_NUM] = {};
            int col_constraints_compare_num = 0;

            for (int k = 0; k < num_complete_rows; ++k)
            {
                int temp = 0;
                while ((board[k][i] == 'X') && (k < num_complete_rows))
                {
                    temp++;
                    k++;
                }
                if (temp != 0)
                {
                    col_constraints_compare[col_constraints_compare_num] = temp;
                    ++col_constraints_compare_num;
                }
            }
            int j = 0;
            for (; j < col_constraints_compare_num - 1; j++)
            {
                if (col_constraints[i][j] != col_constraints_compare[j])
                    return false;
            }
            if (col_constraints_compare_num == 0)
            {
                continue;
            }
            else if (board[num_complete_rows - 1][i] != 'X')
            {
                if (col_constraints[i][j] != col_constraints_compare[j])
                    return false;
            }
            else
            {
                if (col_constraints[i][j] < col_constraints_compare[j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Task 9  
 *
 * This function will solve the board, and store the solution
 * into board[][] directly.
 *
 */

// solve recursion
bool rec_solve(int row_n)
{
    if (num_row_perms[row_n] == 0)
    {
        get_row_perms(row_n);
    }
    if (row_n < num_rows)
    {
        int num_pos = 0;
        for (int i = 0, k = 0; row_constraints[row_n][i] != 0; ++i)
            num_pos++;

        for (int perm_n = 0; perm_n < num_row_perms[row_n]; ++perm_n)
        {
            for (int k = 0; k < num_cols; ++k)
            {
                board[row_n][k] = row_perms[row_n][perm_n][k];
            }

            if (check_rows_valid(row_n + 1))
            {
                if (rec_solve(row_n + 1))
                    return 1;
            }
        }
        return 0;
    }
    else
        return 1;
}

void solve()
{
    rec_solve(0);
}

// main program

int main()
{
    get_input_board();
    print_board();

    while (true)
    {
        cout << "===== Welcome to Nonogram Game =====" << endl;
        cout << "Please enter your choice:" << endl;
        cout << "Enter 'p' to print the current board." << endl;
        cout << "Enter 'm' to modify a cell." << endl;
        cout << "Enter 'c' to check your solution." << endl;
        cout << "Enter 's' to invoke solver." << endl;
        cout << "Enter 'q' to quit." << endl;
        cout << "Your choice: ";
        char input;
        cin >> input;
        if (input == 'p')
        {
            print_board();
        }
        else if (input == 'm')
        {
            user_operate_board();
        }
        else if (input == 'c')
        {
            if (check_whole_board_valid())
            {
                cout << "Congratulations! Your solution is correct!" << endl;
            }
            else
            {
                cout << "Ahh, your solution is incorrect, try again." << endl;
            }
        }
        else if (input == 's')
        {
            cout << "Generating solution:" << endl;
            solve();
            print_board();
        }
        else if (input == 'q')
        {
            cout << "Bye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return 0;
}
