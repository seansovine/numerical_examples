"""A simple ODEINT example.
"""

from enum import Enum

import numpy as np
import scipy.integrate as integ
import matplotlib.pyplot as plt


def dy_dt(y, t):
    """Simple y'' = -y example."""
    return np.asarray([y[1], -y[0]])


def euler_solve(dy_dt, y_0, t):
    """Basic Euler method for 1D, second order equation."""
    y = np.zeros(shape=(t.size, 2))
    y[0] = y_0
    for n in range(1, t.size):
        y[n] = y[n - 1] + (t[n] - t[n - 1]) * dy_dt(y[n - 1], 0)
    return y


NUM_STEPS = 101

t = np.linspace(0, 2 * np.pi, NUM_STEPS)
y_0 = [0, 1]
y_odeint = integ.odeint(dy_dt, y_0, t)
y_euler = euler_solve(dy_dt, y_0, t)

Methods = Enum("Methods", ["Euler", "odeint"])

METHOD = Methods.Euler
match METHOD:
    case Methods.Euler:
        y = y_euler
    case Methods.odeint:
        y = y_odeint
    case _:
        raise Exception("Unknown method name given.")

sin = np.sin(t)
delta = np.abs(sin - y[:, 0])

plt.plot(t, sin, "black")
plt.plot(t, y[:, 0], "red")
plt.plot(t, delta, "green")
plt.show()
