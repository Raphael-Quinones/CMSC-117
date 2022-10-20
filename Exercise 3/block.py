import numpy as np

def block(n, a, b, c):
    U = np.zeros((n,n))
    # 100 1's in set
    a = [1 for i in range(100)]

    # 1 to 100 set
    b = [i for i in range(1,101)]

    # alternating 1 and 3
    c = []
    setter = True
    for i in range(100):
        if setter == True:
            c.append(1)
            setter = False
        else:
            c.append(3)
            setter(True) 
