#include <eigen-3.3.7/Eigen/Dense>
#include <iostream>

using namespace Eigen;

void ludcmp(MatrixXd& A, MatrixXd& L, MatrixXd& U)
{
    int n = A.rows();

    for (int j = 0; j < n; ++j) {

        for (int i = 0; i <= j; ++i) {
            U(i, j) = A(i, j);
            int k = 0;
            for (k = 0; k < i; ++k) {
                U(i, j) -= L(i, k) * U(k, j);
            }
            U(i, j) /= L(i, k);
        }

        for (int i = j + 1; i < n; ++i) {
            L(i, j) = A(i, j);
            int k = 0;
            for (k = 0; k < j; ++k) {
                L(i, j) -= L(i, k) * U(k, j);
            }
            L(i, j) /= U(k, j);
        }
    }
}

int main()
{
    MatrixXd L(3, 3);
    MatrixXd U(3, 3);
    MatrixXd A(3, 3);

    L << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    U << L;

    A << 1, 1, 1,
         4, 3, -1,
         3, 5, 3;

    ludcmp(A, L, U);

    std::cout << L << std::endl;
    std::cout << U << std::endl;

    return 0;
}
