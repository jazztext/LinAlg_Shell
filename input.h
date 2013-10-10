#ifndef INPUT_H
#define INPUT_H

/* Anything to do with user input (besides the shell)   *
   Functions explained as they come up.                 */

// The basic matrix data type.

struct matrix {
    int m; // Number of rows
    int n; // Number of columns
    int **values; //The actual matrix values
};

/* Process the user input, returns what type of input *
 * Was put in (matrix, vector, or none)               */
int typeinput(std::string input)
{
    if (input.at(0)=='[')
        {
            if (input.at(1)=='[')
                return 1;
            else
                return 2;
        }
    else
        return 3;
}


// Initializes a matrix of size mxn.
int** matrixmake(int m, int n)
{
    int **matrix;
    matrix =new int *[n];
    for (int i=0;i<n;i++)
    {
        matrix[i]=new int[m];
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
    unsigned m=0;

    // Finds out the size of the matrix (so far only square matrices are supported.
    while (m<input.length())
    {
        //Interprets the sequence "[[" as the beginning of the matrix.
        if ((input.at(m)=='[')&&(input.at(m+1)=='['))
            n=0;
        else if ((input.at(m)==']')&&(input.at(m+1)=='['))
            m=1000; // Forces the loop to end when a line break "][" is detected.
        else if ((input.at(m)!=',')&&(input.at(m)!=' ')&&(input.at(m)!='[')&&(input.at(m)!=']'))
            n+=1;
        m+=1;
    }

    // Creates an empty matrix of size nxn.
    struct matrix A;
    A.n=n;
    A.m=n;
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

