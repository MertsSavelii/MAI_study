#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// #define M_PI		3.14159265358979323846

void Indexes_Max_Elem(const vector<vector<double>>& A,
                      int& i_max,
                      int& j_max) {
    double a_max = -__DBL_MAX__;
    for (int i = 1; i < A.size(); i++) 
        for (int j = 0; j < i; j++) 
            if (abs(A[i][j]) > a_max) {
                a_max = abs(A[i][j]);
                i_max = i;
                j_max = j;
            }
}

vector<vector<double>> Transpose_Matrix(const vector<vector<double>>& A) {
    vector<vector<double>> result(A[0].size(), vector<double>(A.size(), 0));
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A[i].size(); j++)
            result[j][i] = A[i][j];
    return result;
}

double Get_Phi(double a_ii, double a_jj, double a_ij) {
    return a_ii == a_jj ? M_PI / 4 : 0.5 * atan(2 * a_ij / (a_ii - a_jj));
}

void Initialize_U(vector<vector<double>>& U, int i_max, int j_max, double phi) {
    for (int i = 0; i < U.size(); i++)
        U[i][i] = 1;
    U[i_max][j_max] = -sin(phi);
    U[j_max][i_max] = sin(phi);
    U[i_max][i_max] = U[j_max][j_max] = cos(phi);
}

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

bool End_Of_Iterations(const vector<vector<double>>& A, double eps) {
    double sum = 0.0;
    for (int i = 1; i < A.size(); i++)
        for (int j = 0; j < i; j++)
            sum += pow(A[i][j], 2);
    return sqrt(sum) <= pow(10, -eps) ? true : false;
}

void Jacobi_Eigenvalue(vector<vector<double>> lambda,
                       vector<vector<double>> V,
                       const vector <vector <double>> &A,
                       double eps){
    int i_max, j_max;
    double phi;
    vector<vector<double>> V_(A.size(), vector<double> (A.size(), 0));
    lambda = A;
    V = V_;
    for(int i = 0; i < V.size(); i++)
        V[i][i] = 1;
    // vector <double> lambda;
    while (!End_Of_Iterations(lambda, eps))
    {
        Indexes_Max_Elem(lambda, i_max, j_max);
        phi = Get_Phi(lambda[i_max][i_max], lambda[j_max][j_max], lambda[i_max][j_max]);
        vector <vector <double>> U(A.size(), vector<double> (A.size(), 0));
        Initialize_U(U, i_max, j_max, phi);
        vector <vector <double>> U_t = Transpose_Matrix(U);
        lambda = Matrix_Multiplication(U_t, Matrix_Multiplication(lambda, U));
        V = Matrix_Multiplication(V, U);
    } 
    cout << "Собственные значения:" << endl;
    for(int i = 0; i < lambda.size(); i++)
        cout << "\tλ" << i << " = " << lambda[i][i] << endl;
    cout << "Собственные вектора:" << endl;
    for(int j = 0; j < V.size(); j++){
        cout << j << ":" << endl;
        for(int i = 0; i < V.size(); i++)
            cout << "\t" << V[i][j] << endl;
    }
}