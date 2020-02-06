#include <iostream>
#include <eigen-3.3.7/Eigen/Dense>

using namespace Eigen;

template<class T>
void swap(T& A, int i, int j) {
    int n = A.cols();
    for (int l = 0; l < n; ++l)
    {
        double temp = A(i, l);
        A(i, l) = A(j, l);
        A(j, l) = temp;
    }
}

void gauss_elim(MatrixXd& A, VectorXd& b, VectorXd& x)
{
    int n = A.rows();
    MatrixXd Ab(n, n + 1);
    Ab << A, b;

    for (int k = 0; k < n; ++k)
    {
        double big = Ab(k,k);
        int irow = k;
        
        //Loop of the search for a pivot element
        for (int i = k + 1; i < n; ++i)
        {
            if (Ab(i, k) > big)
            {
                big = Ab(i, k);
                irow = i;
            }
        }

        //We now have the pivot element, so interchange the rows, if needed
        //to put the pivot element on the diagonal.
        if (irow != k)
        {
            swap<MatrixXd>(Ab, irow, k);
        }

        double pivot = Ab(k, k);
        double pivinv = 1.0 / pivot;

        //Divide the row, so that we have 1.0 in the pivot element
        Ab(k, k) = 1.0;
        for (int l = k+1; l < n + 1; ++l) Ab(k, l) *= pivinv;

        //Next we reduce the rows
        for (int i = k + 1; i < n; ++i)
        {
            double factor = Ab(i, k);
            for (int j = k; j < n + 1; ++j)
            {
                Ab(i, j) -= factor * Ab(k, j);
            }
        }
    }

    //Solve Ax=b for an upper triangular matrix A
    for (int i = n - 1; i >= 0; --i) {
        x(i) = Ab(i,n);
        for (int j = i + 1; j < n; ++j)
        {
            x(i) -= Ab(i, j) * x(j);
        }
        x(i) /= Ab(i, i);
    }
}

int main() {
    MatrixXd A(3, 3);
    A << 1, 1, 1,
        4, 3, -1,
        3, 5, 3;

    VectorXd b(3);
    b << 1, 6, 4;

    VectorXd x(3);

    gauss_elim(A, b, x);

    std::cout << x;
    return 0;
}