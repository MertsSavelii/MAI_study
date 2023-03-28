#include <bits/stdc++.h>
using namespace std;

vector<vector<double>> Matrix_Multiplication(const vector<vector<double>>& A,
                                             const vector<vector<double>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    vector<vector<double>> C(n, vector<double>(m, 0.0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}