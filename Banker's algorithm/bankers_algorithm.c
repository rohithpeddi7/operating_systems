// Code by ~Rohith Peddi~
#include <stdio.h>
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

int available[NUMBER_OF_RESOURCES], maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],
    allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],order_of_execution[NUMBER_OF_CUSTOMERS];

int is_safe_state()
{
    int finish[NUMBER_OF_CUSTOMERS] = {} , temp_available[NUMBER_OF_RESOURCES], temp_order[NUMBER_OF_CUSTOMERS],count=0, pnt=0;
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        temp_available[i] = available[i];
    while(count<NUMBER_OF_CUSTOMERS)
    {
        int check=0;
        for (int i=0;i<NUMBER_OF_CUSTOMERS;i++)
        {
            if (finish[i]) continue;
            int less_than=1;
            for (int j=0;j<NUMBER_OF_RESOURCES;j++)
                if (need[i][j]>temp_available[j])
                    less_than=0;
            if (!less_than) continue;
            finish[i]=1,count++,check=1, temp_order[pnt++] = i;
            for (int j=0;j<NUMBER_OF_RESOURCES;j++)
                temp_available[j]+=allocation[i][j];
        }
        if (!check) return 0;
    }
    for (int i=0;i<NUMBER_OF_CUSTOMERS;i++)
        order_of_execution[i] = temp_order[i];
    return 1;
}

int request_resources(int customer_num, int request[])
{
    int check=1;
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        if (request[i]>need[customer_num][i]||request[i]>available[i])
            check=0;
    if (!check) return -1;
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        need[customer_num][i]-=request[i],allocation[customer_num][i]+=request[i], available[i]-=request[i];
    if (!is_safe_state())
    {
        for (int i=0;i<NUMBER_OF_RESOURCES;i++)
            need[customer_num][i]+=request[i],allocation[customer_num][i]-=request[i], available[i]+=request[i];
        return -1;
    }
    return 0;
}

void release_resources(int customer_num, int release[])
{
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
    {
        if (release[i]>allocation[customer_num][i] || release[i]==-1) release[i] = allocation[customer_num][i]; 
        need[customer_num][i] += release[i], allocation[customer_num][i]-=release[i],available[i]+=release[i];
    }
}

void display_resources_distribution()
{
    printf("\nAvailable resources:\n");
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        printf("Resource %d\t",i+1);
    printf("\n");
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        printf("%6d\t\t",available[i]);
    printf("\n\n");
    printf("Maximum resources:\n");
    printf("Customer id\t");
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        printf("Resource %d\t",i+1);
    printf("\n");
    for (int c_id=0;c_id<NUMBER_OF_CUSTOMERS;c_id++)
    {
        printf("%6d\t\t",c_id);
        for (int i=0;i<NUMBER_OF_RESOURCES;i++)
            printf("%6d\t\t",maximum[c_id][i]);
        printf("\n");
    }
    printf("\n");
    printf("Allocated resources:\n");
    printf("Customer id\t");
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        printf("Resource %d\t",i+1);
    printf("\n");
    for (int c_id=0;c_id<NUMBER_OF_CUSTOMERS;c_id++)
    {
        printf("%6d\t\t",c_id);
        for (int i=0;i<NUMBER_OF_RESOURCES;i++)
            printf("%6d\t\t",allocation[c_id][i]);
        printf("\n");
    }
    printf("\n");
    printf("Need resources:\n");
    printf("Customer id\t");
    for (int i=0;i<NUMBER_OF_RESOURCES;i++)
        printf("Resource %d\t",i+1);
    printf("\n");
    for (int c_id=0;c_id<NUMBER_OF_CUSTOMERS;c_id++)
    {
        printf("%6d\t\t",c_id);
        for (int i=0;i<NUMBER_OF_RESOURCES;i++)
            printf("%6d\t\t",need[c_id][i]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
        sscanf(argv[i],"%d",&available[i-1]);
    FILE *max_requests = fopen("max_requests.txt","r");
    for (int i=0;i<NUMBER_OF_CUSTOMERS;i++)
    {
        for (int j=0;j<NUMBER_OF_RESOURCES;j++)
           fscanf(max_requests,"%d,",&maximum[i][j]),need[i][j]=maximum[i][j];
        order_of_execution[i]=i;
    }
    printf("\n****************** Welcome to Rohith Peddi's Bank! ************************\n\n");
    printf("Please enter how we could be of service.\n1. Enter RQ id x..y for request of resources.\n2. RL id x..y for release of resources\n3. * for an overview of all the resources distribution.\n4. PO for printing possible order of execution of processes.\n5. EX for exiting the bank.\n\n");
    char command[7];
    while(7)
    {
        printf("Enter your command: ");
        scanf("%s",command);
        if (command[0]=='*')
            display_resources_distribution();
        else if (command[0]=='R'&&command[1]=='Q')
        {
            int cust_id,req[NUMBER_OF_RESOURCES];
            scanf("%d",&cust_id);
            for (int r=0;r<NUMBER_OF_RESOURCES;r++)
                scanf("%d",&req[r]);
            if (request_resources(cust_id,req)) printf("Uh oh! the resources you requested cannot be allocated to you.\n");
            else printf("Resources have been allocated!\n");
        }
        else if (command[0]=='R'&&command[1]=='L')
        {
            int cust_id, rel[NUMBER_OF_RESOURCES];
            scanf("%d",&cust_id);
            for (int i=0;i<NUMBER_OF_RESOURCES;i++)
                scanf("%d",&rel[i]);
            release_resources(cust_id,rel);
            printf("Resources have been successfully released!\n");
        }
        else if (command[0]=='P'&&command[1]=='O')
        {
            printf("Possible order of execution is: ");
            for (int i=0;i<NUMBER_OF_CUSTOMERS;i++)
                printf("%d ",order_of_execution[i]);
            printf("\n");
        }
        else
            break;
        printf("\n");
    }
    printf("\nThanks for visiting the bank, hope we serviced you well!\n");
    return 0;
}