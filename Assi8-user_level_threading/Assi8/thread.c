#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include "thread.h"

int thread_create(thread_t *thread, int (*fn)(void *), void *arg) 
{
    int tid;
    char *stack = malloc(4096);
    tid = clone(fn, stack + 4096, 0, arg);
    *thread = tid;
    printf("thread id = %d\n", *thread);
    return tid;
}

int thread_join(thread_t thread) 
{
    printf("waitpid ret = %d\n", waitpid(thread, NULL, __WALL));
    return 0;
}

int thread_exit(thread_t thread)
{
    kill(thread, SIGKILL);
    printf("Exit: %d\n", thread);
    return 0;
}

