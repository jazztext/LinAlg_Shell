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
int trace(int m, int n, int **matrix)
{
    if (m!=n)
    {
        std::cout << "Trace is undefined for rectangular matrices.";
        return -3200;
    }
    else
    {
        int tr=0;
        for (int i=0;i<n;i++)
            tr+=matrix[i][i];
        return tr;
    }
}

// Prints a matrix
void printmatrix(int m, int n, int **matrix)
{
    std::cout << "[[ ";
    for (int i=0;i<m;i++)
    {
        for (int j=0;j<n;j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        if (i!=m-1) //Just to make the output pretty
            std::cout << "]\n [ ";
        else
            std::cout << "]]";
    }
}

#endif
