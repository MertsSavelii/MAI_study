#include <iostream>
#include <cmath>
#include <vector>

double dot(std::vector<double> v1, std::vector<double> v2, int)
{
    double sum = 0;
    int n = v1.size();
    for (int i = 0; i < n; ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

std::vector<std::vector<double>> dot(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    int n = A.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

std::vector<std::vector<double>> dot(std::vector<double> v1, std::vector<double> v2)
{
    int n = v1.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = v1[i] * v2[j];
        }
    }
    return result;
}

void _permute_rows(std::vector<std::vector<double>>& matrix, int i, int j)
{
    if (i == j) return;
    for (int k = 0; k < matrix[0].size(); ++k) std::swap(matrix[i][k], matrix[j][k]);
}

void _permute_columns(std::vector<std::vector<double>>& matrix, int i, int j)
{
    if (i == j) return;
    for (int k = 0; k < matrix.size(); ++k) std::swap(matrix[k][i], matrix[k][j]);
}

void _permute_rows(std::vector<double>& vector, int i, int j)
{
    if (i == j) return;
    std::swap(vector[i], vector[j]);
}

void _permute_columns(std::vector<double>& vector, int i, int j)
{
    if (i == j) return;
    std::swap(vector[i], vector[j]);
}

void print(std::vector<std::vector<double>> matrix)
{
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<double>> calc_h_matrix(std::vector<double> v)
{
    int n = v.size();
    std::vector<std::vector<double>> id(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) id[i][i] = 1;
    std::vector<std::vector<double>> v_mat = dot(v, v);
    float num = dot(v, v, 0);
    std::vector<std::vector<double>> result(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = id[i][j] - (2 / num) * v_mat[i][j];
        }
    }
    return result;
}

double calc_norm(std::vector<std::vector<double>> matrix)
{
    double max = 0;
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) sum += std::abs(matrix[i][j]);
        if (sum > max) max = sum;
    }
    return max;
}

double euclidean_norm_k(std::vector<double> v, int k)
{
    double res = 0;
    int n = v.size();
    for (int i = k; i < n; ++i) {
        res += v[i] * v[i];
    }
    return std::sqrt(res);
}

double calc_norm(std::vector<double> vector)
{
    double max = 0;
    int n = vector.size();
    for (int i = 0; i < n; ++i) {
        if (std::abs(vector[i]) > max) max = std::abs(vector[i]);
    }
    return max;
}

double sign(double a)
{
    if (a > 0) return 1;
    else return -1;
}

double fram_norm(std::vector<std::vector<double>> matrix)
{
    int n = matrix.size();
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[i][j] * matrix[i][j];
        }
    }
    return sqrt(sum);
}

double under_diag_norm(std::vector<std::vector<double>> matrix)
{
    int n = matrix.size();
    double sum = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            sum += matrix[i][j] * matrix[i][j];
        }
    }
    return sqrt(sum);
}

std::pair<double, std::pair<int, int>> matrix_max(std::vector<std::vector<double>> matrix)
{
    int n = matrix.size();
    if (n == 1) return {0, {0,0}};
    double max = std::abs(matrix[0][1]);
    int row_index = 0;
    int column_index = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(matrix[i][j]) > max) {
                max = std::abs(matrix[i][j]);
                row_index = i; column_index = j;
            }
        }
    }
    return {max, {row_index, column_index}};
}

std::vector<std::vector<double>> create_u_matrix(int n, int i, int j, double phi)
{
    std::vector<std::vector<double>> u(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) u[i][i] = 1;
    u[i][i] = cos(phi); u[j][j] = cos(phi);
    u[j][i] = sin(phi); u[i][j] = -sin(phi);
    return u;
}

class Matrix
{
private:
    std::vector<std::vector<double>> matrix;
    int n; // count of rows
    int m; // count of columns
    void permute_rows(int i, int j);
    void permute_columns(int i, int j);
    int column_max(int j); // search for max in j column
    void row_transform(int i, int j, double lambda);
public:
    std::pair<Matrix, std::vector<std::pair<int, int>>> LU_decomposition();
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> QR_decomposition();
    std::vector<double> find_values_by_QR(double eps);
    std::vector<double> solve(std::vector<double> b);
    std::vector<double> solve3DiagMat(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> b_right);
    std::vector<double> simple_iterations(std::vector<double> b, double eps);
    std::pair<std::vector<double>, std::vector<std::vector<double>>> rotate_machine(double eps);
    std::vector<double> zeidel(std::vector<double> b, double eps);
    double calc_det();
    std::vector<std::vector<double>> back_matrix();
    std::vector<std::vector<double>> get_matrix() {return matrix;}
public:
    Matrix(std::vector<std::vector<double>> matrix): n(matrix.size()), m(matrix[0].size()), matrix(matrix) {}
    Matrix() {}

};

