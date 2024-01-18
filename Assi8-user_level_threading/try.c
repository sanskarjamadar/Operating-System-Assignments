#include <stdio.h>
#include "myth.h"

int x = 20;

int f(void *arg) {
    int p = *(int *)arg;
    printf("%d x= %d\n", p, x);
    return 0;
}

int main() {
    myth_t tid[3];
    int args[3], j, k;

    for(k = 0; k < 3; k++) {
        args[k] = 10 + k;
        myth_create(&tid[k], f, &tid[k]);
    }

    myth_exit(tid[2]);
    for(k = 0; k < 3; k++) {
        myth_join(tid[k]);
    }
    
    return 0;
}

