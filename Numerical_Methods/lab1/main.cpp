#include <fstream>
#include "json.hpp"
#include "lab1-1.hpp"
#include "lab1-2.hpp"
#include "lab1-3.hpp"
#include "lab1-4.hpp"
#include "lab1-5.hpp"

using namespace std;
using json = nlohmann::json;

void Check_The_Result (vector <vector <double>> &A,
                       vector <double> &x,
                       vector <double> &b){ 
    double my_b;
    for(int i = 0; i < x.size(); i++){
        my_b = 0;
        for(int j = 0; j < x.size(); j++){
            my_b += A[i][j]*x[j];
        }
        my_b = round(my_b*pow(10, 5))/pow(10, 5);
        if(my_b != b[i]){
            cout << "неправильно решил" << endl;
            return;
        }
    }
    cout << "Решение:" << endl;
    for(double& xi: x)
            cout << "\t" << xi << endl;
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

void Read_SLAU_from_JSON (vector <vector<double>> &A,
                          vector <double> &b,
                          string file_name,
                          int lab_num,
                          int& n){
    std::ifstream file(file_name);
    json data;
    file >> data;

    A = data["lab" + to_string(lab_num) + "_A"].get<std::vector<std::vector<double>>>();
    b = data["lab" + to_string(lab_num) + "_b"].get<std::vector<double>>();
    n = b.size();
}

void Read_Matrix (vector <vector<double>> &A,
                int n){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
}

int main(){
    int n, eps = 10;
    vector <vector<double>> A;
    vector <double> b, x;

    cout << "lab1-1" << endl;
    Read_SLAU_from_JSON(A, b, "input.json", 1, n);
    x.resize(n, 0);
    Solve_With_LU(A, b, x, n);
    Check_The_Result(A, x, b);

    cout << "lab1-2" << endl;
    Read_SLAU_from_JSON(A, b, "input.json", 2, n);
    x.resize(n, 0);
    Solve_With_Run_Through(A, b, x, n);
    Check_The_Result(A, x, b);

    cout << "lab1-3" << endl;
    Read_SLAU_from_JSON(A, b, "input.json", 3, n);
    x.resize(n, 0);
    cout << "метод простых итераций:" << endl;
    Solve_By_Iterative_Method(A, b, x, "Simple_Iterations", eps, n);
    Check_The_Result(A, x, b);
    cout << "метод Зейделя:" << endl;
    Solve_By_Iterative_Method(A, b, x, "Seidel", eps, n);
    Check_The_Result(A, x, b);
    
    cout << "lab1-4" << endl;
    Read_SLAU_from_JSON(A, b, "input.json", 4, n);
    Jacobi_Eigenvalue(A, eps);

    cout << "lab1-5" << endl;
    Read_SLAU_from_JSON(A, b, "input.json", 5, n);
    Get_QR(A);
    return 0;
}