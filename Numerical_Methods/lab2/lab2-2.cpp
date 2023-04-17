#include <bits/stdc++.h>

using namespace std;

//  x1^2 + 4x2^2 - 9 = 0
//  -x1 -e^x1 + 3x2 = 0
//  (1.118, 1.392)

const double EPS = 0.01;

// double f1(double x1, double x2) {
//     return pow(x1, 2) + 4 * pow(x2, 2) - 9;
// }

// double f2(double x1, double x2) {
//     return -x1 - exp(x1) + 3 * x2;
// }

// double phi1(double x1, double x2) {
//     return sqrt(9 - 4*pow(x2, 2));
// }

// double phi2(double x1, double x2) {
//     return (x1 + exp(x1))/3;
// }

// double get_q(double x1, double x2)
// {
//     return max(-4*x2/sqrt(9 - 4*pow(x2, 2)), (exp(x1)+1)/3);
// }

// void iteration(double a, double b, double c, double d)
// {
//     double x1 = (b - a) / 2;
//     double x2 = (d - c) / 2;
//     double x_prev1, x_prev2;
//     double q = get_q(x1, x2);
//     if(q >= 1) exit(1);
//     while(max(abs(x1-x_prev1), abs(x2-x_prev2))*q/(1-q) > EPS)
//     {
//         x_prev1 = x1;
//         x_prev2 = x2;
//         x1 = phi1(x_prev1, x_prev2);
//         x2 = phi2(x_prev1, x_prev2);
//     }
// }

// int main()
// {
//     iteration(1, 2, 1, 2);
//     return 0;
// }

int main() {
    double x1 = 0.0, x2 = 0.0;
    double x1_new, x2_new;
    double tol = 1e-6;
    int max_iter = 1000;
    int iter = 0;

    while (iter < max_iter) {
        x1_new = sqrt(9 - 4 * pow(x2, 2));
        x2_new = (exp(-x1) - x1);

        if (abs(x1_new - x1) < tol && abs(x2_new - x2) < tol) {
            break;
        }

        x1 = x1_new;
        x2 = x2_new;
        iter++;
    }

    cout << "x1: " << x1 << endl;
    cout << "x2: " << x2 << endl;

    return 0;
}