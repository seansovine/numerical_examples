#include "matrix.hpp"
#include "vector.hpp"

namespace matrix {

namespace internal {

template <typename T> Matrix<T> forward_sub(Matrix<T> L, Matrix<T> b) {
  assert(b.cols == 1);
  assert(L.rows == b.rows);
  Matrix<T> v{b.rows, 1};

  for (unsigned i = 0; i < L.rows; i++) {
    T t = b(i, 0);
    for (unsigned l = 0; l < i; l++) {
      t -= L(i, l) * v(l, 0);
    }
    v(i, 0) = t / L(i, i);
  }

  return v;
}

template <typename T> Matrix<T> back_sub(Matrix<T> U, Matrix<T> v) {
  assert(v.cols == 1);
  assert(U.rows == v.rows);

  unsigned n = U.rows;
  Matrix<T> x{v.rows, 1};

  for (int i = n - 1; i >= 0; --i) {
    T t = v(i, 0);
    for (unsigned l = i + 1; l < n; l++) {
      t -= U(i, l) * x(l, 0);
    }
    x(i, 0) = t / U(i, i);
  }

  return x;
}

} // namespace internal

/**
 *  Basic solver for equation Ax = b,
 *  where A is square and b is a column
 *  matrix.
 */

template <typename T>
Matrix<T> linear_solve(const Matrix<T> &A, const Matrix<T> &b) {
  assert(b.cols == 1);
  assert(A.rows == b.rows);
  assert(A.rows == A.cols);

  std::pair<Matrix<T>, Matrix<T>> factorization = matrix::LUFactor(A);
  Matrix<T> L = std::move(factorization.first);
  Matrix<T> U = std::move(factorization.second);

  // Solve Lv = b with forward substitution.
  Matrix<T> v = internal::forward_sub(L, b);

  // Solve Ux = v with back substitution.
  Matrix<T> x = internal::back_sub(U, v);

  return x;
}

/**
 *  Partial pivoting algorithm from Golub and Van Loan.
 */

template <typename T>
Matrix<T> solve_partial_pivot(const Matrix<T> &A, const Matrix<T> &b) {
  assert(b.cols == 1);
  assert(A.rows == b.rows);
  assert(A.rows == A.cols);
  unsigned n = A.rows;

  std::pair<Matrix<double>, Matrix<unsigned>> factorization =
      matrix::LUPartialPivot(A);
  Matrix<double> M = std::move(factorization.first);
  Matrix<unsigned> p = std::move(factorization.second);

  Matrix<T> y{b};
  for (unsigned k = 0; k < n - 1; k++) {
    // Apply permutation to RHS.
    T tmp = y(p(k, 0), 0);
    y(p(k, 0), 0) = y(k, 0);
    y(k, 0) = tmp;
    // TODO: Use Vector class here for clarity.

    // Apply row op to RHS.
    for (unsigned l = k + 1; l < n; l++) {
      y(l, 0) = y(l, 0) - y(k, 0) * M(l, k);
    }
  }

  // Check for singular matrix.
  for (unsigned k = 0; k < n; k++) {
    if (M(k, k) == 0)
      throw std::domain_error(
          "Matrix is A singular; cannot guarantee solution exists.");
  }

  Matrix<T> x = internal::back_sub(M, y);
  return x;
}

} // namespace matrix
