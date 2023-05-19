// Code by ~Rohith Peddi~
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 500000
#define MAXNO 500000

int n, num_of_elements, pos=0,consumed=0,l=0,r=0,in=0,out=0;
sem_t mutex, empty, full;
int a[MAXNO],buffer[MAXN];

void *producer(void *args)
{
    for (int i=0;i<num_of_elements;i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("Producer producing %dth array element into buffer at %dth position\n",i+1,in+1);
        buffer[in] = a[r++];
        in = (in+1)%n;
        sem_post(&full);
        sem_post(&mutex);
        if ((rand())&1)
            for (int j=0;j<rand();j++);
    }
}

void *consumer(void *args)
{
    while (consumed<num_of_elements)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumer consuming %dth element of array at %dth position of buffer with value %d\n",++consumed,out+1,buffer[out]);
        out = (out+1)%n;
        sem_post(&empty);
        sem_post(&mutex);
        if ((rand())&1)
            for (int j=0;j<rand();j++);
    }
}

int main()
{
    srand(time(NULL));
    printf("Enter buffer size: ");
    scanf("%d",&n);
    printf("Enter the number of elements that producer produces: ");
    scanf("%d",&num_of_elements);
    for (int i=0;i<num_of_elements;i++)
        scanf("%d",&a[i]);
    sem_init(&mutex,0,1);
    sem_init(&empty,0,n);
    sem_init(&full,0,0);
    pthread_t p,c;
    pthread_attr_t p_attr, c_attr;
    pthread_attr_init(&p_attr);
    pthread_attr_init(&c_attr);
    pthread_create(&p,&p_attr,producer,NULL);
    pthread_create(&c,&c_attr,consumer,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
    return 0;
}