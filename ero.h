#ifndef ERO_H
#define ERO_H

/* Elementary Row Operations                                        *
 * Allows for the 3 elementary row operations for matrices          *
 * Additionally allows for automatic row reduction, currently       *
 * Only to Reduced Row Echelon Form, potentially will allow for     *
 * Just Row Echelon Form, but who knows.                            */


/* Row Interchange Operation                         *
 * Potentially faster if a temp variable isn't used? */
struct matrix switchrow(int row1, int row2, struct matrix A)
{
    if ((row1>A.m)||(row2>A.m))
        std::cout << "Error: One or more rows do not exist.\n";
    else
    {
        int temp;
        for(int i=0;i<A.n;i++)
        {
            temp=A.values[row1-1][i];
            A.values[row1-1][i]=A.values[row2-1][i];
            A.values[row2-1][i]=temp;
        }

    }
    return A;
}

/* Row Scaling by a Scalar Operation                    *
 * Does exactly what it sounds like, no surprises here. */
struct matrix scalerow(int row, double c, struct matrix A)
{
    if (row>A.m)
        std::cout << "Error: Row does not exist.\n";
    else
    {
        for (int i=0;i<A.n;i++)
        {
            A.values[row-1][i]=c*A.values[row-1][i];
        }
    }
    return A;
}

/* Adding a Multiple of a Row to Another Row Operation  *
 * Adds a row multiplied by a scalar to another row.    */
struct matrix rowplus(int row1, int row2, double c, struct matrix A)
{
    if ((row1>A.m)||(row2>A.m))
        std::cout << "Error: One or more rows do not exist.\n";
    else
    {
        for (int i=0;i<A.n;i++)
        {
            A.values[row2-1][i]+=c*A.values[row1-1][i];
        }
    }
    return A;
}


/* Automatic Row Reduction                                  *
 * This is a fairly complicated process, explained as it    *
 * Comes up. Variables will hopefully be explained as well. */
struct matrix rref(struct matrix A)
{
    int p=0;
    for (p=0;p<A.m;p++)
    {
        if (A.values[p][0]==1)     // Searches for rows that start with 1
        {                          // And rearranges rows so that the first
            A=switchrow(1,p+1,A);  // Detected row starting with 1 becomes
            p=A.m+1;               // The first row in the matrix.
        }
    }
    if (p==A.m)
        A=scalerow(1,(1/A.values[0][0]),A); // If no rows starting with 1 are found,
    for (int k=0;k<A.n;k++)                 // Scale the first row so it starts with 1.
    {
        for (int j=k;j<A.m;j++)
        {
            for (int i=k;i<A.m;i++)         // Creates an upper triangular matrix
            {                               // Using the cR1+R2 -> R2 operation.
                if ((i!=j)&&(A.values[j][k]!=0)&&(A.values[i][k]!=0))
                {
                    A=rowplus(std::min(j+1,i+1),std::max(j+1,i+1),(-1)*(A.values[i][k]/A.values[j][k]),A);
                }
                if ((A.values[i][k]<0.0001)&&(A.values[i][k]>-0.0001)) // Attempts to eliminate
                    A.values[i][k]=0;                                  // Floating point errors.
            }
        }
    }
    for (int i=0;i<A.m;i++)
    {
        for (int j=0;j<A.n;j++)
        {
            if (A.values[i][j]!=0)
            {
                A=scalerow(i+1,1/(A.values[i][j]),A); //Scales rows to that all leading entries are 1.
                j=10000;
            }
        }
    }
    for (int k=A.n-1;k>=0;k--)
    {
        for (int j=0;j<A.m;j++)
        {
            for (int i=0;i<A.m;i++)
            {
                if ((i!=j)&&(A.values[j][k]!=0)&&(A.values[i][k]!=0)) // Reduces rows back up
                {                                                     // To get to Reduced Row Echelon Form.
                    A=rowplus(std::max(j+1,i+1),std::min(j+1,i+1),(-1)*(A.values[i][k]/A.values[j][k]),A);
                }
                if ((A.values[i][k]<0.0001)&&(A.values[i][k]>-0.0001)) // Attempts to fix floaing
                    A.values[i][k]=0;                                  // Point errors.
            }
        }
    }
    for (int i=0;i<A.m;i++)
    {
        for (int j=0;j<A.n;j++)
        {
            if (A.values[i][j]==-0) // Replaces all -0 terms of the matrix
                A.values[i][j]=0;   // With 0, mainly for nicer output.
        }
    }
    return A;       // All done!
}

#endif
