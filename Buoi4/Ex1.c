#include <pthread.h>
#include <stdio.h>

void* threadFunc(void* arg) {
    printf("Thread %ld: Hello from thread!\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];

    // Create 2 threads
    for (long i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, threadFunc, NULL);
    }

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads have finished.\n");
    return 0;
}