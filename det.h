#ifndef DET_H
#define DET_H

int det(struct matrix A)
{
    if (A.m!=A.n)
    {
        std::cout << "Determinant is undefined for rectangular matrices.";
        return -3200;
    }
    else
    {
        double ans=0;
        if (A.n==2)
        {
            return ((A.values[0][0]*A.values[1][1])-(A.values[1][0]*A.values[0][1]));
            // Simple determinant for 2x2 matrix = ad-bc
        }
        else
        {
            struct matrix sub[A.n];
            //Create a list of submatrices of A.
            for (int k=0;k<A.n;k++)
            {
                sub[k].m=A.n-1;
                sub[k].n=A.n-1;
                sub[k].values=matrixmake(sub[k].m,sub[k].n);
                //For each submatrix, make them (n-1)x(n-1)
                for(int j=0;j<A.n-1;j++)
                {
                    for (int p=0;p<A.n;p++)
                    {
                        /*For each co-ordinate in the submatrices            *
                         *Set the values to be the corresponding values in A.*/
                        if (p<k)
                        {
                            sub[k].values[j][p]=A.values[j+1][p];
                        }
                        else if (p==k)
                            p+=0;
                        else if (p>k)
                        {
                            if (j+1>=A.n)
                            {
                                sub[k].values[j][p-1]=A.values[0][p];
                            }
                            else
                            {
                                sub[k].values[j][p-1]=A.values[j+1][p];
                            }
                        }
                    }
                }
                //Alternate the positive and negative values in the determinant sum.
                if (k%2==0)
                    ans+=(A.values[0][k]*det(sub[k]));
                else
                    ans+=((-1)*A.values[0][k]*det(sub[k]));
            }
            return ans;
        }
    }
}

#endif
