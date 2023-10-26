#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

int main() {
  // clang-format off
  matrix::Matrix<double> m{
    {0.4, 0.5, 0.1},
    {0.3, 0.3, 0.4},
    {0.1, 0.2, 0.7}
  };
  // clang-format on

  std::cout << "Matrix m =" << std::endl
            << std::string(m) << std::endl
            << std::endl;

  matrix::Vector<double> v{2, 1, 1};

  std::cout << "Vector v =" << std::endl
            << std::string(v) << std::endl
            << std::endl;

  matrix::Vector<double> prod = m * v;

  std::cout << "Product m * v=" << std::endl
            << std::string(prod) << std::endl
            << std::endl;
}
