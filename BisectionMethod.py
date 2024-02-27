#!/usr/bin/python3

def bisection_method(f, a, b, TOL, NMAX):
    N = 1
    while N <= NMAX:
        c = (a + b) / 2  # new midpoint
        if f(c) == 0 or (b - a) / 2 < TOL:  # solution found
            return c
        N += 1  # increment step counter
        if f(c) * f(a) > 0:
            a = c
        else:
            b = c  # new interval

    print("Method failed. Maximum number of steps exceeded.")
    return None

# Example usage
def example_function(x):
    return x**3 - x - 2

# Set initial values
a = 0
b = 3
TOL = 0.001
NMAX = 100

# Apply Bisection Method
result = bisection_method(example_function, a, b, TOL, NMAX)

# Output result
if result is not None:
    print("Approximate root:", result)

