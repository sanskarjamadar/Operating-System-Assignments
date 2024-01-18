typedef int thread_t;
int thread_create(thread_t *thread, int (*fn)(void *), void *arg);
int thread_join(thread_t thread);
int thread_exit(thread_t thread);

