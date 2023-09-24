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
  };
  // clang-format on

  std::pair<Matrix<double>, Matrix<double>> factorization = matrix::LUFactor(A);
  Matrix<double> L = factorization.first;
  Matrix<double> U = factorization.second;

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
}
