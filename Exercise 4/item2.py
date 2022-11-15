import numpy as np
import polyinterp
import matplotlib.pyplot as plt
plt.style.use(
    'seaborn-whitegrid'
)

def f(x):
    return 1/(1+x**2)

def p_n(z):
    x = np.linspace(-5,5,5)
    fx = f(x)
    return polyinterp.LagrangeInterp(fx,x,z)

def g(x):
    return f(x)-p_n(x)

print("supnorm = ", polyinterp.supnorm(g, 1000, -5, 5))