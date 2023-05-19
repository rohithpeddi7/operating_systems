#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

long long int n;

int main(int argc, char *argv[])
{
    if (argc<=1)
    {
        printf("Usage: ./q4 <positive-integer>");
        return 0;
    }
    sscanf(argv[1],"%lld",&n);
    if (n<=0)
    {
        printf("Error! Only accepts positive integers!");
        return 0;
    }
    pid_t pid = fork();
    if (pid<0)
        printf("Unable to create a child! Try again.");
    else if (!pid)
    {
        printf("The sequence of numbers are: ");
        while(7)
        {
            if (n==1) break;
            printf("%lld, ",n);
            if (n%2) n = 3*n+1;
            else n/=2;
        }
        printf("1.");
    }
    else
        wait(NULL);
    return 0;
}