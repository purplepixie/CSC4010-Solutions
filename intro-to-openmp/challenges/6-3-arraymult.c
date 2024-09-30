// array multiplication
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int n = 100000; // length of arrays
    int a[n],b[n],c[n]; // a, b, and c arrays

    // initialise a and b
    srand(time(NULL));
    for (int i=0; i<n; ++i)
    {
        a[i]=rand()%1000;
        b[i]=rand()%1000;
    }

    // sequential loop
    for (int i=0; i<n; ++i)
    {
        c[i] = a[i]*b[i];
    }

    // parallel loop
    #pragma omp parallel for
    for (int i=0; i<n; ++i)
    {
        c[i] = a[i]*b[i];
    }

    // is there a potential for a race condition?
    // no - each parallel operation does a distinct unrelated multiplcation

    // but... are there possible speed issues with false sharing? Yes.
}