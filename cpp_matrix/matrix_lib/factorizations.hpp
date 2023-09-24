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

/**
 *  Applies the LU w/ partial pivoting algorithm of Golub and Van Loan,
 *  pg. 112. Returns a pair of matrices that can be used to solve
 *  the system Ax = b.
 *
 *  Does not explicitly return L of A = LU, but it can be obtained from
 *  return value (see Golub and Van Loan).
 */

namespace internal {

template <typename T> unsigned next_row_(const Matrix<T> &m, unsigned step) {
  unsigned next = step;
  T max_val = m(step, step);

  for (unsigned i = step; i < m.rows; i++) {
    T abs_val = std::abs(m(i, step));
    if (abs_val > max_val) {
      max_val = abs_val;
      next = i;
    }
  }
  return next;
} // Return index of largest entry in m(k:n, k).

template <typename T>
void exchange_row_tails_(Matrix<T> &m, unsigned k, unsigned n) {
  for (unsigned j = k; j < m.cols; j++) {
    T tmp = m(n, j);
    m(n, j) = m(k, j);
    m(k, j) = tmp;
  }
} // Swap tails of rows in-place.

} // namespace internal

template <typename T>
std::pair<Matrix<T>, Matrix<unsigned>> LUPartialPivot(const Matrix<T> &A) {
  assert(A.rows == A.cols);
  unsigned int n = A.rows;

  Matrix<unsigned> p{n - 1, 1};
  Matrix<T> M{A};

  // Do the factorization.
  for (unsigned k = 0; k < n - 1; k++) {
    p(k, 0) = internal::next_row_(M, k);
    internal::exchange_row_tails_(M, k, p(k, 0));

    if (M(k, k) != 0) {
      for (unsigned l = k + 1; l < n; l++) {
        M(l, k) = M(l, k) / M(k, k);
      }
      for (unsigned l = k + 1; l < n; l++) {
        for (unsigned j = k + 1; j < n; j++) {
          M(l, j) = M(l, j) - M(l, k) * M(k, j);
        }
      }
    }
  }

  return std::pair<Matrix<T>, Matrix<unsigned>>{M, p};
}

} // namespace matrix
