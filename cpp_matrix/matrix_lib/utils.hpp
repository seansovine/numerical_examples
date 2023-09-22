#include "matrix.hpp"
#include "vector.hpp"

namespace matrix {

/* ---- Norms ---- */

template <typename T> double infNorm(const Matrix<T> &m) {
  double norm = 0.0;
  for (unsigned i = 0; i < m.rows; i++)
    for (unsigned j = 0; j < m.cols; j++) {
      double d_val = static_cast<double>(m(i, j));
      norm = std::max(norm, std::abs(d_val));
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

} // namespace matrix
