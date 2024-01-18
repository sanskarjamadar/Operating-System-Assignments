typedef int myth_t;
int myth_create(myth_t *thread, int (*fn)(void *), void *arg);
int myth_join(myth_t thread);
int myth_exit(myth_t thread);

