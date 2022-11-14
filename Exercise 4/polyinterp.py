import numpy as np

def supnorm(f,nodes,a,b):
    x = np.linspace(a,b,nodes)
    fx = np.abs(f(x))
    return max(fx)

def LagrangeInterp(fx,x,z):
    n = len(x)
    m = len(z)
    v = np.zeros(m)
    for j in range(0, m):
        for k in range(0,n):
            l =1
            for i in range(0,n):
                if i != k:
                    l = l*(z[j]-x[i])/(x[k] - x[i])
            v[j] = v[j] + fx[k]*l
    return v