void Matrix::permute_rows(int i, int j)
{
    if (i == j) return;
    for (int k = 0; k < m; ++k) std::swap(matrix[i][k], matrix[j][k]);
}

void Matrix::permute_columns(int i, int j)
{
    if (i == j) return;
    for (int k = 0; k < n; ++k) std::swap(matrix[k][i], matrix[k][j]);
}

void Matrix::row_transform(int i, int j, double lambda)
{
    for (int k = 0; k < m; ++k) {
        matrix[j][k] -= lambda * matrix[i][k];
    }
}

int Matrix::column_max(int j)
{
    int max = std::abs(matrix[j][j]);
    int max_index = j;
    for (int i = j; i < n; ++i) {
        if (std::abs(matrix[i][j]) > max)  {
            max = std::abs(matrix[i][j]);
            max_index = i;
        }
    }
    return max_index;
}

std::pair<Matrix, std::vector<std::pair<int, int>>> Matrix::LU_decomposition()
{
    std::vector<std::vector<double>> matrix_old = matrix;
    std::vector<std::vector<double>> L(n, std::vector<double>(n));
    std::vector<std::vector<double>> buffer(n, std::vector<double>(n));
    std::vector<std::pair<int, int>> permutations;
    for (int i = 0; i < n; ++i) L[i][i] = 1;
    for (int k = 0; k < m; ++k) {
        int max = column_max(k);
        permute_rows(k, max);
        permutations.push_back({k, max});
        for (int j = k + 1; j < n; ++j) {
            double lambda = matrix[j][k] / matrix[k][k];
            row_transform(k, j, lambda);
            if (k == 0) L[j][k] = lambda;
            else buffer[j][k] = lambda;
        }
        if (k != 0) {
            _permute_rows(L, k, max);
            _permute_columns(L, k, max);
            for (int j = k + 1; j < n; ++j) {
                L[j][k] = buffer[j][k];
            }
        }
    }
    for (int i = 0; i < permutations.size(); ++i) {
        _permute_rows(matrix_old, permutations[i].first, permutations[i].second);
    }
    return {Matrix(L), permutations};
}

std::vector<double> Matrix::solve(std::vector<double> b)
{
    std::vector<std::vector<double>> first_matrix = this->get_matrix();
    Matrix mat(first_matrix);
    std::pair<Matrix, std::vector<std::pair<int, int>>> lu_decomposition = mat.LU_decomposition();
    for (auto perm: lu_decomposition.second) {
        _permute_rows(b, perm.first, perm.second);
    }
    std::vector<std::vector<double>> lower = lu_decomposition.first.get_matrix();
    int n = b.size();
    std::vector<double> z(n);
    z[0] = b[0];
    for (int i = 1; i < n; ++i) {
        z[i] = b[i];
        for (int j = 0; j < i; ++j) {
            z[i] -= lower[i][j] * z[j];
        }
    }
    std::vector<double> x(n);
    std::vector<std::vector<double>> upper = mat.get_matrix();
    x[n - 1] = z[n - 1] / upper[n - 1][n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = z[i] / upper[i][i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= (upper[i][j] * x[j]) / upper[i][i]; 
        }
    }
    return x;
}

