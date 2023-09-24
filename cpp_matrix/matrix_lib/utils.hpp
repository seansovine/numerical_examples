#include "matrix.hpp"
#include "vector.hpp"

#ifndef UTILS_H
#define UTILS_H

namespace matrix {

/* ---- Norms ---- */

template <typename T> double infNorm(const Matrix<T> &m) {
  double norm = 0.0;
  for (unsigned i = 0; i < m.rows; i++) {
    double row_sum = 0;
    for (unsigned j = 0; j < m.cols; j++) {
      double d_val = static_cast<double>(m(i, j));
      row_sum += std::abs(d_val);
    }
    norm = std::max(norm, row_sum);
  }

  return norm;
}

/* ---- Utility classes. ---- */

namespace internal {

template <typename T> using f_ptr_t = T (*)(const T &);

}

template <typename T> class MatrixFunctor {
  internal::f_ptr_t<T> func;

public:
  MatrixFunctor(internal::f_ptr_t<T> func) : func{func} {};

  Matrix<T> operator()(const Matrix<T> &m) {
    Matrix<T> result{m.rows, m.cols};
    for (unsigned i = 0; i < m.rows; i++)
      for (unsigned j = 0; j < m.cols; j++)
        result(i, j) = func(m(i, j));

    return result;
  }
};

/* ---- Special Matrix constructors. ---- */

template <typename T> Matrix<T> ident(const unsigned int &n) {
  Matrix<T> I{n, n};
  for (unsigned i = 0; i < n; i++) {
    I(i, i) = 1;
  }
  return I;
}

} // namespace matrix

#endif
