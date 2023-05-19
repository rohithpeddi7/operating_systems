// Code by ~Rohith Peddi~
#include <stdio.h>

struct process{
    int Arrival, Burst, TurnAround, Wait, Remaining, Completion;
    int id;
}Q1[100], Q2[100], Q3[100];

void sort(int n){
    struct process temp;
    int x;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(Q1[i].Arrival > Q1[j].Arrival){
                temp = Q1[i];
                Q1[i] = Q1[j];
                Q1[j] = temp;
            }
        }
    }
    x = Q1[0].Arrival;
    for(int i=0;i<n;i++){
        Q1[i].Arrival-=x;
    }
}

int main(){
    int n, k=0, r=0, t=0, TQ1=5, TQ2=8;
    int flag_Q2, flag_Q3;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter time quanta of queue 1: ");
    scanf("%d",&TQ1);
    printf("Enter time quanta of queue 2: ");
    scanf("%d",&TQ2);
    for(int i=0;i<n;i++){
        printf("Enter the Arrival and Burst of Process %d: ", i+1);
        scanf("%d%d", &Q1[i].Arrival, &Q1[i].Burst);
        Q1[i].Remaining = Q1[i].Burst;
        Q1[i].id = i+1;
    }
    sort(n);
    printf("\nProcess in First Queue follows Round Robin with Time Quanta %d\n", TQ1);
    printf("Process ID\tBurst\tWait\tTurn Around\n");
    for(int i=0;i<n;i++){
        if(Q1[i].Remaining<=TQ1){
            t+=Q1[i].Remaining;
            Q1[i].Remaining = 0;
            Q1[i].Wait = t-Q1[i].Arrival-Q1[i].Burst;
            Q1[i].TurnAround = t-Q1[i].Arrival;
            printf("%d\t\t%d\t%d\t\t%d\n", Q1[i].id, Q1[i].Burst, Q1[i].Wait, Q1[i].TurnAround);
        }
        else{
            Q2[k].Wait = t;
            t+=TQ1;
            Q1[i].Remaining-=TQ1;
            Q2[k].Burst = Q1[i].Remaining;
            Q2[k].Remaining = Q2[k].Burst;
            Q2[k].id = Q1[i].id;
            k++;
            flag_Q2 = 1;
        }
    }
    if(flag_Q2==1){
    printf("\nProcess in Second Queue follows Round Robin with Time Quanta %d\n", TQ2);
    printf("Process ID\tBurst\tWait\tTurn Around\n");
    }
    for(int i=0; i<k; i++){
        if(Q2[i].Remaining<=TQ2){
            t+=Q2[i].Remaining;
            Q2[i].Remaining = 0;
            Q2[i].Wait = t-Q2[i].Arrival-Q2[i].Burst;
            Q2[i].TurnAround = t-Q2[i].Arrival;
            printf("%d\t\t%d\t%d\t\t%d\n", Q2[i].id, Q2[i].Burst, Q2[i].Wait, Q2[i].TurnAround);
        }
        else{
            Q3[r].Wait = t;
            t+=TQ2;
            Q2[i].Remaining-=TQ2;
            Q3[r].Burst = Q2[i].Remaining;
            Q3[r].Remaining = Q3[r].Burst;
            Q3[r].id = Q2[i].id;
            r++;
            flag_Q3 = 1;
        }
    }
    if(flag_Q3==1){
        printf("\nProcess in Third Queue follows FCFS\n");
        printf("Process ID\tBurst\tWait\tTurn Around\n");
    }
    for(int i=0;i<r;i++){
        if(i==0)
            Q3[i].Completion = Q3[i].Burst+t-TQ1-TQ2;
        else
            Q3[i].Completion = Q3[i-1].Completion+Q3[i].Burst;
    }
    for(int i=0;i<r;i++){
        Q3[i].TurnAround = Q3[i].Completion;
        Q3[i].Wait = Q3[i].TurnAround - Q3[i].Burst;
        printf("%d\t\t%d\t%d\t\t%d\n", Q3[i].id, Q3[i].Burst, Q3[i].Wait, Q3[i].TurnAround);
    }

}