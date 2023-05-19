#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

long long int *n,*write_end,*check,x,y,z;
char piped_memory[200000];

int main(int argc, char *argv[])
{
    if (argc<=1)
    {
        printf("Usage: ./q4v2 <positive-integer>");
        return 0;
    }
    n = &x,write_end = &y, check = &z;
    pid_t main_p = getpid();
    sscanf(argv[1],"%lld",n);
    if (*n<=0)
    {
        printf("Error! Only accepts positive integers!");
        return 0;
    }
    while(*n!=1)
    {
        *write_end += sprintf(piped_memory+*write_end,"%lld, ",*n);
        if ((*n)&1) *n=3**n+1;
        else *n/=2;
        pid_t pid = fork();
        if (pid<0)
        {
            printf("Error! Fork failed!\n");
            *check=1;
            return 0;
        }
        else if (pid)
            wait(NULL);
    }
    if (*check||getpid()!=main_p);
    else
        printf("The sequence of numbers: %s1.",piped_memory);
    return 0;
}