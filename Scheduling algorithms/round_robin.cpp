// Code by ~Rohith Peddi~
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ll n,time_slice,ct=0,in=0,completed=0;
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter the timeslice: ";
    cin>>time_slice;
    vector<pair<pair<ll,ll>,ll>> a(n),b;
    cout<<"Enter arrival time and burst time of each of the processes:\n";
    map<ll,ll> wait_time,last_seen;
    for (int i=0;i<n;i++)
        cin>>a[i].first.first>>a[i].first.second,a[i].second=i+1,last_seen[i+1] = a[i].first.first;
    b=a;
    sort(a.begin(),a.end());
    cout<<"The order of exceution is: ";
    queue<pair<ll,ll>> q;
    while(true)
    {
        while (in<n&&a[in].first.first<=ct) q.push({a[in].second,a[in++].first.second});
        if (q.empty()&&completed==n) break;
        else if (q.empty())
        {
            ct = a[in].first.first;
            continue;
        }
        pair<ll,ll> current_process = q.front();
        q.pop();
        cout<<current_process.first;
        ll duration = min(time_slice,current_process.second);
        wait_time[current_process.first]+=ct - last_seen[current_process.first];
        ct+=duration;
        last_seen[current_process.first] = ct;
        current_process.second-=duration;
        if (current_process.second) q.push(current_process),cout<<"*";
        else completed++;
        if (completed<n)cout<<"->";
    }
    ll sum=0;
    for (int i=1;i<=n;i++)
        sum+=wait_time[i];
    printf("\nProcess Id\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (ll i=0;i<n;i++)
        printf("%5lld\t\t%5lld\t\t%5lld\t\t%5lld\t\t%6lld\n",i+1,b[i].first.first,b[i].first.second,wait_time[i+1],last_seen[i+1]-b[i].first.first);
    cout<<"\nAverage wait time is "<<(float)sum/n<<endl;
}