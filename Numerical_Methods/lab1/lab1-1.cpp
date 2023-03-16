#include <bits/stdc++.h>
using namespace std;

const int eps = 10;

void Matrix_Sorting(
        vector <vector <double>> &A,
        vector <vector <double>> &L, 
        vector <vector <double>> &U,
        vector <double> &b, int i_start, int j){
        for(int i = i_start; i < A.size(); i++)
            if(abs(A[j][j]) < abs(A[i][j])){
                swap(A[j], A[i]);
                swap(L[j], L[i]);
                swap(U[j], U[i]);
                swap(b[j], b[i]);
            }
}

void show(vector <vector <double>> A) {
	for(int i = 0; i < A.size(); i++) {
		for(int j = 0; j < A.size(); j++)
			cout <<" "<< A[i][j] << " ";
		cout << endl;
	}
}

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
        Matrix_Sorting(A, L, U, b, k, k);
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

void proisv(vector <vector <double>> A, vector <vector <double>> B, 
			vector <vector <double>> &R)
{
	for(int i = 0; i < A.size(); i++)
		for(int j = 0; j < A.size(); j++)
			for(int k = 0; k < A.size(); k++)
				R[i][j] += A[i][k] * B[k][j];
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
    proisv(L,U,R);
    Solve(U, L, b, x);
    for(double& xi: x)
        cout << xi << ' ';
    cout << endl;
    return 0;
}