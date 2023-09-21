# Matrix Class Example

In this project we implement a basic matrix class template
and define some of its operations.

The purpose of this project is hands-on learning. I'm not sure how much more I'll put into this
particular project, but it has been a great learning experience to work on it.

An eventual goal is to use this library as part of the implementation
of a basic, yet fairly general, differential equation solver, also just for the sake of learning.

## Features

- Has a Matrix class template representing an $m x n$ matrix with scalar type T, implementing the parentheses operator.
- Has a Vector subclass representing a column matrix, implementing the subscript operator.
- Implements scalar and matrix-matrix multiplication.

## Design Decisions

Here are some early decisions that have shaped the design:

- Each matrix instance has constant shape.
- Operations return new objects.
  - This is necessary for arbitrary matrix-matrix or matrix-vector products; it seems natural for scalar.
  - Eventually we can implement a basic lazy evaluation scheme for these, returning an expression template.

## To Do

- Improve string output formatting.
- Implement more operations:
  - Matrix transpose: could be done with a derived class overriding access.
  - Matrix-vector product (just need to handle return type).
  - Vector-vector dot product.
- Use the Matrix class to implement a simple numerical ODE solver.
- Use the Curiously Recurring Template Pattern for handling inheritance.
- Use expression templates for arithmetic operations.
- Optimize the matrix multiplication implementation.

And, maybe...

- Add more convenient way to initialize Matrix, maybe using 2d-array literals.
- Consider casting scalars, e.g., to allow integer matrix x double matrix.
