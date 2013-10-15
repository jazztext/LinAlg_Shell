#ifndef INIT_H
#define INIT_H

/* Matrix Initialization                     *
 * Allows for matrices of all sizes besides  *
 * 1x1, and passes the initialized matrix to *
 * The main shell function.                  */

struct matrix initialize(void)
{
    std::cout << "Enter a matrix:";
    std::string input;
    getline(std::cin,input);
    if (input.length()<=5)
    {
        std::cout << "Must be greater than 1x1 matrix. Exiting to shell.\n";
        struct matrix B;
        return B;
    }
    int type = typeinput(input);
    if (type==1)
        return matrixinput(input);
    else
    {
        std::cout << "Unrecognized input format. Exiting to shell.\n";
        struct matrix B;
        return B;
    }
}
#endif
