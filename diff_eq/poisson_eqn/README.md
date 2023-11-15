# Poisson Equation Solvers

This project has NumPy implementations of a few basic solvers solvers for the Poisson equation,

$$\Delta u = f.$$

The original idea for the example was to obtain the electric potential $u$
in the region around the plates of a capacitor when a charge distribution $f$ is given, a problem
which can also be solved [using numerical integration](https://en.wikipedia.org/wiki/Electric_potential#Electric_potential_due_to_a_point_charge).
However, I ended up choosing an arbitrary, but interesting, "charge distribution" function.
We use the Dirichlet boundary condition

$$u = 0 ~~~\text{on}~~ \partial D.$$

## `poisson_direct.py`

This implements a finite-difference approximation and solves the resulting linear system directly
using NumPy. Somewhere between $N = 150$ and $N = 200$, with $N$ being
the grid size, the direct solver times out on my mobile i7 machine.

$$u = 0 ~~~\text{on}~~ \partial D$$

Here is a plot of the solution obtained:

<p align="center" style="margin: 3em;">
<img src="poisson_example.png" width="500" height="459">
</p>

I haven't included any discussion of issues like the accuracy of the
approximation here, but would like to include such a discussion in future examples.

## `poisson_SOR.py`

This solves the same problem using the iterative method of
[successive over-relaxation](https://en.wikipedia.org/wiki/Successive_over-relaxation)
(SOR).
This serial implementation checks the residual at each step, and stops when the difference
of the last two iterations is less than twice machine epsilon. With $M = 200$ the iteration
converges on my machine in 912 steps, taking about 110 seconds.
