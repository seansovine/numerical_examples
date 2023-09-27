# Poisson Equation Solvers

In this project we'll implement / try out libraries for a few solvers for the Poisson equation,

$$\Delta u = f$$

with various boundary conditions.

## `poisson_example.py`

This example is based on the idea of finding the electric potential in a
region when the charge density in the region is given. It is known
(see [Wikipedia](https://en.wikipedia.org/wiki/Electric_potential#Electrostatics))
that the relationship between electric potential and charge density is given by Poisson's equation:

$$-\Delta V_{E} = \frac{\rho}{\epsilon_o}.$$

I initially wanted to make a realistic model of the potential surrounding the plates of a capacitor.
It is true that the potential is constant inside of a conductor, but rather the realistic
charge distribution the plates is not uniform. The main purpose of this project is to get started with
implementing and trying libraries out various solvers, so a came up with a fairly arbitrary distribution.
If I had used an iterative method to solve the system, I could have encoded the constant potential
of the plates into each iteration.

In this first example, I used a finite-difference scheme and solve the resulting solution directly
using NumPy. With a 150 x 150 grid this already takes about 40 seconds on my machine, which I would
consider to be moderately fast. This shows the benefit of using an iterative method vs. a direct method
to solve the sparse system, which I'll do in a future example.

We use the Dirichlet boundary condition

$$u = 0 ~~~\text{on}~~ \partial D$$

which could be the case if the region were enclosed in a metallic box.

Here is a heatmap plot of the solution obtained:

<div style="margin-top: 3em; margin-bottom: 3em; text-align: center;">
	<img src="poisson_example.png"  width="500" height="459" >
</div>

**Note:** I apologize in advance for any inaccuracies in my physics in the description above.
