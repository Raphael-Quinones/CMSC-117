import numpy as np
import linearsystem as ls

def f(x):
    '''
        a, b, c, and d are translated into an array in this one
        a = x[0]
        b = x[1]
        c = x[2]
        d = x[3]
    '''

    f0 = (20 * x[0] * x[2]) - (8*x[0]*x[1]) + (16 * x[2]**3) - (4*x[1]*x[3]) - 39
    f1 = (12*x[0]) + (6*x[1]) + (2*x[2]) - (2*x[3]) - 11
    f2 = (4*x[0]**2) + (2*x[1]*x[2]) - (10*x[2]) + (2*x[0]*x[3]**2) + 7
    f3 = -(3*x[0]*x[3]) - (2*x[1]**2) + (7*x[2]*x[3]) - 16

    return np.array([f0, f1, f2, f3])

def Jf(x):
    '''
        Jf00 = 20c-8b
        Jf01 = -4d-8a
        Jf02 = 48c^2 + 20a
        Jf03 = -4b

        Jf10 = 12
        Jf11 = 6
        Jf12 = 2
        Jf13 = -2

        Jf20 = 8a + 2d^2
        Jf21 = 2c
        Jf22 = 2b - 10
        Jf23  = 4ad

        Jf30 = -3d
        Jf31 = -4b
        Jf32 = 7d
        Jf33 = 7c-3a
    '''
    Jf00 = (20*x[2]) - (8*x[1])
    Jf01 = -(4*x[3]) - (8*x[0])
    Jf02 = (48*x[2]**2) + (20 * x[0])
    Jf03 = -(4*x[1])

    Jf10 = 12
    Jf11 = 6
    Jf12 = 2
    Jf13 = -2

    Jf20 = (8*x[0]) + (2*x[3]**2)
    Jf21 = (2*x[2])
    Jf22 = (2*x[1]) - 10
    Jf23 = (4*x[0]*x[3])

    Jf30 = -(3 *x[3])
    Jf31 = -(4*x[1])
    Jf32 = (7*x[3])
    Jf33 = (7*x[2])-(3*x[0])

    return np.array([[Jf00, Jf01, Jf02, Jf03],
                    [Jf10, Jf11, Jf12, Jf13],
                    [Jf20, Jf21, Jf22, Jf23],
                    [Jf30, Jf31, Jf32, Jf33],])

def NewtonSystem(f, JF, x, tol, maxit):
    k = 0
    err = tol + 1
    while(err > tol) & (k < maxit):
        dx = ls.LUsolve(Jf(x),-f(x))
        x = x + dx
        err = max(row.sum() for row in np.abs(dx))
        k += 1
    
    if (err > tol) & (k == maxit):
        print("Method fails")
    return x, f(x), err, k

tol = 10e-15
maxit = 100

x, fx, err, k = NewtonSystem(f, Jf, [1,1,1,1], tol, maxit)
print("x = ", x)
print("f(x) = ", fx)
print("err = ", err)
print("k = ", k)

    





