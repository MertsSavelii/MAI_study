#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void Read_Tridiagonal_Matrix_From_Normal_Matrix 
                           (vector<vector <double>> A,
                            vector <double> B,
                            vector <double> &a, 
                            vector <double> &b, 
                            vector <double> &c,
                            vector <double> &d,
                            int n){
    d = B;
    a[0] = 0, b[0] = A[0][0], c[0] = A[0][1];
    for(int i = 1; i < n-1; i++){
        a[i] = A[i][i-1];
        b[i] = A[i][i];
        c[i] = A[i][i+1];
    }
    a[n-1] = A[n-1][n-2], b[n-1] = A[n-1][n-1], c[n-1] = 0;
}

void Read_Tridiagonal_Matrix(vector <double> &a, 
                             vector <double> &b, 
                             vector <double> &c,
                             vector <double> &d,
                             int n){
    cin >> b[0] >> c[0] >> d[0];
    for(int i = 1; i < n-1; i++)
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    cin >> a[n-1] >> b[n-1] >> d[n-1];
}

void Direct_Passage (vector <double> a, 
                     vector <double> b, 
                     vector <double> c,
                     vector <double> d, 
                     vector <double> &P, 
                     vector <double> &Q,
                     int n){
    for(int i = 0; i < n; i++){
        P[i] = -c[i] / (b[i] + a[i]*P[i-1]);
        Q[i] = (d[i] - a[i]*Q[i-1]) / (b[i] + a[i]*P[i-1]);
    }
}

void Reverse_Passage (vector <double> &x,
                      vector <double> P,
                      vector <double> Q,
                      int n){
    x[n-1]= Q[n-1];
    for(int i = n-2; i >= 0; i--)
        x[i] = P[i]*x[i+1] + Q[i];
}

void Solve_With_Run_Through(vector <vector <double>> &A,
			                vector <double> &B,
                            vector <double> &x,
                            int n){
    vector <double> a(n, 0), b(n, 0), c(n, 0),
                    d(n, 0), P(n, 0), Q(n, 0);
    Read_Tridiagonal_Matrix_From_Normal_Matrix(A, B, a, b, c, d, n);
    Direct_Passage(a, b, c, d, P, Q, n);
    Reverse_Passage(x, P, Q, n);
}