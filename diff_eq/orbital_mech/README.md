# Some Celestial Mechanics Simulations

The `planet_orbit.py` script simulates a body orbiting a much more
massive body, using the ODE solvers in `scipy.integrate` to approximately solve the
differential equation system resulting from Newton's laws. The results
are displayed as an animated graph using `matplotlib.animate` and optionally written to a gif.

<p align="center" style="margin: 3em;">
<img src="planet_orbit.gif" width="500" height="459">
</p>

One can show (see [Wikipedia](<https://en.wikipedia.org/wiki/Kepler_orbit#Mathematical_solution_of_the_differential_equation_(1)_above>))
that in this model the orbits will be conics -- either circular,
parabolic, or hyperbolic depending on the energy of the initial conditions.
The `scipy` solver produces a fairly accurate approximation in a reasonable
amount of time.
