import numpy as np

OMEGA = 1.5
N = 2
VERBOSE = True


def SOR_next(A, b, x):
    """Perform one SOR iteration."""
    if VERBOSE:
        print("---\n")
        print(x)
        print()

    x_n = x.copy()

    for i in range(len(x_n)):
        sigma = 0
        for j in range(0, i):
            sigma += A[i, j] * x_n[j]
        for j in range(i + 1, len(x_n)):
            sigma += A[i, j] * x[j]

        x_n[i] = (1 - OMEGA) * x[i] + (OMEGA / A[i, i]) * (b[i] - sigma)

    if VERBOSE:
        print(x)
        print()

    return x_n


# fmt: off
A = np.asarray([[-4,  1,  0],
                [ 1, -4,  1],
                [ 0,  1, -4]])
# fmt: on
N = A.shape[0]

print(A)
print()

# fmt: off
b = np.asarray([-2.0,
                -3.0,
                -2.0])
# fmt: on

print(b.reshape((N, 1)))
print()

x = np.zeros(N)

NUM_ITER = 40
for i in range(NUM_ITER):
    x = SOR_next(A, b, x)

print("---\n")
print(x)
print()

res = np.dot(A, x.reshape((N, 1)))

print(res)
print()
