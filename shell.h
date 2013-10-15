#ifndef SHELL_H
#define SHELL_H

/* The shell function! Parses input, makes sure  *
 * A matrix/vector has been initialized before   *
 * Allowing any other user input. (Besides help) */

int shell(void)
{
    // Housekeeping...
    bool running=true;
    bool init=false;
    unsigned which;
    struct matrix A;
    int d,row1,row2;
    double c;
    std::string functions[15]={"print","trace","det","reenter","exit","quit","--","help","rref","swap","scale","scaleadd","transpose","inverse"};

    // User welcome! Everybody likes that!
    std::cout << "Welcome to Matrix Calculator!\nType \"help\" for a list of commands.\n";

    // makes sure a matrix is initialized if something went wrong with the original user input.
    if (init==false)
    {
        A=initialize();
        if ((A.n<100)&&(A.n!=0))
            init=true;
    }

    // Shell prompt...
    std::cout << "matrix>";

    // The actual shell functioning!
    while (running==true)
    {
        // Takes the user input
        which=0;
        std::string input;
        getline(std::cin,input);

        /* Checks again to make sure a matrix is initialized *
         * If none are found, the shell allows only help,    *
         * Exit, and matrix entry commands.                  */
        if ((init==false)&&((input!="enter")&&(input!="help"))&&(input!="exit")&&(input!="quit"))
            std::cout << "ERROR: Must enter a matrix first, try \"enter\"\nmatrix>";
        else if (input=="enter")
        {
            init=false;
            A=initialize();
            if ((A.n<100)&&(A.n!=0))
                init=true;
            std::cout << "matrix>";
        }
        else if (input=="help")
        {
            std::cout << "List of available commands: ";
            for (unsigned i=0;i<(sizeof(functions)/sizeof(*functions))-1;i++)
                std::cout << functions[i] << " ";
            std::cout << "enter\nmatrix>";
        }
        else if ((input=="exit")||(input=="quit"))
            return 7;
        else
        {
            /* If a matrix is found, check if the user input is one *
             * Of the available functions of the shell.             */
            for (unsigned i=0;i<(sizeof(functions)/sizeof(*functions));i++)
            {
                if (input==functions[i])
                {
                    which=i+1;
                }
            }
            /* Carries out the inputted function. There's probably *
             * A way to do this more simply with pointers?         */
            switch (which)
            {
                case 0: // Input does not match any functions.
                    std::cout << "Not a valid command.\n";
                    break;
                case 1: // "print" function, outputs the matrix nicely.
                    printmatrix(A);
                    break;
                case 2: // "trace" function of the matrix.
                    d=trace(A);
                    if (d!=-3200)
                        std::cout << "tr(A) = " << d;
                    break;
                case 3: // "det" (determinant) function of the matrix.
                    d=det(A);
                    if (d!=-3200)
                        std::cout << "det(A) = " << d;
                    break;
                case 4: // Matrix (re)entry.
                    A=initialize();
                    break;
                case 5: // Exit the shell.
                    running=false;
                    break;
                case 6: // Quit the shell
                    running=false;
                    break;
                case 8: // Help function
                    std::cout << "List of available commands: ";
                    for (unsigned i=0;i<(sizeof(functions)/sizeof(*functions));i++)
                    {
                        std::cout << functions[i] << " ";
                    }
                    std::cout << "enter";
                    break;
                case 9: // Reduced Row Echelon Form
                    A=rref(A);
                    std::cout << "Reduced Row Echelon Form of A:\n";
                    printmatrix(A);
                    break;
                case 10:
                    std::cout << "R1 <-> R2\n";
                    std::cout << "Row 1:";
                    std::cin >> row1;
                    std::cout << "Row 2:";
                    std::cin >> row2;
                    A=switchrow(row1,row2,A);
                    break;
                case 11:
                    std::cout << "cR -> R\n";
                    std::cout << "Row:";
                    std::cin >> row1;
                    std::cout << "Scalar:";
                    std::cin >> c;
                    A=scalerow(row1,c,A);
                    break;
                case 12:
                    std::cout << "cR1+R2 -> R2\n";
                    std::cout << "Row 1:";
                    std::cin >> row1;
                    std::cout << "Row 2:";
                    std::cin >> row2;
                    std::cout << "Scalar:";
                    std::cin >> c;
                    A=rowplus(row1,row2,c,A);
                    break;
                case 13:
                    A=transpose(A);
                    printmatrix(A);
                    break;
                case 14:
                    A=inverse(A);
                    break;
            }
            // Shell prompt again!
            std::cout << "\nmatrix>";
        }
    }
    /* Will only return a value if something goes wrong *
     * Or the user exits the shell, ending the program  */
    return 7;
}

#endif
