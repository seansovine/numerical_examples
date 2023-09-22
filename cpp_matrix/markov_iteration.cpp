#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

int main() {
  std::cout << std::fixed << std::setprecision(PRECISION);
  std::string header{"Markov chain steady-state iteration:"};
  std::cout << header << std::endl << std::endl;

  matrix::Matrix<double> m{{0.45, 0.55}, {0.4, 0.6}};
  // Tends to enter state 1 and stay there.

  std::cout << "Transition matrix m =" << std::endl
            << std::string(m) << std::endl
            << std::endl;
  std::cout << "Inf norm of m is: " << matrix::infNorm(m) << std::endl
            << std::endl;

  double tolerance = 1.0E-12;
  matrix::Matrix<double> curr{m};
  matrix::Matrix<double> prev{m};
  unsigned num_iter = 0;

  for (unsigned c = 0;; c++) {
    prev = std::move(curr);
    curr = prev * m;

    matrix::Matrix<double> delta = curr + (-1.0 * prev);
    double norm_delta = matrix::infNorm(delta);
    if (norm_delta < tolerance) {
      num_iter = c + 1;
      break;
    }
  }

  std::cout << std::scientific
            << "Convergence stopping threshold: " << tolerance
            << std::defaultfloat << std::endl;
  std::cout << "Approximate convergence after " << num_iter << " iterations."
            << std::endl
            << std::endl;
  std::cout << "Approximate 1 * π for steady state π: " << std::endl
            << std::string(curr) << std::endl;
}
