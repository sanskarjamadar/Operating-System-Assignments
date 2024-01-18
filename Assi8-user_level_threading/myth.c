#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>

#include "myth.h"

int myth_create(myth_t *thread, int (*fn)(void *), void *arg) {
    int tid;
    char *stack = malloc(4096);
    tid = clone(fn, stack + 4096, 0, arg);
    *thread = tid;
    printf("thread id = %d\n", *thread);
    return tid;
}

int myth_join(myth_t thread) {
    printf("waitpid ret = %d\n", waitpid(thread, NULL, __WALL));
    return 0;
}

int myth_exit(myth_t thread)
{
    kill(thread, SIGKILL);
    printf("Exit: %d\n", thread);
    return 0;
}

