#include <stdio.h>
#include "thread.h"

void *child_thread(void *arg) {
    printf("Child thread started\n");
    printf("Child thread exiting\n");
    thread_exit();
}

int main() {
    thread_t thread;
    thread_create(&thread, child_thread, NULL);
    printf("Parent thread waiting for child\n");
    thread_join(&thread);
    printf("Parent thread exiting\n");
    return 0;
}

