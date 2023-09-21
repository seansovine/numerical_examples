#include <iostream>
#include "matrix.h"

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

	Vector<double> v(2);
	v[0] = 0.1;
	v[1] = 1.2;

	std::cout << std::endl
			  << "Vector:" << std::endl
			  << std::endl
			  << std::string(v) << std::endl;

	return EXIT_SUCCESS;
}
