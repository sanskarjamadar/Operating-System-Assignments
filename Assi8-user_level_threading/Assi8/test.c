#include <stdio.h>
#include "thread.h"

int x = 20;

int f(void *arg) 
{
    int p = *(int *)arg;
    printf("%d x= %d\n", p, x);
    return 0;
}

int main() 
{
    thread_t tid[3];
    int args[3], j, k=0;

    
    while(k < 3)
    {
        args[k] = 10 + k;
        thread_create(&tid[k], f, &tid[k]);
        k++;
        
    }

    thread_exit(tid[2]);
    k = 0;
    
    while(k < 3) 
    {
        thread_join(tid[k]);
        k++;
    }
    
    return 0;
}

