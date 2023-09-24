#include "matrix.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace matrix {

/**
 *  Most basic LU factorization.
 *  Later we will improve it; first with pivoting.
 *
 *  We could also define higher-level functions to use.
 *  For example, we could define submatrix views that allow
 *  access by reference to submatrices of a given Matrix
 *  object, perhaps as special derived classes of Matrix.
 */

template <typename T>
std::pair<Matrix<T>, Matrix<T>> LUFactor(const Matrix<T> &A) {
  assert(A.rows == A.cols);
  unsigned int n = A.rows;

  Matrix<T> L = ident<T>(n);
  Matrix<T> U{A};

  // Do the factorization.
  for (unsigned k = 0; k < n - 1; k++) {
    if (U(k, k) == 0)
      throw std::domain_error(
          "This LU factorization doesn't handle singular matrices.");

    for (unsigned l = k + 1; l < n; l++) {
      T tau = U(l, k) / U(k, k);
      L(l, k) = tau;

      for (unsigned r = k; r < n; r++)
        U(l, r) = U(l, r) - (U(k, r) * tau);
    }
  }

  return std::pair<Matrix<T>, Matrix<T>>{L, U};
}

} // namespace matrix
