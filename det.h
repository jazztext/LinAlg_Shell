#ifndef DET_H
#define DET_H

int det(int n, int **matrix)
{
    int ans=0;
    if (n==2)
    {
        return ((matrix[0][0]*matrix[1][1])-(matrix[1][0]*matrix[0][1]));
        // Simple determinant for 2x2 matrix = ad-bc
    }
    else
    {
        struct matrix sub[n-1];
        //Create a list of submatrices of A.
        for (int k=0;k<n;k++)
        {
            sub[k].m=n-1;
            sub[k].n=n-1;
            sub[k].values=matrixmake(sub[k].m,sub[k].n);
            //For each submatrix, make them (n-1)x(n-1)
            for(int j=0;j<n-1;j++)
            {
                for (int p=0;p<n;p++)
                {
                    /*For each co-ordinate in the submatrices            *
                     *Set the values to be the corresponding values in A.*/
                    if (p<k)
                    {
                        sub[k].values[j][p]=matrix[j+1][p];
                    }
                    else if (p==k)
                        p+=0;
                    else if (p>k)
                    {
                        if (j+1>=n)
                        {
                            sub[k].values[j][p-1]=matrix[0][p];
                        }
                        else
                        {
                            sub[k].values[j][p-1]=matrix[j+1][p];
                        }
                    }
                }
            }
            //Alternate the positive and negative values in the determinant sum.
            if (k%2==1)
                ans+=(matrix[0][k]*det(sub[k].n,sub[k].values));
            else
                ans+=((-1)*matrix[0][k]*det(sub[k].n,sub[k].values));
        }
        return ans;
    }
}

#endif
