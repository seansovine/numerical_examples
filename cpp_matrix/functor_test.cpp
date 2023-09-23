#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

int f(const int &x) { return 2 * (x * x) - 1; }

int main() {
  // clang-format off
  matrix::Matrix<int> m{
    {1,  2},
    {25, 4},
    {7, -3}
  };
  // clang-format on
  // 2 x 2 matrix.

  std::cout << "m = " << std::endl << std::string(m) << std::endl << std::endl;
  std::cout << "inf norm of m is: " << matrix::infNorm(m) << std::endl
            << std::endl;

  matrix::MatrixFunctor<int> F{&f};

  matrix::Matrix<int> F_of_m = F(m);

  std::cout << "F(m) = " << std::endl
            << std::string(F_of_m) << std::endl
            << std::endl;
  std::cout << "inf norm of F(m) is: " << matrix::infNorm(F_of_m) << std::endl
            << std::endl;
}
