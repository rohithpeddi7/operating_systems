// Code by ~Rohith Peddi~
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAXN 100

int n;
sem_t can_sit, chopstick[MAXN];

void *philosopher_func(void *args)
{
    int num = *((int*)args);
    for (int t=0;t<10;t++)
    {
        for (int i=0;i<(rand()+100);i++) /*Think of philosophy and why are we took B.Tech*/ ;
        sem_wait(&can_sit);
        sem_wait(&chopstick[num]);
        sem_wait(&chopstick[(num+1)%n]);
        printf("Philosopher %d picked %d, %d chopsticks and started eating\n",num+1,num+1,(num+1)%n+1);
        for (int i=0;i<(rand()+200);i++) /*Eat for sometime*/ ;
        printf("Philosopher %d finished eating\n",num+1);
        sem_post(&chopstick[num]);
        sem_post(&chopstick[(num+1)%n]);
        sem_post(&can_sit);
    }   
}

int main()
{
    srand(time(NULL));
    printf("Enter the number of philosophers: ");
    scanf("%d",&n);
    sem_init(&can_sit,0,n-1);// To prevent deadlock. Anyways at max n/2 can eat at any time.
    for (int i=0;i<n;i++)
        sem_init(&chopstick[i],0,1);
    pthread_t philosophers[n];
    pthread_attr_t attr;
    for (int i=0;i<n;i++)
    {
        pthread_attr_init(&attr);
        int *num = (int*)malloc(sizeof(int));
        *num = i;
        pthread_create(&philosophers[i],&attr,philosopher_func,num);
    }
    for (int i=0;i<n;i++)
        pthread_join(philosophers[i],NULL);
    printf("All philosophers left the chat\n");
    return 0;
}