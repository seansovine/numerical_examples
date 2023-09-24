#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

/**
 *  Testing out LU w/ partial pivot and accompanying solver.
 */

using matrix::Matrix;

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

  // Do factorization.

  std::cout << "Performing factorization to obtain (M, p) from A." << std::endl
            << std::endl;

  std::pair<Matrix<double>, Matrix<unsigned>> factorization =
      matrix::LUPartialPivot(A);
  Matrix<double> M = std::move(factorization.first);
  Matrix<unsigned> p = std::move(factorization.second);

  std::cout << "Matrix M = " << std::endl
            << std::string(M) << std::endl
            << std::endl;
  std::cout << "Successive permutation vector p = " << std::endl
            << std::string(p) << std::endl
            << std::endl;
}
