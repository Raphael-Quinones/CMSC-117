import numpy as np
import linearsystem as ls

def supnorm(f,step,a,b):
    x = np.linspace(a,b,step)
    fx = f(x)
    return max(fx)

def UndeterminedCoef(fx,x):
    """

    Args:
        fx (_type_): _description_
        x (_type_): _description_
        
    Output:
        P : vector (coefficinet of Lagrange Interpolation Polynomial)
          : [a0 a1 a2 ... an] -> a0 + a1x + a2x^2 + ... +anx^n
    """
    n = len(x)
    V = np.ones((n,n))
    for i in range(n):
        V[:,i] = np.power(x,i)
    return ls.LU_solve(V,fx)