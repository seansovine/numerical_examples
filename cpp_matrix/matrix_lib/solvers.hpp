#include "matrix.hpp"
#include "vector.hpp"

namespace matrix {

namespace internal {

template <typename T> Matrix<T> forward_sub(Matrix<T> L, Matrix<T> b) {
  assert(b.cols = 1);
  assert(L.rows == b.rows);
  Matrix<T> v{b.rows, 1};

  // Compute.

  return v;
}

template <typename T> Matrix<T> back_sub(Matrix<T> U, Matrix<T> v) {
  assert(v.cols = 1);
  assert(U.rows == v.rows);
  Matrix<T> x{v.rows, 1};

  // Compute.

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

  std::pair<Matrix<T>, Matrix<T>> factorization = matrix::LUFactor(A);
  Matrix<T> L = std::move(factorization.first);
  Matrix<T> U = std::move(factorization.second);

  // Solve Lv = b with forward substitution.
  Matrix<T> v = internal::forward_sub(L, b);

  // Solve Ux = v with back substitution.
  Matrix<T> x = internal::back_sub(U, v);

  return x;
}

} // namespace matrix
