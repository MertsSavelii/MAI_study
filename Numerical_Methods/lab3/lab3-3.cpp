#include <bits/stdc++.h>

using namespace std;
//  xi -0.9 0.0 0.9 1.8 2.7 3.6
//  yi -1.2689 0.0 1.2689 2.6541 4.4856 9.9138

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
        x[i] = round(x[i]*pow(10, 10))/pow(10, 10);
    }
}

// double test_f(double x)
// {
//     return x*log(x);
// }
// vector<double> test_x = {0.1, 0.5, 0.9, 1.3, 1.7, 2.1};
// vector<double> test_y = {test_f(test_x[0]), test_f(test_x[1]), test_f(test_x[2]), test_f(test_x[3]), test_f(test_x[4]), test_f(test_x[5])};

void fst_degree_polynom(vector<double> x, vector<double> y)
{
    int n = x.size();
    vector<double> a(2, 0);
    double sum_xi = 0, sum_yi = 0, sum_xi2 = 0, sum_yi_xi = 0;
    for(int i = 0; i < n; i++)
    {
        sum_xi += x[i];
        sum_yi += y[i];
        sum_xi2 += x[i]*x[i];
        sum_yi_xi += x[i]*y[i];
    }
    vector<vector<double>> A_for_LU = {{double(n), sum_xi}, {sum_xi, sum_xi2}};
    vector<double> b_for_LU = {sum_yi, sum_yi_xi};
    Solve_With_LU(A_for_LU, b_for_LU, a, 2);
    double PHI_1 = 0;
    for(int i = 0; i < n; i++)
        PHI_1 += pow((a[0] + a[1]*x[i]) - y[i], 2);
    cout << "Сумма квадратов ошибок Ф1 = " << PHI_1 << endl;
}

void sec_degree_polynom(vector<double> x, vector<double> y)
{
    int n = x.size();
    vector<double> a(3, 0);
    double sum_xi = 0, sum_xi2 = 0, sum_xi3 = 0, sum_xi4 = 0;
    double sum_yi = 0, sum_yi_xi = 0, sum_yi_xi2 = 0;
    for(int i = 0; i < n; i++)
    {
        sum_xi += x[i];
        sum_xi2 += x[i]*x[i];
        sum_xi3 += x[i]*x[i]*x[i];
        sum_xi4 += x[i]*x[i]*x[i]*x[i];
        sum_yi += y[i];
        sum_yi_xi += x[i]*y[i];
        sum_yi_xi2 += x[i]*x[i]*y[i];
    }
    vector<vector<double>> A_for_LU =  {{double(n), sum_xi, sum_xi2}, 
                                        {sum_xi, sum_xi2, sum_xi3},
                                        {sum_xi2, sum_xi3, sum_xi4}};
    vector<double> b_for_LU = {sum_yi, sum_yi_xi, sum_yi_xi2};
    Solve_With_LU(A_for_LU, b_for_LU, a, 3);
    double PHI_2 = 0;
    for(int i = 0; i < n; i++)
        PHI_2 += pow((a[0] + a[1]*x[i] + a[2]*x[i]*x[i]) - y[i], 2);
    cout << "Сумма квадратов ошибок Ф2 = " << PHI_2 << endl;
}

int main()
{
    vector<double> x = {-0.9, 0.0, 0.9, 1.8, 2.7, 3.6};
    vector<double> y = {-1.2689, 0.0, 1.2689, 2.6541, 4.4856, 9.9138};
    fst_degree_polynom(x, y);
    sec_degree_polynom(x, y);
    return 0;
}