#include <bits/stdc++.h>
using namespace std;

void show(vector <vector <int>> A) {
	for(int i = 0; i < A.size(); i++) {
		for(int j = 0; j < A.size(); j++)
			cout <<" "<< A[i][j] << " ";
		cout << endl;
	}
}

int main(){
    int n;
    cin >> n;
    vector <vector<int>> A(n), L(n), U(n);
    int aij;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            cin >> aij;
            A[i].push_back(aij);
            L[i].push_back(0);
            U[i].push_back(0);
        }
    show(A);
    return 0;
}