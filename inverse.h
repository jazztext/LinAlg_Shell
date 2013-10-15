#ifndef INV_H
#define INV_H

/* Matrix Invertibiilty and Identity                      *
 * Uses the Gauss-Jordan elimination after augmenting     *
 * The original matrix against the identity matrix.       *
 * Also provides a function to create an identity matrix. */


/* Identity Creation                               *
 * Creates a matrix of size nxn with 1s along the  *
 * Main diagonal and zeroes for every other term.  */
struct matrix identity(int n)
{
    struct matrix I;
    I.n=n;
    I.m=n;
    I.values=matrixmake(n,n);
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (i==j)
                I.values[i][j]=1;
            else
                I.values[i][j]=0;
        }
    }
    return I;
}

/* Matrix Inversion                                 *
 * Augments the matrix against the identity matrix  *
 * And uses elementary row operations to calculate  *
 * The inverse of the matrix.                       */
struct matrix inverse(struct matrix A)
{
    struct matrix B;    // Initializing a new matrix is necessary because   //
    B.n=A.n;            // Rref affects the original matrix even if it's    //
    B.m=A.m;            // Not told to because pointers.                    //
    B.values=matrixmake(B.m,B.n);
    for (int i=0;i<B.m;i++)
    {
        for (int j=0;j<B.n;j++)
        {
            B.values[i][j]=A.values[i][j];  // Makes B a new matrix equivalent to A //
        }
    }
    if (matrixequals(rref(B),identity(A.n)))  // Checks if A is invertible through B //
    {
        struct matrix Aug;
        Aug.values=matrixmake(A.m,2*A.n);
        Aug.m=A.m;                           // Augments the orginal matrix against //
        Aug.n=A.n*2;                         // The identity by making a new matrix //
        for (int i=0;i<Aug.m;i++)            // Of size mx2n essentially            //
        {
            for (int j=0;j<Aug.n;j++)
            {
                if (j<A.n)
                    Aug.values[i][j]=A.values[i][j];
                else
                {
                    if ((j-A.n)==i)
                        Aug.values[i][j]=1;
                    else
                        Aug.values[i][j]=0;
                }
            }
        }
        rref(Aug);                          // Row reduce the augmented matrix so   //
        for (int i=0;i<Aug.m;i++)           // The identity is now on the left side //
        {                                   // Leaving the inverted matrix          //
            for (int j=A.n;j<Aug.n;j++)
            {
                A.values[i][j-A.n]=Aug.values[i][j];
            }
        }
        std::cout << "Inverse of A:\n";
        printmatrix(A);                     // Prints the inverted matrix, it's easier here   //
    }                                       // Because if nothing happens the original matrix //
    else                                    // Is returned, so printing there wouldn't work.  //
    {
        std::cout << "Matrix is not invertible."; // If it's not invertible, do nothing.      //
    }
    return A;
}

#endif
