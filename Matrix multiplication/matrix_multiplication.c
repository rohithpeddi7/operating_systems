// Code by ~Rohith Peddi~
#include <stdio.h>
#include <pthread.h>

/*
I did the following steps:
1. I'm creating a seperate thread for each row of the matrix A.
2. Each thread runs on a function that calculates each row of the final matrix.
*/

// Defining the maximum dimension, so that we can declare the arrays globally.
#define MAXN 1000

// A and B are given matrices, mul is the resulting matrix after multiplication. 
// (r1,c) are dimensions of matrix A and (c,c2) are dimensions of matrix B
long long mul[MAXN][MAXN],arg_row[MAXN],A[MAXN][MAXN],B[MAXN][MAXN],r1,c,c2;

// The function that each thread runs on.
void *calc_row(void *args)
{
    // Takes the row number that it needs to calculate.
    long long row = *((long long*)args);
    // Each element mul[row][j] is calculated.
    for (int j=0;j<c2;j++)
        for (int k=0;k<c;k++)
            mul[row][j] += A[row][k]*B[k][j];
    pthread_exit(0);
}

int main()
{
    printf("***** MATRIX MULTIPLICATION PROGRAM *****\n");
    printf("Enter the number of rows of matrix A: ");
    scanf("%lld",&r1);
    printf("Enter the number of columns of matrix A (same as number of rows of matrix B): ");
    scanf("%lld",&c);
    printf("Enter the number of columns of matrix B: ");
    scanf("%lld",&c2);
    printf("Enter the matrix A row-by-row:\n");
    for (int i=0;i<r1;i++)
        for (int j=0;j<c;j++)
            scanf("%lld",&A[i][j]);
    printf("Enter the matrix B row-by-row:\n");
    for (int i=0;i<c;i++)
        for (int j=0;j<c2;j++)
            scanf("%lld",&B[i][j]);
    pthread_t row_threads[r1];
    pthread_attr_t attr;
    for (int i=0;i<r1;i++)
    {
        pthread_attr_init(&attr);
        arg_row[i] = i;
        pthread_create(&row_threads[i],&attr,calc_row,&arg_row[i]);
    }
    for (int i=0;i<r1;i++)
        pthread_join(row_threads[i],NULL);
    printf("The matrix AxB is :\n");
    for (int i=0;i<r1;i++)
    {
        for (int j=0;j<c2;j++)
            printf("%lld ",mul[i][j]);
        printf("\n");
    }
    printf("Thanks for using the program!");
    return 0;
}