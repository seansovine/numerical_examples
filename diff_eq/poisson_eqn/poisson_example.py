from timeit import default_timer as timer

import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(precision=2)

M = 151  # Side length of square grid.

## Build operator matrix.
#   Boundary values encoded in RHS.

N = (M - 2) ** 2
A = np.zeros(shape=(N, N))

D = np.zeros(shape=(M - 2, M - 2))
D[np.eye(N=M - 2, k=0, dtype="bool")] = -4
D[np.eye(N=M - 2, k=1, dtype="bool")] = 1
D[np.eye(N=M - 2, k=-1, dtype="bool")] = 1

for i in range(M - 2):
    ran = slice(i * (M - 2), (i + 1) * (M - 2))
    A[ran, ran] = D

A[np.eye(N=N, k=M - 2, dtype="bool")] = 1
A[np.eye(N=N, k=-(M - 2), dtype="bool")] = 1

# print(A)

## Build RHS

g = np.zeros(shape=(M, M))

# Define charge distribution.

L_RAT = 7 / 16
R_RAT = 9 / 16
H_RAT = 1 / 2

l_coord = int(M * L_RAT)
r_coord = int(M * R_RAT)
t_cord = int(M * (1 - H_RAT) / 2.0)
b_cord = t_cord + int(M * H_RAT)

normalizer = (2 / (b_cord - t_cord)) ** 4
for i in range(t_cord, b_cord + 1):
    g[i, l_coord : l_coord + 2] = 0.3 + normalizer * (i - (M - 1) / 2.0) ** 4
    g[i, r_coord : r_coord + 2] = -g[i, l_coord : l_coord + 2]

# print()
print(g)

b = g[1:-1, 1:-1].reshape((N, 1))

## Find solution by directly solving the system.

start = timer()
u_inn = np.linalg.solve(A, b)
elapsed = timer() - start

print()
print(f"Solved equation in {elapsed} seconds.")

u = np.zeros(shape=(M, M))
u[1:-1, 1:-1] = -1 * u_inn.reshape((M - 2, M - 2))

print()
print(u)

## Plot the solution.

plt.imshow(u, cmap="inferno")
plt.colorbar()
plt.show()
