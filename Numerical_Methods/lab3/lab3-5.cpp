#include <bits/stdc++.h>

using namespace std;
//  y = 1/(pow(x,4) + 16)
//  X0 = 0, Xk = 2, h1 = 0.5, h2 = 0.25

double f(double x)
{
    return 1/(pow(x,4) + 16);
}

double rectangle(double l, double r, double h)
{
    double x_i = l;
    double res = 0;
    while (x_i < r) {
        res += f((x_i + x_i + h) * 0.5);
        x_i += h;
    }
    return res * h;
}

double trapezoid(double l, double r, double h)
{
    double x_i = l;
    double res = 0;
    while (x_i < r) {
        res += (f(x_i) + f(x_i + h));
        x_i += h;
    }
    return res * h / 2;
}

double Simpson(double l, double r, double h)
{
    double x_i = l;
    double res = 0;
    while (x_i < r) {
        res += (f(x_i) + 4*f((x_i + x_i + h) * 0.5) + f(x_i + h));
        x_i += h;
    }
    return res * h / 6;
}

double runge_romberg(double Fh, double Fkh, double k, double p) {
    return (Fh - Fkh) / (std::pow(k, p) - 1.0);
}

int main()
{
    double l = 0, r = 2;
    double h1 = 0.5, h2 = 0.25;

    double rect1 = rectangle(l, r, h1);
    cout << "Метод прямоугольников с шагом " << h1 << ": " << rect1 << endl;
    double trap1 = trapezoid(l, r, h1);
    cout << "Метод трапеций с шагом " << h1 << ": " << trap1 << endl;
    double simp1 = Simpson(l, r, h1);
    cout << "Метод Симпсона с шагом " << h1 << ": " << simp1 << endl;

    cout << endl;

    double rect2 = rectangle(l, r, h2);
    cout << "Метод прямоугольников с шагом " << h2 << ": " << rect2 << endl;
    double trap2 = trapezoid(l, r, h2);
    cout << "Метод трапеций с шагом " << h2 << ": " << trap2 << endl;
    double simp2 = Simpson(l, r, h2);
    cout << "Метод Симпсона с шагом " << h2 << ": " << simp2 << endl;

    cout << endl;

    double rect_rr = runge_romberg(rect1, rect2, h2 / h1, 2);
    cout << "Погрешность вычислений методом прямоугольников: " << rect_rr
         << endl;
    double trap_rr = runge_romberg(trap1, trap2, h2 / h1, 2);
    cout << "Погрешность вычислений методом трапеций: " << trap_rr << endl;
    double simp_rr = runge_romberg(simp1, simp2, h2 / h1, 2);
    cout << "Погрешность вычислений методом Симпсона: " << simp_rr << endl;
    return 0;
}