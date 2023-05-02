#include <bits/stdc++.h>

using namespace std;
//  y = tg(x) + x

# define M_PI 3.14159265358979323846

double f(double x)
{
    return tan(x) + x;
}

void lagrange_interpolation_polynomial(double x, vector<double> X)
{
    double res = 0;
    double comp_x_xi = 1;
    double comp_xj_xi = 1;
    for(int j = 0; j <= 3; j++)
    {
        comp_x_xi = 1;
        comp_xj_xi = 1;
        for(int i = 0; i <= 3; i++)
            if(i != j)
            {
                comp_x_xi *= x - X[i];
                comp_xj_xi *= X[j] - X[i];
            }
        double yi = f(X[j]);
        double quotient_yj_com_xj_xi = yi/comp_xj_xi;
        res += comp_x_xi*quotient_yj_com_xj_xi;
    }
    cout << "Вычислим значение интерполяционного многочлена Лагранжа и точное значение функции в точке х* = " << x << endl;
    cout << "L(" << x << ") = " << res << ", y(" << x << ") = " << f(x) << endl;
    cout << "Таким образом, абсолютная погрешность интерполяции составляет: " << abs(res - f(x)) << endl;
}

double separated_differences(int n, int q, vector<double> X)
{
    if(n == 0)
        return f(X[q]);
    return (separated_differences(n-1, q, X) - separated_differences(n-1, q+1, X)) / (X[q] - X[q+n]);
}

void newton_interpolation_polynomial(double x, vector<double> X)
{
    double res = 0;
    for(int j = 0; j <= 3; j++)
    {
        double diff_x_xi = 1;
        for (int i = 0; i <= j-1; i++)
        {
            diff_x_xi *= x - X[i];
        }
        res += separated_differences(j, 0, X)*diff_x_xi;
    }
    cout << "Вычислим значение интерполяционного многочлена Ньютона и точное значение функции в точке х* = " << x << endl;
    cout << "N(" << x << ") = " << res << ", y(" << x << ") = " << f(x) << endl;
    cout << "Таким образом, абсолютная погрешность интерполяции составляет: " << abs(res - f(x)) << endl;
}

int main()
{
    double x = 3*M_PI/16;
    vector<double> X_1 = {0, M_PI/8, 2*M_PI/8, 3*M_PI/8};
    vector<double> X_2 = {0, M_PI/8, M_PI/3, 3*M_PI/8};
    lagrange_interpolation_polynomial(x, X_1);
    newton_interpolation_polynomial(x, X_1);
    return 0;
}