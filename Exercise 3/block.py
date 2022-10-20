import numpy as np

#helper
def transpose(U, n):
    transposedU = np.zeros((n,n))
    for i in range(100):
        for j in range(100):
            transposedU[i][j] = U[j][i]
    return transposedU

def block(n, a, b, c):
    U = np.zeros((n,n))

    # Setting up U
    for i in range(100):
        U[i][i] = a[i]
    for i in range(99):
        U[i][i+1] = b[i]
    for i in range(98):
        U[i][i+2] = c[i]
    for i in range(97):
        U[i][i+3] = 1

    return U


#Solving the equation part
#Using backwardsubrow
def backwardSubRow(U, b):
    #instatiate 100 zeroes to an x list
    x = [0 for i in range(100)]

    # 99 because index starts at 0
    x[99] = b[99]/U[99][99]

    iter = [(99-i) for i in range(100)]

    for i in iter:
        s = 0
        sec_iter = i+1
        for j in range(sec_iter, 100):
            s = s + (U[i][j] * x[j])
        x[i] = (b[i] - s)/U[i][i]
    return x

#Using ForwardSubRow
def forwardSubRow(L, b):
    #instatiate 100 zeroes to an x list
    x = [0 for i in range(100)]

    #set values
    x[0] = b[0]/L[0][0]

    iter = range(2,100)
    for i in iter:
        s = 0
        sec_iter = range(1, i)
        for j in sec_iter:
            s = s + (L[i][j] * x[j])
        x[i] = (b[i] - s)/L[i][i]
    return x


if __name__ == "__main__":
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
            setter = True

    """Answer for Number 1 a"""
    print("Answer for Number 1 a")
    # 100 1's in set
    
    somethingU = block(100, a, b, c)

    oneAsolution = backwardSubRow(somethingU, a)

    print(somethingU)
    
    #prettify
    for i in range(100):
        print(oneAsolution[i])

    """Answer for Number 1 b"""
    print("Answer for Number 1 b")

    #Transpose somethingU
    somethingL = transpose(somethingU, 100)
    oneBsolution = forwardSubRow(somethingL, b)

    print(somethingL)

    for i in range(100):
        print(oneBsolution[i])








