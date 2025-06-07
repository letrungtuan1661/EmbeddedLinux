#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int numbers[SIZE];
int even_count = 0;
int odd_count = 0;

void* count_even(void* arg) {
    for (int i = 0; i < SIZE; ++i) {
        if (numbers[i] % 2 == 0) {
            even_count++;
        }
    }
    pthread_exit(NULL);
}

void* count_odd(void* arg) {
    for (int i = 0; i < SIZE; ++i) {
        if (numbers[i] % 2 != 0) {
            odd_count++;
        }
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));   // Generate random numbers
    for (int i = 0; i < SIZE; ++i) {
        numbers[i] = rand() % 100 + 1;
    }

    pthread_t t1, t2;
    pthread_create(&t1, NULL, count_even, NULL);
    pthread_create(&t2, NULL, count_odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Even count: %d\n", even_count);
    printf("Odd count: %d\n", odd_count);
    return 0;
}