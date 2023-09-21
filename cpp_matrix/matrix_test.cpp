#include <iostream>
#include "matrix_lib/matrix_lib.hpp"

int main()
{
	Matrix<int> m{2, 2};

	// 2 x 2 matrix.

	m(0, 0) = 1;
	m(0, 1) = 1000;
	m(1, 0) = 25;
	m(1, 1) = 1;

	std::cout << std::endl
			  << "Original matrix:"
			  << std::endl
			  << std::string(m) << std::endl;

	// Modify to identity matrix.

	int &entry = m(0, 1);
	entry = 0;
	m(1, 0) = 0;

	Matrix<int> sProdM = 247 * m;
	// Assignment move (C++ <17) or elide copy (for C++ >=17).

	std::cout << std::endl
			  << "Modified matrix:"
			  << std::endl
			  << std::string(sProdM) << std::endl;

	Vector<double> v(2);
	v[0] = 0.1;
	v[1] = 1.2;

	Vector<double> sProdV = 2.0 * v;

	std::cout << std::endl
			  << "Vector:"
			  << std::endl
			  << std::string(sProdV) << std::endl;

	m(0, 0) = 2;
	m(1, 1) = 3;
	Matrix<int> product = m * m;

	std::cout << std::endl
			  << "Product m * m:"
			  << std::endl
			  << std::string(product) << std::endl;

	return EXIT_SUCCESS;
}
