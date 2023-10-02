"""Solve Poisson's equation with Successive Over-Relaxation.
"""

from timeit import default_timer as timer

import numpy as np
import matplotlib.pyplot as plt

# For console output.
np.set_printoptions(precision=2)
VERBOSE = False

from poisson_setup import b, M, h

# Imported from poisson_setup:
# b = RHS of finite diff. eqn. Ax = b.
# M = number of grid endpoints.
# h = Distance between adjacent mesh points.

if VERBOSE:
    print(b)
    print()

# Optimal relaxation parameter.
# See, e.g., Yang and Gobbert.
omega = 2 / (1 + np.sin(np.pi * h))
N = (M - 2) ** 2

if VERBOSE:
    print(f"Relaxation parameter omega is: {omega:.4f}\n")


def SOR_next(x):
    """Perform one SOR iteration."""
    x_n = (1 - omega) * x.copy()

    # Forward substitute.
    x_n[0] += (omega / -4.0) * (b[0, 0] - x[1])
    for i in range(1, N - 1):
        x_n[i] += (omega / -4.0) * (b[i, 0] - x_n[i - 1] - x[i + 1])
    x_n[N - 1] += (omega / -4.0) * (b[N - 1, 0] - x_n[N - 1])

    if VERBOSE:
        print(x_n)
        print()

    return x_n


# Initial guess at the origin.
x = np.zeros(N)

NUM_ITER = 400

start = timer()
for i in range(NUM_ITER):
    x = SOR_next(x)
elapsed = timer() - start

print(f"Performed {NUM_ITER} SOR iterations in {elapsed:.2f} seconds.")
print()

u = np.zeros(shape=(M, M))
u[1:-1, 1:-1] = -1 * x.reshape((M - 2, M - 2))

print(u)
print()

## Plot the solution.

plt.imshow(u, cmap="inferno")
plt.colorbar()
plt.show()
