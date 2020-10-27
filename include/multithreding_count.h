#ifndef INCLUDE_MULTUTHREDING_COUNT_H_
#define INCLUDE_MULTUTHREDING_COUNT_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t mutex;
    size_t value;
} data_t;

typedef struct args {
    size_t chunk_size;
    long file_size;
    char simbol;
    int threads_amount;
    char *path_to_file;
} args;

args *create_starting_args(char *path_to_rile, char simbol);

args *create_thread_args(void *starting_args);

void *thread_routine(void *starting_args);

#endif // INCLUDE_MULTUTHREDING_COUNT_H_