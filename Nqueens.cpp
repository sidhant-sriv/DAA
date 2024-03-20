#include <iostream>
#include <vector>

using namespace std;

/**
 * Checks if it is safe to place a queen at the given position on the chessboard.
 * 
 * @param board The chessboard represented as a 2D vector.
 * @param row The row index of the position to check.
 * @param col The column index of the position to check.
 * @param N The size of the chessboard.
 * @return True if it is safe to place a queen at the given position, false otherwise.
 */
bool isSafe(vector<vector<int>> &board, int row, int col, int N)
{
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueensUtil(vector<vector<int>> &board, int col, int N)
{
    // If all queens are placed, return true
    if (col >= N)
        return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++)
    {
        // Check if the queen can be placed on board[i][col]
        if (isSafe(board, i, col, N))
        {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // Recur to place rest of the queens
            if (solveNQueensUtil(board, col + 1, N))
                return true;

            board[i][col] = 0; //
        }
    }

    return false;
}

bool solveNQueens(int N)
{
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueensUtil(board, 0, N))
    {
        cout << "Solution does not exist";
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }

    return true;
}

int main()
{
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    solveNQueens(N);
    return 0;
}
