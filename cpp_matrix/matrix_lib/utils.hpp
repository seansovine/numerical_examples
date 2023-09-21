#include "matrix.hpp"
#include "vector.hpp"

/* ---- Norms ---- */

template <typename T>
double infNorm(const Matrix<T> &m)
{
	double norm = 0.0;
	for (unsigned i = 0; i < m.rows; i++)
		for (unsigned j = 0; j < m.cols; j++)
		{
			double d_val = static_cast<double>(m(i, j));
			norm = std::max(norm, d_val);
		}
	return norm;
}
