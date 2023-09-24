# Matrix Class Example

This project contains a basic C++ linear algebra library,
written for learning purposes.
I will use this library in some other numerical example projects
that I will add to this repository.
The current version is not complete or fully optimized for efficiency, but I have
made some effort to avoid unnecessary object copying.

## Examples

The main folder contains a few test files, including these:

The file `matrix_test.cpp` demonstrates the defined operations on simple examples.

The file `markov_iteration.cpp` uses this library to approximate $\lim_{k\rightarrow\infty}m^k$, where
$m$ is a stochastic transition matrix. If this limit exists, it is equal to $\mathbf{1}\cdot \pi$,
where $\pi$ is the steady-state distribution of the Markov chain with transition matrix $m$ and $\mathbf{1}$ is a column vector of $1$'s. See [Wikipedia: Markov chain](https://en.wikipedia.org/wiki/Markov_chain#Time-homogeneous_Markov_chain_with_a_finite_state_space).

## Building and running

There is a simple shell script to build and run test scripts using the Makefile in this directory:

```shell
chmod +x bld
./bld <test filename w/o extension> [build|run|run_only]
```

## Features

_Classes:_

- Has a Matrix class template representing an $m x n$ matrix with scalar type T, implementing the parentheses operator.
- Has a Vector subclass representing a column matrix, implementing the subscript operator.
- A `MatrixFunctor<T>` class template that takes a regular function `f` mapping a `T` to a `T` and returns an object that
  acts like a function `F` that maps a `Matrix<T>` to a `Matrix<T>` by applying `f` component-wise.
  Like a very basic version of NumPy ufuncs.

_Operations:_

- Implements scalar multiplication, matrix-matrix addition and multiplication, and the matrix $\infty$-norm.
- Implements explicit Matrix to string conversion.

_Algorithms:_

- A very basic LU factorization.
- A very basic solver for the square, full-rank linear system $Ax= b$, using the $LU$ factorization.

## Design decisions

Here are some early decisions that have shaped the design:

- Each matrix instance has constant shape.
- Operations return new objects.
  - This is necessary for arbitrary matrix-matrix or matrix-vector products.
  - It seems natural to be consistent for scalar products.

Eventually we can implement a basic lazy evaluation scheme for the operations, in which each operation returns an expression template.

## Further ideas

- Implement more operations:
  - Matrix transpose: could be done with a derived class overriding access.
  - Matrix-vector product (just need to handle return type).
  - Vector-vector dot product.
- Use the [Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) for handling inheritance.
- Use [expression templates](https://en.wikipedia.org/wiki/Expression_templates) for matrix operations.
- Optimize the matrix multiplication -- maybe use BLAS and LAPACK.
- Consider casting scalars, e.g., to allow integer matrix x double matrix.
