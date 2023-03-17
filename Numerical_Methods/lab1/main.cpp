#include "lab1-1.hpp"
#include "lab1-2.hpp"

using namespace std;

void Check_The_Result (vector <vector <double>> &A,
                       vector <double> &x,
                       vector <double> &b){ 
    double my_b;
    for(int i = 0; i < x.size(); i++){
        my_b = 0;
        for(int j = 0; j < x.size(); j++){
            my_b += A[i][j]*x[j];
        }
        if(my_b != b[i]){
            cout << "неправильно решил" << endl;
            return;
        }
    }
    for(double& xi: x)
            cout << xi << endl;
}

void Read_SLAU (vector <vector<double>> &A,
                vector <double> &b,
                int n){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
        cin >> b[i];
    }
}

int main(){
    int n;
    cin >> n;
    vector <vector<double>> A(n, vector<double> (n));
    vector <double> b(n, 0), x(n, 0);
    Read_SLAU(A, b, n);
    Solve_With_LU(A, b, x, n);
    Check_The_Result(A, x, b);
    cout << endl;
    Solve_With_Run_Through(A, b, x, n);
    Check_The_Result(A, x, b);
    return 0;
}