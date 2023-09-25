"""Gravity field simulation.

Simulates a planetary body moving in the gravity field of
a body as massive as the sun, in two dimensions.
"""

import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np


def mag(r):
    return np.sqrt(r[0] ** 2 + r[1] ** 2)


## Constants.

# Gravitational constant.
GRAV_CONST = 6.67430e-11  # m^3/ (kg * s^2)

# Mass of sun.
MASS_SUN = 1.989e30  # kg

# Distance of Earth to sun.
DIST_E_S = 150e9  # m

# Sun's radius.
SUN_RADIUS = 6.96e8  # m

# Earth's average orbital velocity.
E_VEL = 29.78e3  # m/s


## Initial values.

INIT_ANGLE = 3.0 * np.pi / 4.0

INIT_DIST_MULT = 0.5
INIT_X = INIT_Y = -1 * INIT_DIST_MULT * (DIST_E_S / np.sqrt(2.0))

INIT_DIST = mag((INIT_X, INIT_Y))

ESCAPE_VEL = np.sqrt(2 * GRAV_CONST * MASS_SUN / INIT_DIST)
INIT_VEL_MULT = 1.0
INIT_VEL = INIT_VEL_MULT * ESCAPE_VEL / np.sqrt(2.0)

# Initial conditions of position and velocity: [x, y, v_x, v_y]
INIT_POS = [
    INIT_X,
    INIT_Y,
    INIT_VEL * np.cos(INIT_ANGLE),
    INIT_VEL * np.sin(INIT_ANGLE),
]

## Discretization parameters.

# Sim rate chosen so that body reaches the "sun"
# in aproximately 10 seconds of simulation time.

# Simulation rate.
SIM_RATE = 5.03693e5  # Seconds of real time per second of sim time.
# Equals 0.1 * # seconds for Earth to reach sun if heading
# directly towards sun at avg. orbital velocity.
# So 1 sim sec. = 0.1 Earth-Sun travel time unit.

# Real unit time step length
DT_FRAC = 1e-4
DT = SIM_RATE * DT_FRAC

# Total real-world and simulation times.
TOT_SIM_SECS = 300  # Sim time if animation timing is accurate.
TOT_REAL_T = SIM_RATE * TOT_SIM_SECS  # Total elapsed real-world seconds.

# Total number of steps, including initial
TOT_STEPS = int(TOT_REAL_T / DT) + 1


## Simulation functions


NEWTON_CONST = GRAV_CONST * MASS_SUN


def d_dt(z):
    """RHS of Newton's second-law as first-order system."""
    dist_cubed = mag(z[0:2]) ** 3
    mult = NEWTON_CONST / dist_cubed
    return np.asarray([z[2], z[3], -z[0] * mult, -z[1] * mult], dtype=np.float128)


def simulate(trajectory):
    """
    Run a basic Euler method approximation to
    populate the trajectory array.
    """
    for t in range(1, TOT_STEPS + 1):
        sun_dist = mag(trajectory[t - 1][0:2])
        if t % 100000 == 0:
            print(f"Time step {t:7d} sun distance: {sun_dist:.4E}")
        if sun_dist < 5 * SUN_RADIUS:
            trajectory[t] = trajectory[t - 1]
            print(f"Too close to sun. Distance: {sun_dist}")
            continue
        deriv = d_dt(trajectory[t - 1])
        delta = DT * deriv
        trajectory[t] = trajectory[t - 1] + delta

    print()


## Run simulation.

print(f"Total time steps in simulation: {TOT_STEPS}")

trajectory = np.zeros(shape=(TOT_STEPS + 1, 4), dtype=np.float128)
trajectory[0] = INIT_POS
print(f"Initial values: {trajectory[0]}\n")

print("Running simulation.")
simulate(trajectory)


## Setup for plotting the trajectory.

DIM_MULT = 1.5
PLOT_DIM = int(DIM_MULT * DIST_E_S)
LSHIFT = 0.0
DSHIFT = 0.0

fig = plt.figure()
ax = plt.axes(
    xlim=(-(1.0 - LSHIFT) * PLOT_DIM, (1.0 + LSHIFT) * PLOT_DIM),
    ylim=(-(1.0 - DSHIFT) * PLOT_DIM, (1.0 + DSHIFT) * PLOT_DIM),
)

# Filled circle representing the sun,
# maginfied to twice its actual relative size.
SUN_DISP_RAD = 2 * SUN_RADIUS
circle = plt.Circle(xy=(0, 0), radius=SUN_DISP_RAD, color="black")
ax.add_artist(circle)

# Line representing the trajectory.
(line,) = ax.plot([], [], lw=1)


def init():
    line.set_data([], [])
    # return (line,) # Unneeded b/c blit=False.


def update_plt(t):
    x_traj = trajectory[:t, 0]
    y_traj = trajectory[:t, 1]
    line.set_data(x_traj, y_traj)
    # return (line,)


# Uncomment for static testing:
# STOP = int(0.4 * (TOT_STEPS + 1))
# update_plt(STOP)

# Only plot every nth time-step.
SAMPLE_RATE = 5000
# Effectively speeds up the animation, since there are limits to
# how many frames per second the machine can display.


ANIM_TIME_MULT = 10.0  # Speed-up factor.
ANIM_INTER_MILIS = 1000 * DT_FRAC / ANIM_TIME_MULT
# In theory w/ ANIM_TIME_MULT = 1 and SAMPLE_RATE = 1,
# this should make the actual time of the animation match the simulation time.
# But there are limits to how fast the animation can display frames.

print(f"Requested milliseconds between frames: {ANIM_INTER_MILIS}")

ani = anim.FuncAnimation(
    fig=fig,
    func=update_plt,
    init_func=init,
    frames=range(0, TOT_STEPS + 1, SAMPLE_RATE),
    interval=ANIM_INTER_MILIS,
    blit=False,
    repeat=False,
)

## Plot and/or save the results.

SAVE = False
SHOW = True

if SAVE:
    print("Saving animation to file.")
    ani.save("orbit_animation_fast.gif", dpi=100, writer=anim.PillowWriter(fps=25))
    print("Save complete.")

if SHOW:
    plt.show()
