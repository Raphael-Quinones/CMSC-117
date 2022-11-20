import numpy as np
import polyinterp
import matplotlib.pyplot as plt
plt.style.use(
    'seaborn-whitegrid'
)

def f(x):
    return 1/(1-x**2+x**4)

def p_n(z, a=-5, b=-5,n=11):
    x = np.linspace(a,b,n)
    fx = f(x)
    return polyinterp.LagrangeInterp(fx,x,z)

def g(x):
    return f(x)-p_n(x)

def g1(x):
    return f(x)-p_n(x,-5,-2,11)
def g2(x):
    return f(x)-p_n(x,-2,1,11)
def g3(x):
    return f(x)-p_n(x,1,5,11)

supnorm = max(polyinterp.supnorm(g1,1000,-5,-2), polyinterp.supnorm(g1,1000,-2,1), polyinterp.supnorm(g1,1000,1,5))
print("supnorm = ", supnorm)
z = np.linspace(-5,5, 1000)
z1 = np.linspace(-5,-2, 333)
z2 = np.linspace(-2,1, 333)
z3 = np.linspace(1,5, 334)
fz = f(z)
Pz = p_n(z)
Pz1 = p_n(z1,-5,-2,11)
Pz2 = p_n(z2,-2,1,11)
Pz3 = p_n(z3,1,5,11)
plt.figure(1)
plt.plot(z, fz, '-ok', marker = " ", label = 'f')
#plt.plot(z, Pz, '-ok', marker = " ", color = 'b', label = 'P')
plt.plot(z1, Pz1, '-ok', marker = " ", color = 'b', label = 'P')
plt.plot(z2, Pz2, '-ok', marker = " ", color = 'b', label = 'P')
plt.plot(z3, Pz3, '-ok', marker = " ", color = 'b', label = 'P')


plt.show()