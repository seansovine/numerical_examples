"""Solve Poisson's equation using successive over-relaxation.
"""

from timeit import default_timer as timer

import numpy as np
import matplotlib.pyplot as plt

# For console output.
np.set_printoptions(precision=2)
VERBOSE = False

from poisson_setup import A, b, M, h

# Imported from poisson_setup:
# A = finite diff. matrix for internal points.
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


## SOR iteration function.


def SOR_next(A, b, x):
    """
    Perform one SOR iteration.

    Computes the residual at each step, an O(M^2) operation.
    It is possible to determine the convergence rate analytically,
    So then we could choose the number of iterations a priori.

    However this is still an order faster than a direct solution and
    gives access to larger problem.
    """

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

    prod = A @ x_n
    delta = prod - b.reshape((N,))
    resid = np.linalg.norm(delta)

    if VERBOSE:
        print("\n---\n")
        print(f"A shape: {A.shape}; x_n shape: {x_n.shape}; b shape: {b.shape}")
        print(prod.reshape((M - 2, M - 2)))
        print()
        print(b.reshape(M - 2, M - 2))
        print()
        print(delta.reshape(M - 2, M - 2))
        print()
        print(f"Residual is: {resid}")

    return (x_n, resid)


## Initial guess and convergence threshold.

# Initial guess at the origin.
x = np.zeros(N)

print("\n---\n")
mach_eps = np.finfo(np.float64).eps
print(f"Machine epeilon for np.float64: {mach_eps}")
print("Setting convergence threshold to 2 * machine epsilon.")
THRESHOLD = 2 * mach_eps

## Iterate until epsilon-convergence.

start = timer()
num_iter = 0
while True:
    num_iter += 1
    x, resid = SOR_next(A, b, x)
    if resid < THRESHOLD:
        break

elapsed = timer() - start

print(f"Performed {num_iter} SOR iterations to convergence in {elapsed:.2f} seconds.")
print()

u = np.zeros(shape=(M, M))
u[1:-1, 1:-1] = -1 * x.reshape((M - 2, M - 2))

print(u)
print()

## Plot the solution.

plt.imshow(u, cmap="inferno")
plt.colorbar()
plt.show()
