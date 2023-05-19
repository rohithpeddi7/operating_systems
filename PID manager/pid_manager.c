#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_PID 300
#define MAX_PID 5000

// Let's do by simple array.
bool *pids;

int allocate_map()
{
    pids = (bool*)calloc(MAX_PID-MIN_PID+1,sizeof(bool));
    if (!pids)
        return -1;
    return 1;
}

int allocate_pid()
{
    for(int pid=MIN_PID;pid<=MAX_PID;pid++)
        if (!pids[pid-MIN_PID])
        {
            pids[pid-MIN_PID]=true;
            return pid;
        }
    return -1;
}

void release_pid(int pid)
{
    pids[pid-MIN_PID] = false;
}

void deallocate()
{
    free(pids);
}


int main()
{
    allocate_map();
    int pid = allocate_pid();
    if (pid<0)
        printf("Process Allocation Unsuccessful\n");
    else
        printf("Process allocated with %d\n",pid);
    if (pid>0)
        release_pid(pid),printf("Process with %d pid deallocated.\n",pid);
    deallocate();
    return 0;
}
