#include <stdlib.h>
#include <sys/wait.h>
#include "thread.h"
#define _GNU_SOURCE  
#include <linux/sched.h>

void thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg) {
    thread->stack = malloc(STACK_SIZE);
    if (!thread->stack) {
        exit(EXIT_FAILURE);
    }
    thread->pid = clone(start_routine, (char *)thread->stack + STACK_SIZE, CLONE_VM | SIGCHLD, arg);
    if (thread->pid == -1) {
        exit(EXIT_FAILURE);
    }
}

void thread_join(thread_t *thread) {
    waitpid(thread->pid, NULL, 0);
    free(thread->stack);
}

void thread_exit() {
    exit(EXIT_SUCCESS);
}

