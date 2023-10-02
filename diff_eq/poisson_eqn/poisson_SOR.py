"""Solve Poisson's equation with Successive Over-Relaxation.
"""

from timeit import default_timer as timer

import numpy as np
import matplotlib.pyplot as plt

# For console output.
np.set_printoptions(precision=2)
VERBOSE = False

from poisson_setup import A, b, M, h

# Imported from poisson_setup:
# b = RHS of finite diff. eqn. Ax = b.
# M = number of grid endpoints.
# h = Distance between adjacent mesh points.

if VERBOSE:
    print(b)
    print()

# Optimal relaxation parameter.
# See, e.g., Yang and Gobbert.
OMEGA = 2 / (1 + np.sin(np.pi * h))
N = (M - 2) ** 2

if VERBOSE:
    print(f"Relaxation parameter omega is: {OMEGA:.4f}\n")


def SOR_next(A, b, x):
    """Perform one SOR iteration."""

    if VERBOSE:
        print("---\n")
        print(x)
        print()

    x_n = x.copy()

    for i in range(M - 2):
        sigma = x[i + (M - 2)]
        if i == 0:
            sigma += x[i + 1]
        elif i == M - 3:
            sigma += x_n[i - 1]
        else:
            sigma += x[i + 1] + x_n[i - 1]

        x_n[i] = (1 - OMEGA) * x[i] + (OMEGA / -4.0) * (b[i, 0] - sigma)

    for n in range(1, M - 3):
        offset = n * (M - 2)
        for i in range(M - 2):
            i_o = offset + i
            sigma = x_n[i_o - (M - 2)] + x[i_o + (M - 2)]
            if i == 0:
                sigma += x[i_o + 1]
            elif i == M - 3:
                sigma += x_n[i_o - 1]
            else:
                sigma += x[i_o + 1] + x_n[i_o - 1]

            x_n[i_o] = (1 - OMEGA) * x[i_o] + (OMEGA / -4.0) * (b[i_o, 0] - sigma)

    offset = (M - 3) * (M - 2)
    for i in range(M - 2):
        i_o = offset + i
        sigma = x_n[i_o - (M - 2)]
        if i == 0:
            sigma += x[i_o + 1]
        elif i == M - 3:
            sigma += x_n[i_o - 1]
        else:
            sigma += x[i_o + 1] + x_n[i_o - 1]

        x_n[i_o] = (1 - OMEGA) * x[i_o] + (OMEGA / -4.0) * (b[i_o, 0] - sigma)

    if VERBOSE:
        print(x)
        print()

    return x_n


# Initial guess at the origin.
x = np.zeros(N)

NUM_ITER = 100

start = timer()
for i in range(NUM_ITER):
    x = SOR_next(A, b, x)
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
