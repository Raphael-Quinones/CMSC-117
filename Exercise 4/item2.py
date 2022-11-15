import numpy as np
import polyinterp
import matplotlib.pyplot as plt
plt.style.use(
    'seaborn-whitegrid'
)

def f(x):
    return 1/(1-x**2+x**4)

def p_n(z):
    x = np.linspace(-1,1,20 )
    fx = f(x)
    return polyinterp.LagrangeInterp(fx,x,z)

def g(x):
    return f(x)-p_n(x)

print("supnorm = ", polyinterp.supnorm(g, 1000, -1, 1))
z = np.linspace(-1,1, 100)
fz = f(z)
Pz = p_n(z)
plt.figure(1)
plt.plot(z, fz, '-ok', marker = " ", label = 'f')
plt.plot(z, Pz, '-ok', marker = " ", color = 'b', label = 'P')
plt.show()