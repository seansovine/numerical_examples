#include <iostream>
#include <iomanip>
#include <sstream>

template <typename T>
class Matrix
{
	// Store row-major.
	T *data;
	const unsigned rows;
	const unsigned cols;

public:
	Matrix(const unsigned &rows, const unsigned &cols) : rows{rows}, cols{cols}
	{
		const unsigned int num_entries = rows * cols;
		data = new T[num_entries]{};
	}

	~Matrix()
	{
		delete[] data;
	}

	// See: https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op
	T &operator()(unsigned row, unsigned col);		// To modify the value.
	T operator()(unsigned row, unsigned col) const; // For use with const Matrixes.

	explicit operator std::string() const;
};

/* ---- Implementation. ---- */

template <typename T>
T &Matrix<T>::operator()(unsigned row, unsigned col)
{
	// Row-major access.
	return data[col + row * cols];
}

template <typename T>
T Matrix<T>::operator()(unsigned row, unsigned col) const
{
	// Row-major access.
	return data[col + row * cols];
}

template <typename T>
Matrix<T>::operator std::string() const
{
	// Compute max width for alignment.

	unsigned max_width = 0; // Could do per-column.
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			const T &entry = (*this)(i, j);
			std::string as_string = std::to_string(entry);
			unsigned width = static_cast<unsigned>(as_string.length());
			max_width = (width > max_width) ? width : max_width;
		}
	}

	// Build string.

	std::stringstream oss{};
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			const T &entry = (*this)(i, j);
			oss << std::setw(max_width + 1) << entry;
		}
		if (i < rows - 1)
			oss << std::endl;
	}

	return oss.str();
}

/* ---- Main function. ---- */

int main()
{
	Matrix<int> m{2, 2};

	// 2 x 2 identity matrix.

	m(0, 0) = 1;
	m(0, 1) = 1000;
	m(1, 0) = 25;
	m(1, 1) = 1;

	std::cout << std::endl
			  << "Original matrix:" << std::endl
			  << std::endl
			  << std::string(m) << std::endl;

	int &entry = m(0, 1);
	entry = 0;
	m(1, 0) = 0;

	std::cout << std::endl
			  << "Modified matrix:" << std::endl
			  << std::endl
			  << std::string(m) << std::endl;

	return EXIT_SUCCESS;
}
