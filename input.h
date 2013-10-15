#ifndef INPUT_H
#define INPUT_H

/* Anything to do with user input (besides the shell)   *
   Functions explained as they come up.                 */

// The basic matrix data type.

struct matrix {
    int m; // Number of rows
    int n; // Number of columns
    double **values; //The actual matrix values
};

/* Process the user input, returns what type of input *
 * Was put in (matrix, vector, or none)               */
int typeinput(std::string input)
{
    if ((input.at(0)=='[')&&(input.at(1)=='['))
        return 1;
    else
        return 0;
}


// Initializes a matrix of size mxn.
double** matrixmake(int m, int n)
{
    double **matrix;
    matrix = new double *[m];
    for (int i=0;i<m;i++)
    {
        matrix[i]=new double[n];
    }
    return matrix;
}

/* Parses the inputted string and creates the matrix *
 * From the string. So far only 1 digit ints work.   */

struct matrix matrixinput(std::string input)
{
    unsigned i=0;
    int j=0;
    int p=0;
    int n=0;
    int m=1;
    int q=0;

    // Finds out the size of the matrix
    while (q<input.length())
    {
        //Interprets the sequence "[[" as the beginning of the matrix.
        if ((input.at(q)=='[')&&(input.at(q+1)=='['))
            n=0;
        else if ((input.at(q)==']')&&(input.at(q+1)==']'))
            q=1000;
        else if ((input.at(q)==']')&&(input.at(q+1)=='['))
        {
            m+=1;
            n=0;
        }
        else if ((input.at(q)!=',')&&(input.at(q)!=' ')&&(input.at(q)!='[')&&(input.at(q)!=']'))
            n+=1;
        q+=1;
    }

    // Creates an empty matrix of size mxn.
    struct matrix A;
    A.n=n;
    A.m=m;
    A.values=matrixmake(A.m,A.n);

    while (i<input.length()-1)
    {
        if (input.at(i)==']')
        {
            if (input.at(i+1)=='[')
            {
                // Interprets line breaks "]["
                i+=1;
                p=0;
                j+=1;
            }
            if (input.at(i+1)==']')
                return A;
            // When an end signal "]]" is detected, return the matrix.
        }
        else if ((input.at(i)!=',')&&(input.at(i)!=' ')&&(input.at(i)!='[')&&(input.at(i)!=']'))
        {
            // Converts the detected number characters into values in the matrix.
            // Only 1 digit ints are supported as of right now.
            char k=input.at(i);
            A.values[j][p]=k-'0';
            if (p==A.n-1)
            {
                p=-1;
                j+=1;
            }
            p+=1;
            i+=1;
        }
        i+=1; // Increment the loop. Why not use a for? Who knows?
    }
    return A; // Stops the build warnings.
}



#endif

