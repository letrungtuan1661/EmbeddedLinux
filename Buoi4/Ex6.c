#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000       
#define NUM_THREADS 4

long long global_sum = 0;
int *data = NULL;              
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;
            
typedef struct {
    int start;                 
    int end;                  
} thread_arg_t;

void* partial_sum(void *arg_void)
{
    thread_arg_t *arg = (thread_arg_t *)arg_void;

    long long local_sum = 0;
    for (int i = arg->start; i < arg->end; ++i)
        local_sum += data[i];
    
    pthread_mutex_lock(&sum_mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);

    pthread_exit(NULL);
}

int main(void)
{
    /* Allocate and fill the array */
    data = malloc(sizeof(int) * ARRAY_SIZE);
    if (!data) {
        printf("Malloc error!");
        return 1;
    }

    for (int i = 0; i < ARRAY_SIZE; ++i)
        data[i] = 1;              

    /* Prepare thread arguments */
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];
    int slice = ARRAY_SIZE / NUM_THREADS;

    for (int t = 0; t < NUM_THREADS; ++t) {
        args[t].start = t * slice;
        args[t].end   = (t == NUM_THREADS - 1) ? ARRAY_SIZE
                                               : (t + 1) * slice;
    }

    /* Launch the threads */
    for (int t = 0; t < NUM_THREADS; ++t)
        pthread_create(&threads[t], NULL, partial_sum, &args[t]);

    /* Wait for all threads to finish */
    for (int t = 0; t < NUM_THREADS; ++t)
        pthread_join(threads[t], NULL);

    /* Report the result */
    printf("Total sum  = %lld\n", global_sum);

    /* Clean up */
    free(data);
    pthread_mutex_destroy(&sum_mutex);

    return 0;
}