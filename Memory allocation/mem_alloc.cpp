// Code by Rohith Peddi
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n;

vector<ll> a;

ll get_next_unallocated_ind(ll f)
{
    for (int i = f;i<n;i++) if (a[i]!=-1) return i;
    return n;
}

void compact()
{
    ll s=n;
    for(ll i=0;i<n;i++)
        if(a[i]==-1)
        {
            s=i;
            break;
        }
    for(ll i=s+1;i<n;i++)
        if(a[i]!=-1)
            swap(a[s++],a[i]);
    printf("Successfully compacted the memory!\n");
}

void status()
{
    ll s=0;
    vector<pair<ll,ll>> c,b;
    for (int i=1;i<n;i++)
    {
        if (a[i]!=a[i-1])
        {
            if (a[i-1]==-1)
                b.push_back({s,i-1});
            else
                c.push_back({s,i-1});
            s = i;
        }
    }
    if (a[n-1]==-1)
        b.push_back({s,n-1});
    else
        c.push_back({s,n-1});
    printf("Allocated memory: ");
    for (auto x: c)
        printf("P%lld [%lld:%lld], ",a[x.first],x.first,x.second);
    printf("\n");
    printf("Unallocated memory: ");
    for (auto x: b)
        printf("[%lld:%lld], ",x.first,x.second);
    printf("\n");
}

void release(ll p)
{
    for (int i=0;i<n;i++)
        if (a[i]==p)
            a[i]=-1;
    printf("Successfully released process %lld memory\n",p);
}

void worst_fit(ll p, ll size)
{
    ll s=-1,e=-1,max_size=0;
    for (int i=0;i<n;i++)
        if (a[i]==-1)
        {
            ll j = get_next_unallocated_ind(i);
            if (j-i>max_size)
                s = i,e = j-1,max_size = j-i;
            i = j;
        }
    if (s!=-1&&max_size>=size)
    {
        for (int i =s; i<s+size;i++)
            a[i] = p;
        printf("Successfully allocated process %lld with %lld memory using worst fit allocation\n",p,size);
        return;
    }
    printf("Cannot allocate the requirements!\n");
}

void first_fit(ll p, ll size)
{
    for (int i=0;i<n;i++)
        if (a[i]==-1)
        {
            ll j = get_next_unallocated_ind(i);
            if (j-i>=size)
            {
                for (int k=i;k<i+size;k++)
                    a[k] = p;
                printf("Successfully allocated process %lld with %lld memory using first fit allocation\n",p,size);
                return;
            }
            i = j;
        }
    printf("Cannot allocate the requirements!\n");
}

void best_fit(ll p, ll size)
{
    ll s=-1,e=-1,min_size=INT32_MAX;
    for (int i=0;i<n;i++)
        if (a[i]==-1)
        {
            ll j = get_next_unallocated_ind(i);
            if (j-i>=size&&j-i<min_size)
                s = i,e = j-1,min_size = j-i;
            i = j;
        }
    if (s!=-1)
    {
        for (int i =s; i<s+size;i++)
            a[i] = p;
        printf("Successfully allocated process %lld with %lld memory using best fit allocation\n",p,size);
        return;
    }
    printf("Cannot allocate the requirements!\n");
}

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        printf("Usage: ./<prog-name> <total-mem-size>");
        return 0;
    }
    sscanf(argv[1],"%lld",&n);
    for(int i=0;i<n;i++)
        a.push_back(-1);
    char s[100];
    while(true)
    {
        ll p,size;
        printf("\nAllocator> ");
        fflush(stdin); scanf("%s",s);
        if (s[0]=='X')
            return 0;
        else if (s[0]=='C')
            compact();
        else if (s[0]=='R'&&s[1]=='Q')
        {
            scanf("%s",s); sscanf(s+1,"%lld",&p);
            char c;
            cin>>size>>c;
            if (c=='W')
                worst_fit(p,size);
            else if (c=='F')
                first_fit(p,size);
            else
                best_fit(p,size);
        }
        else if (s[0]=='R'&&s[1]=='L')
        {
            scanf("%s",s); sscanf(s+1,"%lld",&p);
            release(p);
        }
        else
            status();
    }
    return 0;
}