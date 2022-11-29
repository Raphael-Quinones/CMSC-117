import numpy as np
import polyinterp

def riemannint(f,a,b,numnodes):
    x, stepsize = np.linspace(a,b,numnodes,retstep=True)
    fx = f(x)
    return sum(stepsize*fx)

def riemannint_gen(f,nodes):
    nodes = np.array(nodes)
    fx = f(nodes[1:])
    h = nodes[1:] - nodes[:len(nodes)-1]
    return sum(h*fx)

def CNCquadweight(n):
    """
    Args:
        n : int
            degree of the Reference Lagrange Polynomial
    """
    x = np.linspace(0,1,n+1)
    fx = np.zeros(len(x))
    w = np.zeros(len(x))
    for k in range(len(x)):
        fx[k] = 1
        a = polyinterp.UndeterminedCoef(fx,x)
        y = 1/np.array(range(1,n+2))
        w[k] = n*sum(a*y)       
        fx[k] = 0
    return w

def ClosedNewtonCotes(f,a,b,weights,numnodes):
    n = len(weights)
    x, stepsize = np.linspace(a,b,numnodes,retstep=True)
    h = stepsize/(n-1)
    s = 0
    for k in range(numnodes-1):
        y = np.linspace(x[k],x[k+1],n)
        fy = f(y)
        s = s + sum(weights*fy)
    return s*h

def fun(x): return np.exp(x)
wei = CNCquadweight(5)
print(wei)
print(ClosedNewtonCotes(fun,0,1,wei,1000))
print(riemannint(fun,0,1,1000))