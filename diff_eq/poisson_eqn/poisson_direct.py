from timeit import default_timer as timer

import numpy as np
import matplotlib.pyplot as plt

# For console output.
np.set_printoptions(precision=2)

from poisson_setup import A, b, M

# Imported from poisson_setup:
# A = finite diff. matrix for internal points.
# b = RHS of finite diff. eqn. Ax = b.
# M = number of grid endpoints.
# h = Distance between adjacent mesh points.

## Find solution by directly solving the system.

start = timer()
u_inn = np.linalg.solve(A, b)
elapsed = timer() - start

print(f"Solved equation in {elapsed} seconds.")
print()

u = np.zeros(shape=(M, M))
u[1:-1, 1:-1] = -1 * u_inn.reshape((M - 2, M - 2))

print(u)
print()

## Plot the solution.

plt.imshow(u, cmap="inferno")
plt.colorbar()
plt.show()
