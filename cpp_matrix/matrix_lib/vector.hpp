#include "matrix.hpp"

/* ---- Forward declaration. ---- */

template <typename T>
class Vector;

template <typename T>
Vector<T> operator*(const T &, const Vector<T> &);

#ifndef VECTOR_IMPL
#define VECTOR_IMPL

/* ---- Vector declaration. ---- */

template <typename T>
class Vector : public Matrix<T>
{
public:
	Vector(const unsigned &);
	Vector(const Matrix<T> &);
	Vector(const Vector<T> &);
	Vector(Matrix<T> &&);
	Vector(Vector<T> &&);

	T &operator[](const unsigned &i);
	T operator[](const unsigned &i) const;

	template <typename _>
	friend Vector<T> operator*(const T &a, const Vector<T> &m);
};

/* ---- Vector implementation. ---- */

template <typename T>
T &Vector<T>::operator[](const unsigned &i)
{
	return (*this)(i, 0);
}

template <typename T>
T Vector<T>::operator[](const unsigned &i) const
{
	return (*this)(i, 0);
}

// Constructors. (Base desctructor is used.)

template <typename T>
Vector<T>::Vector(const unsigned &rows) : Matrix<T>(rows, 1){};

template <typename T>
Vector<T>::Vector(const Matrix<T> &mat) : Matrix<T>(mat){};

template <typename T>
Vector<T>::Vector(const Vector<T> &other) : Matrix<T>(other){};

template <typename T>
Vector<T>::Vector(Matrix<T> &&other) : Matrix<T>(other){};

template <typename T>
Vector<T>::Vector(Vector<T> &&other) : Matrix<T>(other){};

#endif