std::vector<double> Matrix::solve3DiagMat(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> b_right)
{
    int n = a.size();
    std::vector<double> sol(n);
    std::vector<double> p(n);
    std::vector<double> q(n);
    p[0] = -c[0] / b[0];
    q[0] = b_right[0] / b[0];
    for (int i = 1; i < n; ++i) {
        p[i] = -c[i] / (b[i] + a[i] * p[i - 1]);
        q[i] = (b_right[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
    }
    sol[n - 1] = q[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        sol[i] = p[i] * sol[i + 1] + q[i];
    }
    return sol;
}

double Matrix::calc_det()
{
    std::pair<Matrix, std::vector<std::pair<int, int>>> lu = this->LU_decomposition();
    std::vector<std::vector<double>> lower = lu.first.get_matrix();
    std::vector<std::vector<double>> upper = this->get_matrix();
    int n = lower.size();
    double res = 1.0;
    for (int i = 0; i < n; ++i) {
        res *= lower[i][i] * upper[i][i];
    }
    return res;
}

std::vector<std::vector<double>> Matrix::back_matrix()
{
    std::vector<std::vector<double>> mat = this->get_matrix();
    int n = mat.size();
    std::vector<std::vector<double>> res(n, std::vector<double>(n));
    std::vector<double> id(n);
    for (int i = 0; i < n; ++i) {
        id[i] = 1.0;
        if (i > 0) id[i - 1] = 0.0;
        Matrix a(mat);
        std::vector<double> solution = a.solve(id);
        for (int j = 0; j < solution.size(); ++j) {
            res[j][i] = solution[j];
        }
    }
    return res;
}

std::vector<double> Matrix::simple_iterations(std::vector<double> b, double eps)
{
    int n = b.size();
    std::vector<std::vector<double>> matrix = this->matrix;
    std::vector<std::vector<double>> alpha(n, std::vector<double>(n));
    std::vector<double> beta(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            alpha[i][j] = - matrix[i][j] / matrix[i][i];
        }
        beta[i] = b[i] / matrix[i][i];
    }
    double q = calc_norm(alpha);
    std::vector<double> x_curr(n);
    std::vector<double> diff(n);
    std::vector<double> x_prev = beta;
    double x_norm = calc_norm(x_prev);
    double cur_eps = q / (1 - q) * x_norm;
    int iterations_count = 0;
    while (cur_eps > eps) {
        ++iterations_count;
        std::cout << "curr_eps=" << cur_eps << "\n";
        for (int i = 0; i < n; ++i) {
            //std::cout << "i=" << i << "\n";
            double sum = 0;
            //std::cout << "new sol\n";
            for (int j = 0; j < n; ++j) {
                //std::cout << i << " " << j << "\n";
                //std::cout << "calc sum\n";
                sum += alpha[i][j] * x_prev[j];
            }
            //std::cout << "here?\n";
            x_curr[i] = sum + beta[i];
        }
        //std::cout << "new sol\n";
        for (int i = 0; i < n; ++i) {
            diff[i] = x_prev[i] - x_curr[i];
        }
        x_prev = x_curr;
        cur_eps = q / (1 - q) * calc_norm(diff);
    }
    std::cout << "solution:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << x_curr[i] << " ";
    }
    std::cout << "iterations count: " << iterations_count << "\n";
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> Matrix::QR_decomposition()
{
    std::vector<std::vector<double>> cur_matrix = this->matrix;
    int n = cur_matrix.size();
    std::vector<std::vector<double>> Q(n, std::vector<double>(n));
    std::vector<std::vector<double>> R(n, std::vector<double>(n));
    R = cur_matrix;
    for (int i = 0; i < n; ++i) Q[i][i] = 1;
    for (int i = 0; i < n - 1; ++i) {
        std::vector<double> curr(n);
        std::vector<double> v(n);
        for (int j = 0; j < n; ++j) {
            curr[j] = cur_matrix[j][i];
        }
        double norm = euclidean_norm_k(curr, i);
        v[i] = cur_matrix[i][i] + sign(cur_matrix[i][i]) * norm;
        for (int k = i + 1; k < n; ++k) {
            v[k] = cur_matrix[k][i];
        }
        std::vector<std::vector<double>> h = calc_h_matrix(v);
        Q = dot(Q, h);
        cur_matrix = dot(h, cur_matrix);
        R = dot(h, R);
    }
    return {Q, R};

}

std::vector<double> Matrix::find_values_by_QR(double eps)
{
    Matrix cur_matrix = this->matrix;

    double cur_eps = under_diag_norm(cur_matrix.get_matrix());
    while (cur_eps > eps) {
        auto qr_pair = cur_matrix.QR_decomposition();
        cur_matrix = Matrix(dot(qr_pair.second, qr_pair.first));
        cur_eps = under_diag_norm(cur_matrix.get_matrix());
    }
    std::vector<std::vector<double>> res = cur_matrix.get_matrix();
    int n = res.size();
    std::vector<double> solution(n);
    for (int i = 0; i < n; ++i) {
        solution[i] = res[i][i];
    }
    return solution;
}

std::vector<double> Matrix::zeidel(std::vector<double> b, double eps)
{
    int n = b.size();
    std::vector<std::vector<double>> matrix = this->matrix;
    std::vector<std::vector<double>> alpha(n, std::vector<double>(n));
    std::vector<double> beta(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            alpha[i][j] = - matrix[i][j] / matrix[i][i];
        }
        beta[i] = b[i] / matrix[i][i];
    }
    double q = calc_norm(alpha);
    std::vector<double> x_curr(n);
    std::vector<double> diff(n);
    std::vector<double> x_prev = beta;
    double x_norm = calc_norm(x_prev);
    double cur_eps = q / (1 - q) * x_norm;
    int iterations_count = 0;
    while (cur_eps > eps) {
        std::vector<double> save_prev(n);
        ++iterations_count;
        //4std::cout << "curr_eps=" << cur_eps << "\n";
        for (int i = 0; i < n; ++i) {
            //std::cout << "i=" << i << "\n";
            double sum = 0;
            //std::cout << "new sol\n";
            for (int j = 0; j < n; ++j) {
                //std::cout << i << " " << j << "\n";
                //std::cout << "calc sum\n";
                sum += alpha[i][j] * x_prev[j];
            }
            //std::cout << "here?\n";
            x_curr[i] = sum + beta[i];
            save_prev[i] = x_prev[i];
            x_prev[i] = x_curr[i];
        }
        //std::cout << "new sol\n";
        for (int i = 0; i < n; ++i) {
            diff[i] = save_prev[i] - x_curr[i];
        }
        //x_prev = x_curr;
        cur_eps = q / (1 - q) * calc_norm(diff);
    }
    std::cout << "solution:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << x_curr[i] << " ";
    }
    std::cout << "iterations count: " << iterations_count << "\n";
}

