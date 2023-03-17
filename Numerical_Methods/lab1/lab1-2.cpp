#include <bits/stdc++.h>
using namespace std;

void Read_Tridiagonal_Matrix (vector <double> &a, 
                              vector <double> &b, 
                              vector <double> &c,
                              vector <double> &d, 
                              vector <double> &P, 
                              vector <double> &Q,
                              int n){
    cin >> b[0] >> c[0] >> d[0];
    P[0] = -c[0]/b[0];
    Q[0] = d[0]/b[0];
    for(int i = 1; i < n-1; i++){
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        P[i] = -c[i] / (b[i] + a[i]*P[i-1]);
        Q[i] = (d[i] - a[i]*Q[i-1]) / (b[i] + a[i]*P[i-1]);
    }
    cin >> a[n-1] >> b[n-1]>> b[n-1];
    Q[n-1] = (d[n-1] - a[n-1]*Q[n-2]) / (b[n-1] + a[n-1]*P[n-2]);
}

int main(){
    int n; cin >> n;
    vector <double> a(n, 0), b(n, 0), c(n, 0),
                    d(n, 0), P(n, 0), Q(n, 0);
    Read_Tridiagonal_Matrix(a, b, c, d, P, Q, n);
    vector <double> x(n, 0);
    x[n-1]= Q[n-1];
    for(int i = n-2; i >= 0; i--)
        x[i] = P[i]*x[i+1] + Q[i];
    for(int i = 0; i < n; i++)
        cout << x[n] << endl;
    return 0;
}