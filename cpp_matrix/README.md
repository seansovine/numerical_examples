# Matrix Class Example

In this project we will implement a basic matrix class template
and define some of its operations.

An eventual goal is to use this class as part of the implementation
of a basic, yet fairly general, ODE solver.

The purpose of this project is hands-on learning.

## To Do

- ~~Add vector subclass with subscript operator.~~
- Implement operator\* for ~~scalar (first) and~~ matrix multiplication.
- ~~Move class and method definitions to header.~~
- Use the Matrix class to implement a simple numerical ODE solver.

Further on:

- ~~Make scalar multiplication work for Vector.~~
- Perhaps we should use the Curiously Recurring Template Pattern for Vector.

## On Inheritance (and Templates) and Vector

We need to pause at this point and make a more sytematic review of
inheritance. It feels like we've implemented scalar multiplication for Vector
in a non-optimal way. Along the way we had to explicitly extend constructors
and the multiplication operator from the Matrix base class. This _could_ be
a consequence of the decision we made to make scalar multiplication for Matrix
return a new matrix, vs. modifying the right-hand operand in place. It could
also be a consequence of the fact that we're force to use a friend function to
put the scalar value in the left operand.

But, in any case it's clear that we don't really understand the way methods
(in particular constructors) interact with inheritance. And even less so when
templates are thrown into the mix.

**TODO:** Read up on these things.
