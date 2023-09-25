# Earth-Sun Orbit Simulator

This project has a Python script that simulates the Earth's orbit around the Sun,
with the initial distance from Sun and initial velocity magnitude and direction
changed by small multiples from their realistic values. It produces an animation and saves it to
a gif file using the matplotlib `FuncAnimation` class.

The simulation is currently using the basic Euler method to approximate the solution to
Newton's equation.

The time-step of the simulation is scaled so that Earth would reach the sun
in 10 simulation seconds, starting from its average distance and at its
average orbital velocity. The animation is sped up by a factor of 10, so
in the animation the Earth would reach the Sun in 1 second of animation time.