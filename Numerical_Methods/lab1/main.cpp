#include "lab1-1.hpp"

using namespace std;

bool Check_The_Result (vector <vector <double>> &A,
                       vector <double> &x,
                       vector <double> &b){ 
    double my_b;
    for(int i = 0; i < x.size(); i++){
        my_b = 0;
        for(int j = 0; j < x.size(); j++){
            my_b += A[i][j]*x[j];
        }
        if(my_b != b[i])
            return false;
    }
    return true;
}

int main(){
    int n;
    cin >> n;
    vector <vector<double>> A(n, vector<double> (n));
    vector <double> b(n, 0), x(n, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
        cin >> b[i];
    }
    
    Solve_With_LU(A, b, x, n);
    if(Check_The_Result(A, x, b))
        for(double& xi: x)
            cout << xi << endl;
    else 
        cout << "не правильное решил" << endl;
    return 0;
}