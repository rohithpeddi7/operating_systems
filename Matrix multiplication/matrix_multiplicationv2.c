// Code by ~Rohith Peddi~
#include <stdio.h>
#include <pthread.h>

/*
This is the version 2. In this version, there is a maximum limit on number of threads,
and each thread divides the number of rows.
*/

// Defining the maximum dimension, so that we can declare the arrays globally.
#define MAXN 1000
#define MAXT 100
typedef long long ll;

// A and B are given matrices, mul is the resulting matrix after multiplication. 
// (r1,c) are dimensions of matrix A and (c,c2) are dimensions of matrix B
ll mul[MAXN][MAXN],A[MAXN][MAXN],B[MAXN][MAXN],r1,c,c2;

typedef struct row_args {
    ll start_row,end_row;
} row_args;

ll min(ll a, ll b)
{
    return a<b?a:b;
}

// The function that each thread runs on.
void *calc_row(void *args)
{
    // Takes the row numbers that it needs to calculate.
    ll start = ((row_args *)args)->start_row, end = ((row_args *)args)->end_row;
    // Each element mul[row][j] is calculated. row is from [start,end)
    for (ll row=start;row<end;row++)
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
    ll n_threads = min(r1,MAXT),n_rows = (r1+n_threads-1)/n_threads;
    pthread_t row_threads[n_threads];
    row_args args[min(r1,MAXT)];
    pthread_attr_t attr;
    for (int i=0;i<n_threads;i++)
    {
        pthread_attr_init(&attr);
        args[i].start_row = i*n_rows;
        args[i].end_row = min(r1,(i+1)*n_rows);
        pthread_create(&row_threads[i],&attr,calc_row,&args[i]);
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