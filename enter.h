#ifndef INIT_H
#define INIT_H

/* Matrix initialization, will probably   *
 * Be expanded to allow for vector input. */

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
    struct matrix A;
    if (type==1)
    {
        A = matrixinput(input);
        return A;
    }
    else if (type==2)
    {
        //int *vect;
        std::cout << "Note: You have entered a vector.\nVector functionality has not yet been added.\n";
        //vect = vectorinput(input);
    }
    else
    {
        std::cout << "Unrecognized input format. Exiting to shell.\n";
        struct matrix B;
        return B;
    }

}
#endif
