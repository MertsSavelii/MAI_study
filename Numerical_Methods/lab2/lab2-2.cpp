#include <bits/stdc++.h>

using namespace std;

//  x1^2/9 + x2^2/2.25 - 1 = 0
//  -x1 -e^x1 + 3x2 = 0

const double EPS = 0.01;

double phi1(double x1, double x2) {
    return -3*sqrt(1 - x2*x2/2.25);
    // return x1*x1/9+x2*x2/2.25 - 1 + x1;
}

double phi2(double x1, double x2) {
    return (exp(x1)+x1)/3;
}

double d_phi1_d_x1(double x1, double x2) {
    return 0;
    // return 2*x1/9+1;
}

double d_phi1_d_x2(double x1, double x2) {
    return 4*x2/sqrt(9-4*x2*x2);
    // return 2*x2/2.25;
}

double d_phi2_d_x1(double x1, double x2) {
    return (exp(x1)+1)/3;
}

double d_phi2_d_x2(double x1, double x2) {
    return 0;
}

double norm_of_majoring_matrix(double l1, double r1, double l2, double r2){
    double q = DBL_MIN;
    for(double l : {l1, l2})
        for(double r : {r1, r2})
            q = max({q, abs(d_phi1_d_x1(l, r)), 
                        abs(d_phi1_d_x2(l, r)), 
                        abs(d_phi2_d_x1(l, r)), 
                        abs(d_phi2_d_x2(l, r))});
    return q;
}

void iteration(double l1, double r1, double l2, double r2)
{
    double q = norm_of_majoring_matrix(l1, r1, l2, r2);
    double eps_coef = abs(q/(1-q));
    // if (q >= 1) exit(1);
    double x1 = l1 + (r1-l1)/2, x2 = l2 + (r2-l2)/2;
    double x_prev1, x_prev2;
    double r = 2*EPS;
    do
    {
        x_prev1 = x1, x_prev2 = x2;
        x1 = phi1(x_prev1, x_prev2);
        x2 = phi2(x_prev1, x_prev2);
        r = max(abs(x1-x_prev1), abs(x2-x_prev2))*eps_coef;
    } while (r > EPS);
    cout << x1 << ' ' << x2 << endl;
}

double f1(double x1, double x2) {
    // return 0.1*x1*x1 + x1 + 0.2*x2*x2 - 0.3;
    return x1*x1/9 + x2*x2/2.25 - 1;
}

double f2(double x1, double x2) {
    // return 0.2*x1*x1 + x2 - 0.1*x1*x2 - 0.7;
    return 3*x2 - exp(x1) - x1;
}

double d_f1_d_x1(double x1, double x2) {
    // return 0.2*x1 + 1;
    return 2*x1/9;
}

double d_f1_d_x2(double x1, double x2) {
    // return 0.4*x2;
    return 8*x2/9;
}

double d_f2_d_x1(double x1, double x2) {
    // return 0.4*x1 - 0.1*x2;
    return -exp(x1) - 1;
}

double d_f2_d_x2(double x1, double x2) {
    // return 1 - 0.1*x1;
    return 3;
}

void newton(double l1, double r1, double l2, double r2)
{
    double x1 = l1 + (r1-l1)/2, x2 = l2 + (r2-l2)/2;
    double x_prev1, x_prev2;
    double r = 2*EPS;
    double det_A1, det_A2, det_J;
    while (r > EPS)
    {
        x_prev1 = x1, x_prev2 = x2;
        det_A1 = f1(x1, x2)*d_f2_d_x2(x1, x2) - f2(x1, x2)*d_f1_d_x2(x1, x2);
        det_A2 = f2(x1, x2)*d_f1_d_x1(x1, x2) - f1(x1, x2)*d_f2_d_x1(x1, x2);
        det_J = d_f1_d_x1(x1, x2)*d_f2_d_x2(x1, x2) - d_f2_d_x1(x1, x2)*d_f1_d_x2(x1, x2);
        x1 -= det_A1/det_J;
        x2 -= det_A2/det_J;
        r = max(abs(x1-x_prev1), abs(x2-x_prev2));  
    }
    cout << x1 << ' ' << x2 << endl;
}

int main()
{
    iteration(1, 1.2, 1.2, 1.4);
    // newton(0, 0.5, 0.5, 1); из методички
    newton (1, 1.2, 1.2, 1.4);
    return 0;
}