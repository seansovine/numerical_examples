""" Setup for discrete Poisson equation solution.

We solve Lu = g on [0, 1] x [0, 1] w/ Dirichlet
condition u = 0 on boundary, using a finite-difference
approximation.
"""

import numpy as np

VERBOSE = True

# # of mesh pionts.
M = 201

# Spacing of mesh points.
h = 1 / (M - 1)

## Build operator matrix.
#   A represents the Laplacian at interior pts.
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

if VERBOSE:
    print(A)
    print()

## Build RHS

g = np.zeros(shape=(M, M))

# Define charge distribution.

L_RAT = 7 / 16
R_RAT = 9 / 16
H_RAT = 1 / 2
PLATE_WIDTH = 1

l_coord = int(M * L_RAT)
r_coord = int(M * R_RAT)
t_cord = int(M * (1 - H_RAT) / 2.0)
b_cord = t_cord + int(M * H_RAT)

normalizer = (2 / (b_cord - t_cord)) ** 4
for i in range(t_cord, b_cord + 1):
    g[i, l_coord : l_coord + PLATE_WIDTH] = 0.3 + normalizer * (i - (M - 1) / 2.0) ** 4
    g[i, r_coord : r_coord + PLATE_WIDTH] = -g[i, l_coord : l_coord + PLATE_WIDTH]

if VERBOSE:
    print(g)
    print()

b = g[1:-1, 1:-1].reshape((N, 1)) * h**2
