#include <bits/stdc++.h>
using namespace std;

const int eps = 10;

void LU(vector <vector <double>> A,
        vector <vector <double>> &L, 
		vector <vector <double>> &U){
	U=A;
	
    for(int k = 0; k < A.size(); k++)
        for(int i = k+1; i < A.size(); i++)
            for(int j = 0; j < A.size(); j++){
                if(j == k)
                    L[i][k] = U[i][k]/U[k][k];
                U[i][j] -= U[k][j]*L[i][k];
            }
    for(int i = 0; i < A.size(); i++)
        L[i][i] = 1;
}

void LU_With_Selection_Of_Main_Element(
        vector <vector <double>> &A,
        vector <vector <double>> &L, 
        vector <vector <double>> &U,
        vector <double> &b){
    U=A;
    for(int k = 0; k < A.size(); k++){
        for(int i = k; i < A.size(); i++)
            if(abs(A[k][k]) < abs(A[i][k])){
                swap(A[k], A[i]);
                swap(L[k], L[i]);
                swap(U[k], U[i]);
                swap(b[k], b[i]);
            }
        for(int i = k+1; i < A.size(); i++)
            for(int j = 0; j < A.size(); j++){
                if(j == k)
                    L[i][k] = U[i][k]/U[k][k];
                U[i][j] -= U[k][j]*L[i][k];
            }
    }
    for(int i = 0; i < A.size(); i++)
        L[i][i] = 1;
}

void Solve (vector <vector <double>> &U,
            vector <vector <double>> &L, 
			vector <double> &b,
            vector <double> &x){
    vector <double> y(x.size());
    double sum;
    for(int n = 0; n < x.size(); n++){
        sum = 0;
        for(int k = 0; k < n; k++){
            sum += L[n][k]*y[k];
        }
        y[n] = b[n] - sum;
    }
    for(int n = x.size()-1; n >= 0 ; n--){
        sum = 0;
        for(int k = n; k < x.size(); k++){
            sum += U[n][k]*x[k];
        }
        x[n] = (y[n] - sum)/U[n][n];
        x[n] = round(x[n]*pow(10, eps))/pow(10, eps);
    }
}

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
    vector <vector<double>> A(n, vector<double> (n)),
                            L(n, vector<double> (n)),
                            U(n, vector<double> (n)),
                            R(n, vector<double> (n));
    vector <double> b(n, 0), x(n, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
        cin >> b[i];
    }
    LU_With_Selection_Of_Main_Element(A, L, U, b);
    Solve(U, L, b, x);
    if(Check_The_Result(A, x, b)){
        for(double& xi: x)
            cout << xi << ' ';
        cout << endl;
    } else 
        cout << "не правильное решил" << endl;
    return 0;
}