std::pair<std::vector<double>, std::vector<std::vector<double>>> Matrix::rotate_machine(double eps)
{
    std::vector<std::vector<double>> cur_matrix = this->matrix;
    int n = cur_matrix.size();
    std::vector<std::vector<double>> u_result(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) u_result[i][i] = 1;
    double cur_eps = fram_norm(cur_matrix);
    //std::cout << "cur_eps=" << cur_eps << "\n";
    int i = 0;
    while (cur_eps > eps) {
        //if (i > 6) break;
        ++i;
        //std::cout << "cur_eps=" << cur_eps << "\n";
        auto result = matrix_max(cur_matrix);
        //double max = result.first;
        int row_index = result.second.first;
        int column_index = result.second.second;
        double max = cur_matrix[row_index][column_index];
        double cur_phi;
        if (cur_matrix[row_index][row_index] == cur_matrix[column_index][column_index]) cur_phi = 3.14 / 4; 
        else cur_phi = 0.5 * atan(2 * max / (cur_matrix[row_index][row_index] - cur_matrix[column_index][column_index]));
        //std::cout << "indexes = (" << row_index + 1 << ", " << column_index + 1 << ")\n";
        //std::cout << "compute new phi:\n";
        //std::cout << "arctan(2 * " << max << "/(" << matrix[row_index][row_index] << "-" << matrix[column_index][column_index] << "))\n";
        //std::cout << "phi=" << cur_phi << "\n";
        //std::cout << "cur_matrix:\n";
        //print(cur_matrix);
        std::vector<std::vector<double>> u = create_u_matrix(n, row_index, column_index, cur_phi);
        //if (i == 1) u_result = u;
        u_result = dot(u_result, u);
        std::cout << "cur v:\n";
        print(u_result);
        //u_result = dot(u, u_result);
        //std::cout << "u matrix:\n";
        //print(u);
        std::vector<std::vector<double>> u_tranpose = u;

        u_tranpose[row_index][column_index] *= -1; u_tranpose[column_index][row_index] *= -1;
        cur_matrix = dot(u_tranpose, dot(cur_matrix, u));
        cur_eps = fram_norm(cur_matrix);
    }
    //std::cout << "matrix\n";
    //print(cur_matrix);
    //std::cout << "u_result:\n";
    //print(u_result);
    std::vector<double> sol(n);
    for (int i = 0; i < n; ++i) {
        sol[i] = cur_matrix[i][i];
    }
    return {sol, u_result};
}