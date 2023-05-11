#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double Euclidean_norm(std::vector<double>& v, int i)
{
    double res = 0;
    for (; i < v.size(); i++)
        res += v[i] * v[i];
    return  sqrt(res);
}

double sign(double a)
{
    return a > 0 ? 1 : -1;  
}

vector<double> V(vector<double> &A_j, int j)
{
    vector<double> v(A_j.size(), 0);
    double norm = Euclidean_norm(A_j, j);
    v[j] = A_j[j] + sign(A_j[j])*norm;
    for (int i = j+1; i < A_j.size(); i++)
        v[i] = A_j[i];
    return v;
}

double VTV(vector<double>& v)
{
    double vtv = 0;
    for(double& v_i: v)
        vtv += v_i*v_i;
    return vtv;
}

vector<vector<double>> VVT(vector<double> &v)
{
    vector<vector<double>> vvt(v.size(), vector<double>(v.size(), 0));
    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < v.size(); j++)
            vvt[i][j] = v[i]*v[j];
    return vvt;
}

vector<vector<double>> Get_H_for_j_colum (vector<double> &A_j, int j)
{
    vector<double> v = V(A_j, j);
    double vtv = VTV(v);
    vector<vector<double>> vvt = VVT(v);
    vector<vector<double>> H(A_j.size(), vector<double>(A_j.size(), 0));
    for(int i = 0; i < A_j.size(); i++)
        H[i][i] = 1;    // теперь это единичная матрица
    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < v.size(); j++)
            H[i][j] -= (2/vtv)*vvt[i][j];
    return H;
}

vector<vector<double>> Matrix_Multip(const vector<vector<double>>& A, const vector<vector<double>>& B) {
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

pair<vector<vector<double>>, vector<vector<double>>> Get_QR(vector<vector<double>> &A)
{
    vector<vector<double>> R = A;
    vector<vector<double>> Q(A.size(), vector<double>(A.size(), 0));
    for(int i = 0; i < Q.size(); i++)
        Q[i][i] = 1;
    for(int j = 0; j < R.size()-1; j++)
    {
        vector<double> A_j = {R[0][j], R[1][j], R[2][j]}; 
        vector<vector<double>> H = Get_H_for_j_colum(A_j, j);
        R = Matrix_Multip(H, R);
        Q = Matrix_Multip(Q, H);
    }
    return {Q, R};
}

double under_diag_norm(vector<vector<double>> matrix)
{
    double sum = 0;
    for (int i = 0; i <  matrix.size(); ++i)
        for (int j = 0; j < i; ++j)
            sum += matrix[i][j] * matrix[i][j];
    return sqrt(sum);
}

void Checking_Results(vector<vector<double>> A, vector<double> lambda, vector<vector<double>> V)
{
    cout << "Proverca resultatov" << endl;
    int n = lambda.size();

    for(int num = 0; num < n; num++) {
        cout << endl << "nomer sobstvennogo znacheniya:" << num << endl;

        vector<double> V_j (n, 0);
        for(int i = 0; i < n; i++)
            V_j[i] = V[i][num];

        vector<double> AV_j (n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                AV_j[i] += A[i][j] * V_j[j];

        vector<double> lambdaV_j (n, 0);
        for (int i = 0; i < n; i++)
            lambdaV_j[i] += lambda[num] * V_j[i];
        
        for(int i = 0; i < n; i++)
            cout << "\t" << AV_j[i] - lambdaV_j[i] <<endl;
    }
}

void Solve_by_QR(vector<vector<double>> &A, double eps)
{
    vector<vector<double>> res = A;
    vector<vector<double>> V (A.size(), vector<double> (A.size(), 0));
    for(int i = 0; i < V.size(); i++)
        V[i][i] = 1;
    while (under_diag_norm(res) > eps) {
        auto qr_pair = Get_QR(res);
        res = Matrix_Multip(qr_pair.second, qr_pair.first);
        V = Matrix_Multip(V, qr_pair.first);
    }
    cout << "Sobstvennie znacheniya:" << endl;
    for (int i = 0; i < res.size(); ++i)
        cout << '\t' << res[i][i]  << endl;
    cout << "Sobstvennie vectora:" << endl;
    for(int j = 0; j < V.size(); j++){
        cout << j << ":" << endl;
        for(int i = 0; i < V.size(); i++)
            cout << "\t" << V[i][j] << endl;
    }

    vector<double> lambda (res.size());
    for(int i = 0; i < res.size(); i++)
        lambda[i] = res[i][i];

    Checking_Results(A, lambda, V);
}

int main()
{
    vector<vector<double>> A = 
    {
        {-7, -5, -9},
        {-5, 5, 2},
        {-9, 2, 9}
    };
    Solve_by_QR(A, 0.01);
    return 0;
}