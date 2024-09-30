// bank transactions with simple list
#include <stdio.h>
#include <omp.h>

int main()
{
    // initialise the transaction array with a simple list
    int T[] = { 60, 85, -100, 24, 99, 362, -8, -14, -9, 128, 7, -5, 12, 25, 93, -84, 86, 54, -10, -5 };
    int tlen = 20; // length of transactions
    int B = 1000; // opening balance

    // Sequential version
    printf("** SEQUENTIAL VERSION **\n");
    printf("Opening balance is %d\n",B);
    for(int i=0; i<tlen; ++i)
    {
        B += T[i];
        printf("Balance is %d\n",B);
    }
    printf("Final balance is %d\n",B);


    // Parallel version
    B = 1000; // re-initialise balance
    printf("** PARALLEL VERSION **\n");
    printf("Opening balance is %d\n",B);
    #pragma omp parallel for
    for(int i=0; i<tlen; ++i)
    {
        B += T[i];
        printf("Balance is %d updated by thread %d\n",B,omp_get_thread_num());
    }
    printf("Final balance is %d\n",B);

    // Is there a potential for a race condition? 
    // Yes there is and you can sometimes see it... sometimes not.

    // Fixed parallel version
    B = 1000; // re-initialise balance
    printf("** FIXED PARALLEL VERSION **\n");
    printf("Opening balance is %d\n",B);
    #pragma omp parallel for
    for(int i=0; i<tlen; ++i)
    {
        #pragma omp critical
        B += T[i];
        printf("Balance is %d updated by thread %d\n",B,omp_get_thread_num());
    }
    printf("Final balance is %d\n",B);

    return 0;
}