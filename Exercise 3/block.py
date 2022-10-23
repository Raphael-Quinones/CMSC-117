import numpy as np
import sys

#Set up numpy to print whole arrays
np.set_printoptions(threshold=sys.maxsize)

#helper
def transpose(U, n):
    transposedU = np.zeros((n,n))
    for i in range(n):
        for j in range(n):
            transposedU[i][j] = U[j][i]
    return transposedU

def block(n, a, b, c):
    U = np.zeros((n,n))

    # Setting up U
    for i in range(n):
        U[i][i] = a[i]
    for i in range(n-1):
        U[i][i+1] = b[i]
    for i in range(n-2):
        U[i][i+2] = c[i]
    for i in range(n-3):
        U[i][i+3] = 1

    return U


#Solving the equation part
#Using backwardsubrow
def backwardSubRow(U,n, b):
    #instatiate 100 zeroes to an x list
    x = [0 for i in range(n)]

    # 99 because index starts at 0
    x[n-1] = b[n-1]/U[n-1][n-1]

    iter = [(n-i-1) for i in range(n)]

    for i in iter:
        s = 0
        sec_iter = i+1
        for j in range(sec_iter, n):
            s = s + (U[i][j] * x[j])
        x[i] = (b[i] - s)/U[i][i]
    return x

#Using ForwardSubRow
def forwardSubRow(L, n, b):
    #instatiate 100 zeroes to an x list
    x = [0 for i in range(n)]

    #set values
    x[0] = b[0]/L[0][0]

    iter = range(1,n)
    for i in iter:
        s = 0
        sec_iter = range(0, i)
        for j in sec_iter:
            s = s + (L[i][j] * x[j])
        x[i] = (b[i] - s)/L[i][i]
    return x

#LU factorization lukji
def lukji(A, n):
    for k in range(n):
        iter = k + 1
        for j in range(iter, n):
            A[j][k] = A[j][k]/A[k][k]
        for j in range(iter, n):
            sec_iter = k + 1
            for i in range(sec_iter, n):
                A[i][j] = A[i][j] - (A[i][k] * A[k][j])
    return A

# separate upper and lower triangular system from lukji
def separatelukji(lukjiarray, n):
    upper = np.zeros((n,n))
    lower = np.zeros((n,n))


    #for upper
    iterupper = [(n-1-i) for i in range(n)]
    for i in iterupper:
        sec_iterupper = i
        for j in range(sec_iterupper, n):
            upper[i][j] = lukjiarray[i][j]

    #for lower
    iterlower = range(0,n)
    for i in iterlower:
        sec_iterlower = range(0, i)
        for j in sec_iterlower:
            lower[i][j] = lukjiarray[i][j]
    #artificially create 1's on the diagonals
    for i in range(n):
        lower[i][i] = 1
    return upper, lower

def res_norm(T, x):
    # find Ax for computing residual norm
    Ax = np.matmul(T, x)  

    #residual norm
    res_norm = 0
    res_normarray = []
    for i in range(100):
        res_norm = res_norm + (abs(a[i] - Ax[i]))
        res_normarray.append(abs(a[i] - Ax[i]))
    return res_norm
        



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
    with open('Item1a.txt', 'w') as f:
        print("Answer for Number 1 a", file = f)
    
        somethingU = block(100, a, b, c)
        oneAsolution = backwardSubRow(somethingU,100, a)

        print("Matrix for 1a", file = f)
        for i in range(100):
            print(list(somethingU[i]), file = f)

        #residual norm
        res_normone = res_norm(somethingU, oneAsolution)
        print("Residual Norm", file = f)
        print(res_normone, file = f)

    
        #prettify
        print("Answer for 1a", file = f)
        print(oneAsolution, file = f)

    """Answer for Number 1 b"""
    with open('Item1b.txt', 'w') as f:

        print("Answer for Number 1 b", file = f)

        #Transpose somethingU
        somethingL = transpose(somethingU, 100)
        oneBsolution = forwardSubRow(somethingL, 100, b)

        print("Matrix for 1b", file = f)
        for i in range(100):
            print(list(somethingL[i]), file = f)

        #residual norm
        res_normtwo = res_norm(somethingL, oneBsolution)
        print("Residual Norm", file = f)
        print(res_normtwo, file = f)

        print("Answer for 1b", file = f)
        print(oneBsolution, file = f)

    '''Answer for 2 a'''
    with open('Item2a.txt', 'w') as f:

        print("Answer for 2a", file = f)
        #setting up given
        numbertwoa = np.zeros((3,3))
        numbertwoa[0][0] = 50
        numbertwoa[0][1] = 107
        numbertwoa[0][2] = 36
        numbertwoa[1][0] = 25
        numbertwoa[1][1] = 54
        numbertwoa[1][2] = 20
        numbertwoa[2][0] = 31
        numbertwoa[2][1] = 66
        numbertwoa[2][2] = 21

        print("Given", file = f)
        for i in range(3):
            print(numbertwoa[i], file = f)
                
        solutiontwoa = lukji(numbertwoa, 3)
        oneupper, onelower = separatelukji(solutiontwoa, 3)

        print("Upper Triangle from LU Factorization", file = f)
        print(oneupper, file = f)
        print("Lower Triangle from LU Factorization", file = f)
        print(onelower, file = f)

        atemp = forwardSubRow(onelower, 3, a)
        atemptwo = backwardSubRow(oneupper, 3, atemp)
        print("Answer for 2a", file = f)
        print(atemptwo, file = f)

    '''Answer for 2b'''
    with open('Item2b.txt', 'w') as f:

        print("Answer for 2b", file = f)
        #setting up given
        numbertwob = np.zeros((3,3))
        numbertwob[0][0] = 10
        numbertwob[0][1] = 2
        numbertwob[0][2] = 1
        numbertwob[1][0] = 2
        numbertwob[1][1] = 20
        numbertwob[1][2] = -2
        numbertwob[2][0] = -2
        numbertwob[2][1] = 3
        numbertwob[2][2] = 10

        print("Given", file = f)
        for i in range(3):
            print(numbertwob[i], file = f)

        solutiontwob = lukji(numbertwob, 3)
        twoupper, twolower = separatelukji(solutiontwob, 3)

        print("Upper Triangle from LU Factorization", file = f)
        print(twoupper, file = f)
        print("Lower Triangle from LU Factorization", file = f)
        print(twolower, file = f)

        #Finding the solutions
        btemp = forwardSubRow(twolower, 3, a)
        btemptwo = backwardSubRow(twoupper, 3, btemp)
        print("Answer for 2b", file = f)
        print(btemptwo, file = f)











