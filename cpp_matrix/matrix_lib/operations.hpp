#include "matrix.hpp"
#include "vector.hpp"

/* ---- Scalar products. ---- */

template <typename T>
Matrix<T> operator*(const T &a, const Matrix<T> &m)
{
	Matrix<T> result{m.rows, m.cols};
	for (unsigned i = 0; i < m.rows; i++)
	{
		for (unsigned j = 0; j < m.cols; j++)
		{
			result(i, j) = a * m(i, j);
		}
	}
	return result; // Returns new Matrix object.
}

template <typename T>
Vector<T> operator*(const T &a, const Vector<T> &m)
{
	Matrix<T> mat{m};
	Matrix<T> result = a * mat;
	return static_cast<Vector<T>>(std::move(result));
}

/* ---- Matrix-Matrix operations. ---- */

template <typename T>
T prodIK_(const Matrix<T> &lhs, const Matrix<T> &rhs, unsigned i, unsigned k)
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
	for (unsigned i = 0; i < lhs.rows; i++)
		for (unsigned k = 0; k < rhs.cols; k++)
			result(i, k) = prodIK_(lhs, rhs, i, k);

	return result;
} // Basic algorithm.

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
	if (lhs.cols != rhs.cols || lhs.rows != rhs.rows)
		throw std::domain_error("Dimensions must match to add matrices.");

	Matrix<T> result{lhs.rows, rhs.cols};
	for (unsigned i = 0; i < lhs.rows; i++)
		for (unsigned j = 0; j < rhs.cols; j++)
			result(i, j) = lhs(i, j) + rhs(i, j);

	return result;
}
