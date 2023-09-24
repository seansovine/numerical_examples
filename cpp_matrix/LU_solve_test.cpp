#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

/**
 *  First example using LU w/ pivoting to solve a system Ax = b.
 */

using matrix::Matrix;

template <typename T>
std::pair<Matrix<T>, Matrix<T>> LUFactor(const Matrix<T> &);

int main() {
  // clang-format off
  Matrix<double> A{
    {0.1, 5,   4  },
    {1,   3,   2.3},
    {23,  0.1, 2  }
  };
  // clang-format on

  std::cout << "Matrix A = " << std::endl
            << std::string(A) << std::endl
            << std::endl;

  // clang-format off
  Matrix<double> b{
    {7  },
    {0.2},
    {29 }
  };
  // clang-format on

  std::pair<Matrix<double>, Matrix<double>> factorization = matrix::LUFactor(A);
  Matrix<double> L = std::move(factorization.first);
  Matrix<double> U = std::move(factorization.second);

  std::cout << "Matrix L = " << std::endl
            << std::string(L) << std::endl
            << std::endl;
  std::cout << "Matrix U = " << std::endl
            << std::string(U) << std::endl
            << std::endl;

  Matrix<double> LU = L * U;
  std::cout << "Verify, L*U = " << std::endl
            << std::string(LU) << std::endl
            << std::endl;

  std::cout << "Matrix b = " << std::endl
            << std::string(b) << std::endl
            << std::endl;

  Matrix<double> x = matrix::linear_solve(A, b);
  std::cout << "Solution x to Ax = b is:" << std::endl
            << std::string(x) << std::endl
            << std::endl;

  Matrix<double> Ax = A * x;
  std::cout << "Verifying solution: Ax =" << std::endl
            << std::string(Ax) << std::endl
            << std::endl;
}
