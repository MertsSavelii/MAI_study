#include <bits/stdc++.h>

using namespace std;
//  X* = 1.5
//  i  = 0 1 2 3 4
//  xi = 0.0 0.9 1.8 2.7 3.6
//  fi = 0.0 0.72235 1.5609 2.8459 7.7275

void Read_Tridiagonal_Matrix(vector <double> &a, 
                             vector <double> &b, 
                             vector <double> &c,
                             vector <double> &d,
                             vector <double> &y,
                             double h){
    int n = y.size()-2;
    a[0] = 0, c[n-1] = 0;
    for(int i = 0; i < n; i++)
        d[i] = 3/h*(y[i+2]-2*y[i+1] +y[i]);
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
    for(int i = x.size()-1; i >= 2; i--)
        x[i] = x[i-2];
    x[0] = x[1] = 0;
}

void Solve_With_Run_Through(vector <double> &x,
                            vector <double> &y,
                            double h){
    int n = y.size()-2;
    vector <double> a(n, h), b(n, 4*h), c(n, h),
                    d(n, 0), P(n, 0), Q(n, 0);
    Read_Tridiagonal_Matrix(a, b, c, d, y, h);
    Direct_Passage(a, b, c, d, P, Q, n);
    Reverse_Passage(x, P, Q, n);
}

// double test_f(double x)
// {
//     return x*log(x);
// }
// double test_hi = 0.4;
// vector<double> test_x = {0.1, 0.5, 0.9, 1.3, 1.7, 2.1};
// vector<double> test_y = {test_f(test_x[0]), test_f(test_x[1]), test_f(test_x[2]), test_f(test_x[3]), test_f(test_x[4]), test_f(test_x[5])};

void find_a(vector<double>& a, vector<double>& y)
{
    for(int i = 1; i < a.size(); i++)
        a[i] = y[i-1];
}

void find_b(vector<double> &b, vector<double> &c,vector<double> &y, double h)
{
    for(int i = 1; i < c.size(); i++)
        b[i] = (y[i]-y[i-1])/h - h/3*(c[i+1]+2*c[i]);
}

void find_c(vector<double>& c, vector<double>& y, double h)
{
    Solve_With_Run_Through(c, y, h);
}

void find_d(vector<double> &d, vector<double> &c, double h)
{
    for(int i = 1; i < d.size(); i++)
        d[i] = (c[i+1] - c[i])/(3*h);
}

void cubic_spline(double x, vector<double>& X, vector<double>& Y, double hi)
{
    double res = 0;
    int n = X.size();
    vector<double> a(n, 0), b(n, 0), c(n+1, 0), d(n, 0);
    find_a(a, Y);
    find_c(c, Y, hi);
    find_b(b, c, Y, hi);
    find_d(d, c, hi);
    int i = 0;
    while(X[i] < x)
        i++;
    res = a[i] + b[i]*(x-X[i-1]) + c[i]*pow(x-X[i-1], 2) + d[i]*pow(x-X[i-1], 3);
    cout << "Вычислим значение сплайна х* = " << x << endl;
    cout << "S(" << x << ") = " << res << endl;
}

int main()
{
    double x = 1.5;
    vector<double> X = {0.0, 0.9, 1.8, 2.7, 3.6};
    vector<double> Y = {0.0, 0.72235, 1.5609, 2.8459, 7.7275};
    cubic_spline(x, X, Y, 0.9);
    return 0;
}