#include <bits/stdc++.h>

using namespace std;
// x^3 - 2x^2 - 10x + 15 = 0
const double EPS = 0.001;
const double lambda = 0.006;


double phi_for_iter (double x)
{
    return (x*x*x - 2*x*x + 15)/10;
}

double dphi_for_iter(double x)
{
    return (3*x*x - 4*x)/10;
}

double f(double x)
{
    return pow(x, 3) - 2*pow(x, 2) - 10*x + 15;
}

double df(double x)
{
    return 3*pow(x, 2) - 4*x - 10;
}

double ddf(double x)
{
    return 6*x - 4;
}

double phi_for_Newton (double x)
{
    return x - f(x)/df(x);
}

double dphi_for_Newton(double x)
{
    return -f(x)*ddf(x)/pow(df(x), 2);
}

void Simple_Iterations(double a, double b)
{
    double q = abs(max(dphi_for_iter(a), dphi_for_iter(b)));
    if(q > 1) exit(1);
    double x = (b+a)/2, x_prev, eps_k;
    int count = 0;
    while (abs(x-x_prev) * q/(1-q) > EPS)
    {
        x_prev = x;
        x = phi_for_iter(x);
        count++;
    }
    cout << "корень = " << x << endl;
    cout << "кол-во итераций = " << count << endl;
}

void Newton(double a, double b)
{
    double x, x_prev ;
    if(f(a)*ddf(a) > 0) x = a, x_prev = b;
    else if(f(b)*ddf(b) > 0) x = b, x_prev = a;
    else exit(1);
    int count = 0;
    while(abs(x - x_prev) > EPS)
    {
        x_prev = x;
        x = phi_for_Newton(x_prev);
        count++;
    }
    cout << "корень = " << x << endl;
    cout << "кол-во итераций = " << count << endl;
}

int main()
{
    cout << "Простые итерации" << endl;
    Simple_Iterations(0, 2.5);
    cout << "Метод Ньютона" << endl;
    Newton(2.62, 10);
    return 0;
}