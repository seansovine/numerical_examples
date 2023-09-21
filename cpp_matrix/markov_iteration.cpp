#include <iostream>
#include "matrix_lib/matrix_lib.hpp"

int main()
{
	std::cout << std::fixed << std::setprecision(PRECISION);
	std::string header{"Markov chain steady-state iteration:"};
	std::cout << header << std::endl
			  << std::endl;

	Matrix<double> m{2, 2};
	m(0, 0) = 0.45;
	m(0, 1) = 0.55;
	m(1, 0) = 0.4;
	m(1, 1) = 0.6; // Tends to enter state 1 and stay there.

	std::cout << "Transition matrix m =" << std::endl
			  << std::string(m) << std::endl
			  << std::endl;
	std::cout << "Inf norm of m is: " << infNorm(m) << std::endl
			  << std::endl;

	double tolerance = 1.0E-12;
	Matrix<double> curr{m};
	Matrix<double> prev{m};
	unsigned num_iter = 0;

	for (unsigned c = 0;; c++)
	{
		prev = std::move(curr);
		curr = prev * m;

		Matrix<double> delta = curr + (-1.0 * prev);
		double norm_delta = infNorm(delta);
		if (norm_delta < tolerance)
		{
			num_iter = c + 1;
			break;
		}
	}

	std::cout << "Approximate convergence after " << num_iter << " iterations." << std::endl;
	std::cout << "Approximate steady state: " << std::endl
			  << std::string(curr) << std::endl;
}
