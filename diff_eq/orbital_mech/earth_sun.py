"""Gravity field simulation.

Simulates a planetary body moving in the gravity field of
a body as massive as the sun, in two dimensions.
"""

import math

import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

## Constants.

# Gravitational constant.
GRAV = 6.67430e-11  # m^3/ (kg * s^2)

# Mass of sun.
M_SUN = 1.989e30  # kg

# Distance of Earth to sun.
DIST_E_S = 150e9  # m

# Sun's radius.
SUN_RADIUS = 6.96e8  # m

# Earth's average orbital velocity.
E_VEL = 29.78e3  # m/s

NEWT_CONST = GRAV * M_SUN

## Initial values.

INIT_VEL_MULT = 2.0
INIT_ANGLE = 2.25 * math.pi / 4.0
INIT_DIST_MULT = 0.25

# Initial conditions of position and velocity: [x, y, v_x, v_y]
INIT_Z = [
    INIT_DIST_MULT * -DIST_E_S,
    INIT_DIST_MULT * -DIST_E_S,
    INIT_VEL_MULT * math.cos(INIT_ANGLE) * E_VEL,
    INIT_VEL_MULT * math.sin(INIT_ANGLE) * E_VEL,
]

## Discretization.

# Sim rate chosen so that body reaches the "sun"
# in aproximately 10 seconds of simulation time.

# Simulation rate.
SIM_RATE = 5.03693e5  # Seconds of real time per second of sim time.
# Equals 0.1 * # seconds for Earth to reach sun if heading
# directly towards sun at avg. orbital velocity.
# So 1 sim sec. = 0.1 Earth-Sun travel time unit.

# Real unit time step length
DT_FRAC = 1e-2
DT = SIM_RATE * DT_FRAC

# Total real time.
TOT_SIM_SECS = 600
TOT_REAL_T = SIM_RATE * TOT_SIM_SECS  # So TOT_SIM_SECS of sim time.

# Total number of steps
TOT_STEPS = int(TOT_REAL_T / DT) + 1


def d_dt(z):
    """RHS of Newton's second-law as first-order system."""
    dist_cubed = (z[0] ** 2 + z[1] ** 2) ** (3 / 2)
    mag = NEWT_CONST / dist_cubed
    return np.asarray([z[2], z[3], -z[0] * mag, -z[1] * mag])


def simulate(trajectory):
    """
    Run a basic Euler method approximation to populate
    the trajectory array.
    """
    for t in range(1, TOT_STEPS + 1):
        deriv = d_dt(trajectory[t - 1])
        delta = DT * deriv
        trajectory[t] = trajectory[t - 1] + delta
        if t % 100 == 0:
            print(f"Time step {t:4d} deriv: {deriv}")
            print(f"               point: {trajectory[t]}")


## Do simulation.

print(f"Total time steps in simulation: {TOT_STEPS}")

trajectory = np.zeros(shape=(TOT_STEPS + 1, 4), dtype=np.float64)
trajectory[0] = INIT_Z

print(f"Initial values: {trajectory[0]}\n")

print("Running simulation:")
simulate(trajectory)


## Plot the trajectory.

DIM_MULT = 2.0
PLOT_DIM = int(DIM_MULT * DIST_E_S)

fig = plt.figure()
ax = plt.axes(
    xlim=(-0.5 * PLOT_DIM, 1.5 * PLOT_DIM), ylim=(-1.5 * PLOT_DIM, 0.5 * PLOT_DIM)
)

# Filled circle representing the sun,
# maginfied two twice it's actual relative size.
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

# Num milliseconds between frames of animation.
SAMPLE_RATE = 10  # Only plot every nth time-step.
# Effectively speeds up animation.
# 10 means the Earth reaches the Sun in 1 second.

ANIM_TIME_MULT = 1.0  # Speed-up factor.
ANIM_INTER_MILIS = 1000 * DT_FRAC / ANIM_TIME_MULT
# So that 1 real sec = 1 sim sec, as defined above.

print(f"\nMilliseconds between frames: {ANIM_INTER_MILIS}")

ani = anim.FuncAnimation(
    fig=fig,
    func=update_plt,
    init_func=init,
    frames=range(0, TOT_STEPS + 1, SAMPLE_RATE),
    interval=1,
    blit=False,
    repeat=False,
)

# Uncomment to save the animation.
ani.save("orbit_animation.mp4", fps=30, extra_args=["-vcodec", "libx264"])

plt.show()
