# Matrix Class Example

In this project we implement a basic matrix class template
and define some of its operations.

An eventual goal is to use this class as part of the implementation
of a basic, yet fairly general, ODE solver.

The purpose of this project is hands-on learning. I'm not sure how much more I'll put into this
particular project, but it has been a great learning experience to work on it.

## Features

- Has a Matrix class template representing an $m x n$ matrix with scalar type T, implementing the parentheses operator.
- Has a Vector subclass representing a column matrix, implementing the subscript operator.
- Implements scalar and matrix-matrix multiplication.

## Design Decisions

Here are some early decisions that have shaped the design:

- Each matrix instance has constant shape.
  - This means we should be checking the shape in copy and move constructors.
- Operations return new objects.
  - This is necessary for matrix-matrix or matrix-vector products; it seems natural for scalar.
  - Eventually we can implement lazy evaluation of these.

## To Do

- Improve string output formatting.
- Implement more operations:
  - Matrix transpose
  - Matrix-vector product (just need to handle return type).
  - Vector dot product
- Use the Matrix class to implement a simple numerical ODE solver.
- Use the Curiously Recurring Template Pattern for to hand inheritance.
- Use expression templates for arithmetic operations (major refactor).
- Optimize the matrix multiplication implementation.

## On Inheritance (and Templates) and Vector

The design of Vector has brought to light some challenges of using
inheritance with templates. Basically, we followed compiler messages and
internet searches for help and documentation until we made it work. It would
be good to go back and read up on this now, to find the standard ways
of handling this.
