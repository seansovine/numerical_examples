# Matrix Class Example

In this project we implement basic matrix and vector class templates
and define the basic operations for matrix and vector objects.
An eventual goal is to use this library in the implementation
of a basic but fairly general differential equation solver.
The current version is not optimized much for efficiency, except for
some effort to avoid unnecessary object copying.

## Examples

The file `matrix_test.cpp` demonstrates the defined operations on simple examples.

The file `markov_iteration.cpp` uses this library to approximate $\lim_{k\rightarrow\infty}m^k$, where
$m$ is a stochastic transition matrix. If this limit exists, it is equal to $\mathbf{1}\cdot \pi$,
where $\pi$ is the steady-state distribution of the Markov chain with transition matrix $m$ and $\mathbf{1}$ is a column vector of $1$'s. See [Markov chain](https://en.wikipedia.org/wiki/Markov_chain#Time-homogeneous_Markov_chain_with_a_finite_state_space).

## Building and running

There is a simple shell script to build and run test scripts using the Makefile in this directory:

```shell
chmod +x bld
./bld <filename w/o extension> [run|run_only]
```

## Features

- Has a Matrix class template representing an $m x n$ matrix with scalar type T, implementing the parentheses operator.
- Has a Vector subclass representing a column matrix, implementing the subscript operator.
- Implements scalar multiplication, matrix-matrix addition and multiplication, and the matrix $\infty$-norm.
- Implements explicit Matrix to string conversion.

## Design decisions

Here are some early decisions that have shaped the design:

- Each matrix instance has constant shape.
- Operations return new objects.
  - This is necessary for arbitrary matrix-matrix or matrix-vector products.
  - It seems natural to be consistent for scalar products.

Eventually we can implement a basic lazy evaluation scheme for the operations, in which each operation returns an expression template.

## Further ideas

First:

- Implement more operations:
  - Matrix transpose: could be done with a derived class overriding access.
  - Matrix-vector product (just need to handle return type).
  - Vector-vector dot product.
- Use the Matrix class to implement a simple numerical ODE solver.
- Use the [Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) for handling inheritance.
- Use [expression templates](https://en.wikipedia.org/wiki/Expression_templates) for arithmetic operations.
- Optimize the matrix multiplication -- maybe use BLAS or LAPACK.

And then, maybe:

- Add more convenient way to initialize Matrix, maybe using 2d-array literals.
- Consider casting scalars, e.g., to allow integer matrix x double matrix.
