#include <bits/stdc++.h>

using namespace std;
//  X = 3
//  xi = 1.0, 2.0, 3.0, 4.0, 5.0
//  yi = 2.6931, 4.0986, 5.3863, 6.6094

int find_interval(double x, vector<double> &X)
{
    for(int i = 0; i < X.size()-1; i++)
        if(X[i] <= x && x >=  X[i + 1])
            return i;
    return -1;
}

void fst_derivative(double x, vector<double> &X, vector<double> &Y)
{
    int i = (find_interval(x, X));
    cout << ((Y[i+1]-Y[i])*pow((X[i]-X[i-1]),2) - (Y[i-1]-Y[i])*pow((X[i+1]-X[i]), 2))/
            ((X[i]-X[i-1])*(X[i+1]-X[i])*(X[i+1]-X[i-1])) << endl;
}

void sec_derivative(double x, vector<double> &X, vector<double> &Y)
{
    int i = (find_interval(x, X));
    cout << (2*(Y[i+1]-Y[i])*(X[i]-X[i-1]) + 2*(Y[i-1]-Y[i])*(X[i+1]-X[i]))/
            ((X[i]-X[i-1])*(X[i+1]-X[i])*(X[i+1]-X[i-1])) << endl;
}

int main()
{
    vector<double> X = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> Y = {2.6931, 4.0986, 5.3863, 6.6094};
    fst_derivative(3, X, Y);
    sec_derivative(3, X, Y);
    return 0;
}