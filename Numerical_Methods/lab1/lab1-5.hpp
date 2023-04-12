#include <bits/stdc++.h>
using namespace std;

vector<double> V(vector<double> &A_j, int j)
{
    vector<double> v(A_j.size(), 0);
    // v[j] += A_j[j]*A_j[j];
    for (int i = j+1; i < A_j.size(); i++)
    {
        v[j] += A_j[i]*A_j[i];
        v[i] = A_j[i];
    }
    v[j] = sqrt(v[j]);
    v[j] = A_j[j] > 0 ? v[j] : -v[j];   //sign
    v[j] = A_j[j] + v[j];
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
            H[i][j] -= 2*vvt[i][j]/vtv;
    return H;
}

vector<vector<double>> Matrix_Multip(const vector<vector<double>>& A,
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

pair<vector<vector<double>>, vector<vector<double>>> Get_QR(vector<vector<double>> &A)
{
    vector<vector<double>> R = A;
    vector<vector<double>> Q(A.size(), vector<double>(A.size(), 0));
    for(int i = 0; i < Q.size(); i++)
        Q[i][i] = 1;
    for(int j = 0; j < A.size()-1; j++)
    {
        vector<vector<double>> H = Get_H_for_j_colum(A[j], j);
        R = Matrix_Multip(H, R);
        Q = Matrix_Multip(Q, H);
    }
    return pair(Q, R);
}