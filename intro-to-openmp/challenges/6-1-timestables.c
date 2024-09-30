#include <stdio.h>
#include <omp.h>

int main()
{
    // m x n values
    int m = 1000;
    int n = 1000;
    // m x n array - note no need to initialise
    int table[m][n];

    // sequential implementation
    for (int mi=0; mi<m; mi++)
    {
        for (int ni=0; ni<n; ni++)
        {
            table[mi][ni] = mi*ni;
        }
    }

    // parallel implementation
    #pragma omp parallel // create parallel region
    {
        #pragma omp for // use the team to process a for loop (note no parallel)
        for (int mi=0; mi<m; mi++)
        {
            for (int ni=0; ni<n; ni++)
            {
                table[mi][ni] = mi*ni;
            }
        }
    }

    /*
    Interesting note: could we use 2 x #pragma omp for directives, one before each loop?
    The answer is no, we get a compile time error.

    We could however consider using collapse if the OpenMP version supports it... perhaps
    */
    
    return 0;
}