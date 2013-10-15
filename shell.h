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
    int d;
    std::string functions[9]={"print","trace","det","reenter","exit","quit","ero","help"};

    // User welcome! Everybody likes that!
    std::cout << "Welcome to Matrix Calculator!\nType \"help\" for a list of commands.\n";

    // makes sure a matrix is initialized if something went wrong with the original user input.
    if (init==false)
    {
        A=initialize();
        if (A.n<100)
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
         * If none are found, the shell allows only help and *
         * Matrix entry commands.                            */
        if ((init==false)&&((input!="enter")&&(input!="help")))
            std::cout << "ERROR: Must enter a matrix first, try \"enter\"\nmatrix>";
        else if (input=="enter")
        {
            A=initialize();
            if (A.n<100)
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
                    printmatrix(A.m,A.n,A.values);
                    break;
                case 2: // "trace" function of the matrix.
                    d=trace(A.m,A.n,A.values);
                    if (d!=-3200)
                        std::cout << "tr(A) = " << d;
                    break;
                case 3: // "det" (determinant) function of the matrix.
                    d=det(A.m,A.n,A.values);
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
                case 7: // Will pass matrix to elementary row operations shell
                    eshell(A.m,A.n,A.values);
                    break;
                case 8: // Help function
                    std::cout << "List of available commands: ";
                    for (unsigned i=0;i<(sizeof(functions)/sizeof(*functions));i++)
                    {
                        std::cout << functions[i] << " ";
                    }
                    std::cout << "enter";
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
