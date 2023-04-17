#include <bits/stdc++.h>
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

double VTV (vector<double>& v)
{
    double vtv = 0;
    for(double& v_i: v)
        vtv += v_i*v_i;
    return vtv;
}

vector<vector<double>> VVT (vector<double> &v)
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
    for(int j = 0; j < A.size()-1; j++)
    {
        vector<double> A_j = {A[0][j], A[1][j], A[2][j]}; 
        vector<vector<double>> H = Get_H_for_j_colum(A_j, j);
        R = Matrix_Multip(H, R);
        Q = Matrix_Multip(Q, H);
    }
    return {Q, R};
}