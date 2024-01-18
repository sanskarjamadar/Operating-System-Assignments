#ifndef THREAD_H
#define THREAD_H

#include <sched.h>

#define STACK_SIZE (1024 * 1024)

typedef struct thread_t {
    pid_t pid;
    void *stack;
} thread_t;

void thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg);
void thread_join(thread_t *thread);
void thread_exit();

#endif

