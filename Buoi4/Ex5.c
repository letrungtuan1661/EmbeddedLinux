#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    for (int i = 0; i < 5; ++i) {
        pthread_rwlock_rdlock(&rwlock);
        printf("Reader %ld: read data = %d\n", (long)arg, data);
        pthread_rwlock_unlock(&rwlock);
        sleep(1); 
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    for (int i = 0; i < 5; ++i) {
        pthread_rwlock_wrlock(&rwlock);
        data += 1;
        printf("Writer %ld: wrote data = %d\n", (long)arg, data);
        pthread_rwlock_unlock(&rwlock);
        sleep(2); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t readers[5], writers[2];

    for (long i = 0; i < 5; ++i)    // Readers
        pthread_create(&readers[i], NULL, reader, (void*)i);
    for (long i = 0; i < 2; ++i)    // Writers
        pthread_create(&writers[i], NULL, writer, (void*)i);

    for (int i = 0; i < 5; ++i)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; ++i)
        pthread_join(writers[i], NULL);

    pthread_rwlock_destroy(&rwlock);
    printf("Final data = %d\n", data);
    return 0;
}