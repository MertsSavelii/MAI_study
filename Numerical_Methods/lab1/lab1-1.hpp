#include <bits/stdc++.h>
using namespace std;

const int eps = 10; // точность округления 

void LU_With_Selection_Of_Main_Element(
        vector <vector <double>> &A,
        vector <vector <double>> &L, 
        vector <vector <double>> &U,
        vector <double> &b,
        int n){
    U=A;
    for(int k = 0; k < n; k++){
        for(int i = k; i < n; i++)
            if(abs(A[k][k]) < abs(A[i][k])){
                swap(A[k], A[i]);
                swap(L[k], L[i]);
                swap(U[k], U[i]);
                swap(b[k], b[i]);
            }
        for(int i = k+1; i < n; i++)
            for(int j = 0; j < n; j++){
                if(j == k)
                    L[i][k] = U[i][k]/U[k][k];
                U[i][j] -= U[k][j]*L[i][k];
            }
    }
    for(int i = 0; i < n; i++)
        L[i][i] = 1;
}

void Solve_With_LU (vector <vector <double>> &A,
			        vector <double> &b,
                    vector <double> &x,
                    int n){
    vector <vector<double>> L(n, vector<double> (n)),
                            U(n, vector<double> (n));
    LU_With_Selection_Of_Main_Element(A, L, U, b, n);
    vector <double> y(n);
    double sum;
    for(int i = 0; i < n; i++){
        sum = 0;
        for(int k = 0; k < i; k++){
            sum += L[i][k]*y[k];
        }
        y[i] = b[i] - sum;
    }
    for(int i = n-1; i >= 0 ; i--){
        sum = 0;
        for(int k = i; k < n; k++){
            sum += U[i][k]*x[k];
        }
        x[i] = (y[i] - sum)/U[i][i];
        x[i] = round(x[i]*pow(10, eps))/pow(10, eps);
    }
}

