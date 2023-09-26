# Earth-Sun Orbit Simulator

The `earth_sun_scip.py` script simulates the Earth's orbit around the Sun,
using the ODE solvers in `scipy.integrate` to approximately solve the
differential equation resulting from Newton's laws. The results
are displayed as an animated graph using `matplotlib.animate`.

One can show that in this model the orbits will be conics -- either circular,
parabolic, or hyperbolic depending on the energy of the initial conditions.
The `scipy` solver allows a fairly accurate approximation in a reasonable
amount of time.
