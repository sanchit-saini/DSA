/*
 Problem Statement: Given a matrix if an element in the matrix is 0 then you
 will have to set its entire column and row to 0 and then return the matrix.
 */

#include <iostream>
#include <vector>

using namespace std;


auto brute(vector<vector<int>> matrix) {
    int row = matrix.size();
    int col = matrix[0].size();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == 0) {

                // set row
                for (int x = 0; x < col; ++x)
                    if (matrix[i][x] != 0)
                        matrix[i][x] = -1;

                // set column
                for (int x = 0; x < row; ++x)
                    if (matrix[x][j] != 0)
                        matrix[x][j] = -1;
            }
        }
    }


    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == -1)
                matrix[i][j] = 0;
        }
    }

    return matrix;
}


auto better(vector<vector<int>> matrix) {
    int mrow = matrix.size();
    int mcol = matrix[0].size();

    // use extra array to track state of present zero
    vector<int> row(mrow, -1), col(mcol, -1);


    for (int i = 0; i < mrow; ++i) {
        for (int j = 0; j < mcol; ++j) {
            if (matrix[i][j] == 0)
                row[i] = col[j] = 0;
        }
    }

    for (int i = 0; i < mrow; ++i) {
        for (int j = 0; j < mcol; ++j) {
            if (row[i] == 0 || col[j] == 0)
                matrix[i][j] = 0;
        }
    }

    return matrix;
}


auto optimal(vector<vector<int>> matrix) {
    int row = matrix.size();
    int col = matrix[0].size();

    // for tracking state of first column
    bool flag = false;

    for (int i = 0; i < row; ++i) {

        if (matrix[i][0] == 0)
            flag = true;

        for (int j = 1; j < col; ++j) {
            if (matrix[i][j] == 0)
                matrix[i][0] = matrix[0][j] = 0;
        }
    }

    for (int i = row - 1; i >= 0; i--) {
        for (int j = col - 1; j >= 1; j--) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        }

        if (flag)
            matrix[i][0] = 0;
    }

    return matrix;
}


void print(vector<vector<int>> &m) {
    for (auto row:m) {
        for (auto element: row)
            cout << element << " ";
        cout << "\n";
    }
    cout << "\n";
}


int main() {

    vector<vector<int>> matrix = {
        {0, 1, 2, 0},
        {3, 4, 5, 2},
        {1, 3, 1, 5}
    };

    auto bm = brute(matrix);
    print(bm);

    auto btm = better(matrix);
    print(btm);

    auto om = optimal(matrix);
    print(om);

    return 0;
}
