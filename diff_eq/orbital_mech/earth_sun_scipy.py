"""Earth-Sun system using SciPy's odeint solver.

We also rescaled all the parameters to convenient values.
"""

import numpy as np
import scipy.integrate as integ
import matplotlib.pyplot as plt
import matplotlib.animation as anim

## Constants; scaled for convenience.

GRAV_CONST = 1.0
SUN_MASS = 1.0
DIST_EA_SU = 1.0
NEWTON_CONST = GRAV_CONST * SUN_MASS

## Simulation functions


def norm(r):
    """Compute distance of 2D point from origin."""
    return np.sqrt(r[0] ** 2 + r[1] ** 2)


def dr_dt(y, t):
    """RHS of Newton's second-law as first-order system."""

    dist_cubed = norm(y[0:2]) ** 3
    mult = NEWTON_CONST / dist_cubed

    print(f"At t = {t:4.3f} distance from origin: {norm(y[0:2])}")
    return np.asarray([y[2], y[3], -y[0] * mult, -y[1] * mult])


## Initial values.

INIT_DIST = 8.0
INIT_X = -INIT_DIST / np.sqrt(2.0)
INIT_Y = -INIT_DIST / np.sqrt(2.0)

ESCAPE_VEL = np.sqrt(2 * GRAV_CONST * SUN_MASS / INIT_DIST)

INIT_ANGLE = 1.5 * np.pi / 4.0
INIT_VEL = 1.25 * ESCAPE_VEL

r0 = np.asarray(
    [
        INIT_X,
        INIT_Y,
        np.cos(INIT_ANGLE) * INIT_VEL / np.sqrt(2.0),
        np.sin(INIT_ANGLE) * INIT_VEL / np.sqrt(2.0),
    ]
)

# Number of timesteps to run the simulation.
SAMPLES = 2501
t = np.linspace(0, 500, SAMPLES)

trajectory = integ.odeint(dr_dt, r0, t)

## Setup for plotting the trajectory.

PLOT_DIM = 30.0
LSHIFT = -0.125
DSHIFT = -0.5

fig = plt.figure()
ax = plt.axes(
    xlim=(-(1.0 - LSHIFT) * PLOT_DIM, (1.0 + LSHIFT) * PLOT_DIM),
    ylim=(-(1.0 - DSHIFT) * PLOT_DIM, (1.0 + DSHIFT) * PLOT_DIM),
)

# Filled circle representing the sun.
SUN_DISP_RAD = 0.1
circle = plt.Circle(xy=(0, 0), radius=SUN_DISP_RAD, color="black")
ax.add_artist(circle)

# Line representing the trajectory.
(line,) = ax.plot([], [], lw=1)


def init():
    line.set_data([], [])


def update_plt(n):
    x_traj = trajectory[:n, 0]
    y_traj = trajectory[:n, 1]
    line.set_data(x_traj, y_traj)


## Plot the trajectory

# Only plot each Nth sample to speed up animation.
SAMPLING_RATE = 2
ani = anim.FuncAnimation(
    fig=fig,
    func=update_plt,
    init_func=init,
    frames=range(0, SAMPLES, SAMPLING_RATE),
    interval=10,
    blit=False,
    repeat=False,
)

SAVE_GIF = True
SHOW_PLOT = True

if SAVE_GIF:
    print()
    print("Saving... ", end="")
    ani.save("planet_orbit.gif", fps=30)
    print("done.")

if SHOW_PLOT:
    plt.show()
