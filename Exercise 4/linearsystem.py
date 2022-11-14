import numpy as np

#Solving Triangular Systems (Without Pivoting)
def ForwardSubRow(L,b):
    """
    Solving Lower Triangular System using foward substitution by rows
    
    Parameters
    ----------
    L : Lower Triangular Matrix
        Coefficient Matrix for Lz = b
    b : Vector
    
    Output
    ------
    x : Vector
        Solution to Lz = b
    """
    n = len(L)
    for i in range(0,n):
        if L[i][i] == 0:
            print("Error! The triangular matrix is not singular.")
            break
    x = np.ones(n)
    x[0] = b[0]/L[0][0]
    for i in range(1,n):
        s = 0
        for j in range(0,i):
            s = s + L[i][j]*x[j]
        x[i] = (b[i] - s)/L[i][i]
    return x

def BackwardSubCol(U,b):
    """
    Solving Upper Triangular System using backward substitution by columns
    
    Parameters
    ----------
    U : Upper Triangular Matrix
        Coefficient Matrix for Uz = b
    b : Vector
    
    Output
    ------
    x : Vector
        Solution to Uz = b
    """
    n = len(U)
    for j in range(0,n):
        if U[j][j] == 0:
            print("Error! The triangular matrix is not singular.")
            break
    for j in range(n-1,0,-1):
        b[j] = b[j]/U[j][j]
        for i in range(0,j):
            b[i] = b[i] - U[i][j]*b[j]
    b[0] = b[0]/U[0][0]
    return b

#LU Factorization (Without Pivoting)
def lu_jki(A):
    """
    LU Factorization using jki (column version of SAXPY) method.
    
    Parameters
    ----------
    A : Matrix
    
    Output
    ------
    A : LU factorization of A stored in A
    """
    n = len(A)
    for j in range(0,n):
        for k in range(0,j):
            for i in range(k+1,n):
                A[i][j] = A[i][j] - A[i][k]*A[k][j]
        for k in range(j+1,n):
            A[k][j] = A[k][j]/A[j][j]      
    return A

def get_lu(A):
    """
    Separates the LU Factorization of A
    
    Parameters
    ----------
    A : Matrix (LU factorization of A)
    
    Output
    ------
    L : lower triangular matrix L; and 
    U : upper triangular matrix U
    """
    n = len(A)
    L = np.tril(A)
    L[range(n), range(n)] = np.ones(n).astype(float)
    U = np.triu(A)
    return L, U

#Solve the linear system Ax = b
def LUsolve(A,b):
    L, U = get_lu(lu_jki(A))
    y = ForwardSubRow(L,b)
    x = BackwardSubCol(U,y)
    return x