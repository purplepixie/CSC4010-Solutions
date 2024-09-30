// search
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int l = 100000; // length of array
    int A[l]; // array of numbers
    int s = 55; // search value
    int c = 0; // counter of found values

    // initialise A with random numbers
    srand(time(NULL)); // seed the random number generator 
    for (int i=0; i<l; ++i)
        A[i] = rand()%100; // random number 0-99 inclusive
    
    // sequential version
    for (int i=0; i<l; ++i)
        if (A[i] == s)
            ++c;
    printf("Sequential found %d matches for %d\n",c,s);
    
    // parallel version 1
    c = 0; // re-initialise c
    #pragma omp parallel for
    for (int i=0; i<l; ++i)
        if (A[i] == s)
            ++c;
    printf("Parallel v1 found %d matches for %d\n",c,s);

    // The above is racey as anything... let's try critical

    // parallel version 2
    c = 0; // re-initialise c
    #pragma omp parallel for
    for (int i=0; i<l; ++i)
        if (A[i] == s)
            #pragma omp critical
            ++c;
    printf("Parallel v2 found %d matches for %d\n",c,s);

    // ok we've fixed it... but what does timing look like (can't see it here would need to split out)
    // alternatives to critical will be looked at soon when you can loop back (ha!) to this and try
    // with different data update methods

    return 0;
}