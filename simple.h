#ifndef SIMPLE_H
#define SIMPLE_H

/* This is for the simple (<10 lines) operations *
 * Required for the entire program to work.      */

// Sums a given list.
int sum(int *terms,int n)
{
    int s=0;
    for(int i=0;i<n;i++)
    {
        s+=terms[i];
    }
    return s;
}

// Takes the product of a given list
int pi(int *terms, int n)
{
    int p=terms[0];
    for(int i=1;i<n;i++)
    {
        p=p*terms[i];
    }
    return p;
}

// Takes the trace of a matrix
int trace(struct matrix A)
{
    if (A.m!=A.n)
    {
        std::cout << "Trace is undefined for rectangular matrices.";
        return -3200;
    }
    else
    {
        int tr=0;
        for (int i=0;i<A.n;i++)
            tr+=A.values[i][i];
        return tr;
    }
}

// Prints a matrix
void printmatrix(struct matrix A)
{
    std::cout << "[[ ";
    for (int i=0;i<A.m;i++)
    {
        for (int j=0;j<A.n;j++)
        {
            std::cout << A.values[i][j] << " ";
        }
        if (i!=A.m-1) //Just to make the output pretty
            std::cout << "]\n [ ";
        else
            std::cout << "]]";
    }
}

// Absolute value
double abs(double a)
{
    if (a<0)
        return (-1)*a;
    return a;
}

// Matrix transpose
struct matrix transpose(struct matrix A)
{
    struct matrix B;
    B.values=matrixmake(A.n,A.m);
    B.n=A.m;
    B.m=A.n;
    for (int i=0;i<A.m;i++)
    {
        for (int j=0;j<A.n;j++)
        {
            B.values[j][i]=A.values[i][j];
        }
    }
    return B;
}

bool matrixequals(struct matrix A, struct matrix B)
{
    if ((A.n!=B.n)||(A.m!=B.m))
        return false;
    else
    {
        for (int i=0;i<A.m;i++)
        {
            for (int j=0;j<A.n;j++)
            {
                if (A.values[i][j]!=B.values[i][j])
                    return false;
            }
        }
        return true;
    }
}
#endif
