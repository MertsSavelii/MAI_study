#include <bits/stdc++.h>
using namespace std;

void Checking_Diagonal_Predominance_Of_Matrix 
                       (vector <vector <double>> &A){
    double sum_a_ij;
    for (size_t i = 0; i < A.size(); i++)
    {
        sum_a_ij = 0;
        for (size_t j = 0; j < A.size(); j++)
            sum_a_ij += abs(A[i][j]);
        if(2*abs(A[i][i]) < sum_a_ij){
            cout << "Решение не сходится!" << endl;
            exit(0);
        }
    }
}

void Reduction_To_Equivalent_Form_By_Jacobi_Method (
                        vector <vector <double>> &A,
                        vector <double> &b,
                        vector <vector <double>> &alpha,
                        vector <double> &beta,
                        int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            alpha[i][j] = (i != j) ? -A[i][j]/A[i][i] : 0; 
        beta[i] = b[i]/A[i][i];
    }
}

bool End_Of_Iterations (vector <double> &x_prev,
                        vector <double> &x_curr,
                        int eps,
                        int n){
    for(int i = 0; i < n; i++)
        if(abs(x_curr[i] - x_prev[i]) <= pow(0.1, eps))
            return true;
    return false;
}

void Solve_With_Simple_Iterations (vector <vector <double>> &alpha,
                                   vector <double> &beta,
                                   vector <double> &x,
                                   int eps,
                                   int &k,
                                   int n){
    vector <double> x_prev (n, 0);
    do {
        swap(x, x_prev);
        for (size_t i = 0; i < n; i++) {
            x[i] = beta[i];
            for (size_t j = 0; j < n; j++)
                x[i] += alpha[i][j]*x_prev[j];
            x[i] = round(x[i]*pow(10, eps))/pow(10, eps);
        }   
        k++;
    } while (!End_Of_Iterations(x_prev, x, eps, n));
}

void Solve_With_Seidel (vector <vector <double>> &alpha,
                        vector <double> &beta,
                        vector <double> &x,
                        int eps,
                        int &k,
                        int n){
    vector <double> x_prev (n, 0);
    do {
        swap(x, x_prev);
        for (size_t i = 0; i < n; i++) {
            x[i] = beta[i];
            for (size_t j = 0; j < i; j++)
                x[i] += alpha[i][j]*x[j];
            for (size_t j = i; j < n; j++)
                x[i] += alpha[i][j]*x_prev[j];
            x[i] = round(x[i]*pow(10, eps))/pow(10, eps);
        }  
        k++;
    } while (!End_Of_Iterations(x_prev, x, eps, n));
}

void Solve_By_Iterative_Method (vector <vector <double>> &A,
                                vector <double> &b,
                                vector <double> &x,
                                string method,
                                int eps,
                                int n){
    vector <vector <double>> alpha (n, vector <double> (n, 0));
    vector <double> beta (n, 0);
    Checking_Diagonal_Predominance_Of_Matrix(A);
    Reduction_To_Equivalent_Form_By_Jacobi_Method(A, b, alpha, beta, n);
    x = beta; // нулевое приближение х0
    int k = 0;
    if(method == "Simple_Iterations")
        Solve_With_Simple_Iterations(alpha, beta, x, eps, k, n);
    else
        Solve_With_Seidel(alpha, beta, x, eps, k, n);
    cout << "Количество итераций: " << k << endl;
}