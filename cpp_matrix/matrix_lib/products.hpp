#include "matrix.hpp"
#include "vector.hpp"

/* ---- Matrix-Matrix product. ---- */

template <typename T>
T prodIK(const Matrix<T> &lhs, const Matrix<T> &rhs, unsigned i, unsigned k)
{
	T result{};
	for (unsigned j = 0; j < lhs.cols; j++)
		result += lhs(i, j) * rhs(j, k);
	return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
	if (lhs.cols != rhs.rows)
		throw std::domain_error("LHS #cols must match RHS #rows.");

	Matrix<T> result{lhs.rows, rhs.cols};

	// TODO: This is naive; do this more efficiently.
	for (unsigned i = 0; i < lhs.rows; i++)
		for (unsigned k = 0; k < rhs.cols; k++)
			result(i, k) = prodIK(lhs, rhs, i, k);

	return result;
}
