#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>
#define MAX 7777

long long int n,sequence[MAX];

void *fib(void *param)
{
    long long int till, x=0, y=1;
    sscanf(param,"%lld",&till); 
    sequence[0] = 0;
    for (long long i = 1; i < till; i++)
        sequence[i] = y, y += x, x=sequence[i];
    pthread_exit(0);
}

// Only works till 93. Above which overflow of long long occurs.
int main(int argc, char *argv[])
{
    if (argc<=1)
    {
        printf("Usage: ./q5 <positive-integer>");
        return 0;
    }
    sscanf(argv[1],"%lld",&n);
    if (n<=0)
    {
        printf("Error! Only accepts positive integers!");
        return 0;
    }
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    char args[77];
    sprintf(args,"%lld",n);
    pthread_create(&tid, &attr, fib, args);
    pthread_join(tid,NULL);
    printf("The fibonacci sequence is: ");
    for (int i=0;i<n-1;i++)
        printf("%lld, ", sequence[i]);
    printf("%lld.",sequence[n-1]);
    return 0;
}