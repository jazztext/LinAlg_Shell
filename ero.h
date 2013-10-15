#ifndef ERO_H
#define ERO_H

struct matrix switchrow(int row1, int row2, int **matrix, int m, int n)
{
    if ((row1>m)||(row2>m))
        std::cout << "Error: One or more rows do not exist.\n";
    else
    {
        int temp;
        for(int i=0;i<n;i++)
        {
            temp=matrix[row1-1][i];
            matrix[row1-1][i]=matrix[row2-1][i];
            matrix[row2-1][i]=temp;
        }

    }
    struct matrix A;
    A.n=n;
    A.m=m;
    A.values=matrix;
    return A;
}

struct matrix scalerow(int row, int c, int **matrix, int m, int n)
{
    if (row>m)
        std::cout << "Error: Row does not exist.\n";
    else
    {
        for (int i=0;i<n;i++)
        {
            matrix[row-1][i]=c*matrix[row-1][i];
        }
    }
    struct matrix A;
    A.n=n;
    A.m=m;
    A.values=matrix;
    return A;
}

struct matrix rowplus(int row1, int row2, int c, int **matrix, int m, int n)
{
    if ((row1>m)||(row2>m))
        std::cout << "Error: One or more rows do not exist.\n";
    else
    {
        for (int i=0;i<n;i++)
        {
            matrix[row2-1][i]+=c*matrix[row1-1][i];
        }
    }
    struct matrix A;
    A.n=n;
    A.m=m;
    A.values=matrix;
    return A;
}


struct matrix eshell(int m, int n, int **matrix)
{
    struct matrix A;
    A.m=m;
    A.n=n;
    A.values=matrix;
    bool running=true;
    std::string operation;
    while (running==true)
    {
        std::cout << "\nero>";
        std::cin >> operation;
        int length=operation.length();
        char charop[length];
        operation.copy(charop,length);
        if (operation=="help")
        {
            std::cout << "1) Switch two rows\n2) Scale a row\n3) Add a multiple of another row\n4) Return to shell, saving changes\n";
        }
        else if ((operation=="quit")||(operation=="exit"))
        {
            struct matrix B;
            B.n=n;
            B.m=m;
            B.values=matrix;
            return B;
        }
        else if (operation=="print")
        {
            printmatrix(A.n,A.values);
        }
        else
        {
            int which=charop[0]-'0';
            int row1,row2,c;
            switch (which)
            {
                case 1:
                    std::cout << "R1 <-> R2\n";
                    std::cout << "Row 1:";
                    std::cin >> row1;
                    std::cout << "Row 2:";
                    std::cin >> row2;
                    A=switchrow(row1,row2,matrix,m,n);
                    break;
                case 2:
                    std::cout << "cR -> R\n";
                    std::cout << "Row:";
                    std::cin >> row1;
                    std::cout << "Scalar:";
                    std::cin >> c;
                    A=scalerow(row1,c,matrix,m,n);
                    break;
                case 3:
                    std::cout << "cR1+R2 -> R2\n";
                    std::cout << "Row 1:";
                    std::cin >> row1;
                    std::cout << "Row 2:";
                    std::cin >> row2;
                    std::cout << "Scalar:";
                    std::cin >> c;
                    A=rowplus(row1,row2,c,matrix,m,n);
                    break;
                case 4:
                    std::cout << "Returning to shell.";
                    return A;
                    break;
                default:
                    std::cout << "Not a valid command. Try \"help\" for commands.\n";
                    break;
            }
        }
    }
}
#endif
