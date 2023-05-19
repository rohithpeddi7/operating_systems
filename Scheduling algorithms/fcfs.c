// Code by ~Rohith Peddi~
#include <stdio.h>
#define ll long long
#define MAXN 200010

ll n, arrival_time[MAXN], burst_time[MAXN], waiting_time[MAXN], turnaround_time[MAXN], order[MAXN];

void swap(ll *p, ll *q)
{
    ll temp = *p;
    *p = *q;
    *q = temp;
}

ll partition(ll l, ll r)
{
    ll pivot = r,j=l-1;
    for (ll i=l;i<r;i++)
        if (arrival_time[i]<arrival_time[pivot])
        {
            j++;
            swap(&arrival_time[i],&arrival_time[j]);
            swap(&burst_time[i],&burst_time[j]);
            swap(&order[i],&order[j]);
        }
    j++;
    swap(&arrival_time[pivot],&arrival_time[j]);
    swap(&burst_time[pivot],&burst_time[j]);
    swap(&order[pivot],&order[j]);
    return j;
}

void quick_sort(ll l, ll r)
{
    if (l>=r) return;
    ll p = partition(l,r);
    quick_sort(l,p-1);
    quick_sort(p+1,r);
}

ll max(ll a, ll b)
{
    return a>b?a:b;
}

void find_statistics()
{
    int ct = 0;
    for (ll i=0;i<n;i++)
        waiting_time[i] = max(ct,arrival_time[i])-arrival_time[i],ct=max(ct,arrival_time[i])+burst_time[i],
        turnaround_time[i] = waiting_time[i] + burst_time[i];
}

float find_avg(ll *a)
{
    ll sum=0;
    for (ll i=0;i<n;i++) sum+=a[i];
    return (float)sum/n;
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%lld",&n);
    printf("Enter arrival time and burst time of each of the processes:\n");
    for (ll i=0;i<n;i++)
        scanf("%lld%lld",&arrival_time[i],&burst_time[i]);
    for (int i=0;i<n;i++)
        order[i] = i+1;
    // Sorting w.r.t arrival_time
    quick_sort(0,n-1);
    find_statistics();
    printf("Order of processes: ");
    for (int i=0;i<n;i++)
    {
        if (i) printf("->");
        printf("%lld",order[i]);
    }
    printf("\n");
    float avg_waiting_time = find_avg(waiting_time),avg_turnaround_time = find_avg(turnaround_time);
    printf("Process Id\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (ll i=0;i<n;i++)
        printf("%5lld\t\t%5lld\t\t%5lld\t\t%5lld\t\t%6lld\n",i+1,arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    printf("Average waiting time: %.3f\nAverage turnaround time: %.3f\n",avg_waiting_time,avg_turnaround_time);
}