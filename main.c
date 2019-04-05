#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int n = 1000;
int v1[1000], v2[1000], v3[1000];
int threads = 10;

void * sum (void * arg) {
    int begin = (int) arg;

    int i;

    for (i = (begin * n / threads); i < (begin + 1) * n / threads; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

int main() {
    int i;

    for(i = 0; i < n; i++) {
        v1[i] = 1;
        v2[i] = 1;
    }

    pthread_t th[threads];

    for(i = 0; i < threads; i++)
        pthread_create(&th[i], NULL, sum, i);

    for(i = 0; i < threads; i++)
        pthread_join(th[i], NULL);

    printf("[");
    for(i = 0; i < n-1; i++) {
        printf("%d, ", v3[i]);
    }
    printf("%d]", v3[n-1]);

    return 0;
}