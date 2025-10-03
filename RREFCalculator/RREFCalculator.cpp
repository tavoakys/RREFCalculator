#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

const double epsilon = 1e-9;

void outputMatrix(const vector<vector<double>>& matrix) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();
    cout << fixed << setprecision(6);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double val = (fabs(matrix[i][j]) < epsilon) ? 0 : matrix[i][j];
            cout << setw(12) << val << " ";
        }
        cout << "\n";
    }
}

int main() {


    int rows, cols;
    cout << "Enter number of rows and columns: ";
    if (!(cin >> rows >> cols) || rows <= 0 || cols <= 0) {
        cout << "Invalid matrix size.\n";
        return 0;
    }

    vector<vector<double>> matrix(rows, vector<double>(cols));
    cout << "Enter the matrix row by row (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    auto start = chrono::high_resolution_clock::now();

    int r = 0; 
    for (int c = 0; c < cols && r < rows; c++) { 
        int pivot = r;
        for (int i = r; i < rows; i++) {
            if (fabs(matrix[i][c]) > fabs(matrix[pivot][c])) {
                pivot = i;
            }
        }

        if (fabs(matrix[pivot][c]) < epsilon) {
            continue;
        }

        if (pivot != r) {
            for (int j = 0; j < cols; j++) {
                double temp = matrix[r][j];
                matrix[r][j] = matrix[pivot][j];
                matrix[pivot][j] = temp;
            }
        }

        double pivotVal = matrix[r][c];
        for (int j = 0; j < cols; j++) {
            matrix[r][j] /= pivotVal;
        }

        for (int i = 0; i < rows; i++) {
            if (i == r) {
                continue;
            }
            double multiple = matrix[i][c];
            if (fabs(multiple) > epsilon) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] -= multiple * matrix[r][j];
                }
            }
        }

        r++;
    }

    cout << "\nRREF:\n";
    outputMatrix(matrix);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed = end - start;

	cout << "\nTime elapsed: " << timeElapsed.count() << " ms\n";

    return 0;
}
