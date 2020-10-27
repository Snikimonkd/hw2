#include "multithreding_count.h"
#include "count.h"
#include <pthread.h>
#include <unistd.h>

data_t counter = {PTHREAD_MUTEX_INITIALIZER, 0};

data_t number_of_chunk = {PTHREAD_MUTEX_INITIALIZER, 0};

args *create_starting_args(char *path_to_file, char simbol) {
    args *new_args = malloc(sizeof(args));
    if (new_args == NULL) {
        return NULL;
    }

    new_args->threads_amount = sysconf(_SC_NPROCESSORS_ONLN);
    if (new_args->threads_amount == -1) {
        free(new_args);
        return NULL;
    }

    if (path_to_file == NULL) {
        free(new_args);
        return NULL;
    }

    new_args->path_to_file = path_to_file;

    FILE *istream = fopen(path_to_file, "rt");
    if (istream == NULL) {
        free(new_args);
        return NULL;
    }
    if (fseek(istream, 0, SEEK_END) != 0) {
        free(new_args);
        fclose(istream);
        return NULL;
    }
    new_args->file_size = (long)ftell(istream);
    if (new_args->file_size == -1L) {
        free(new_args);
        fclose(istream);
        return NULL;
    }
    fclose(istream);

    new_args->chunk_size = new_args->file_size / new_args->threads_amount;

    new_args->simbol = simbol;

    return new_args;
}

args *create_thread_args(void *starting_args) {
    if (starting_args == NULL) {
        return NULL;
    }

    if (((args *)starting_args)->path_to_file == NULL) {
        return NULL;
    }

    args *thread_args = malloc(sizeof(args));
    if (thread_args == NULL) {
        return NULL;
    }

    thread_args->path_to_file = ((args *)starting_args)->path_to_file;

    thread_args->file_size = ((args *)starting_args)->file_size;

    thread_args->chunk_size = ((args *)starting_args)->chunk_size;

    thread_args->simbol = ((args *)starting_args)->simbol;

    thread_args->threads_amount = ((args *)starting_args)->threads_amount;

    return thread_args;
}

void *thread_routine(void *starting_args) {
    if (starting_args == NULL) {
        return NULL;
    }
    args *thread_args = create_thread_args(starting_args);
    if (thread_args == NULL) {
        return NULL;
    }

    if (thread_args->path_to_file == NULL) {
        free(thread_args);
        return NULL;
    }
    FILE *istream = fopen(thread_args->path_to_file, "rt");
    if (istream == NULL) {
        free(thread_args);
        return NULL;
    }

    pthread_mutex_t *mutex = &number_of_chunk.mutex;
    int errflag = pthread_mutex_lock(mutex);
    size_t chunk = 0;
    if (errflag != 0) {
        free(thread_args);
        fclose(istream);
        return NULL;
    }
    chunk = number_of_chunk.value;
    ++number_of_chunk.value;
    errflag = pthread_mutex_unlock(mutex);
    if (errflag != 0) {
        free(thread_args);
        fclose(istream);
        return NULL;
    }

    size_t left = chunk * thread_args->chunk_size;
    if (fseek(istream, left, SEEK_SET) != 0) {
        free(thread_args);
        fclose(istream);
        return NULL;
    }

    size_t right;
    if (chunk != (thread_args->threads_amount - 1)) {
        right = left + thread_args->chunk_size;

    } else {
        right = thread_args->file_size;
    }

    char new_char;
    size_t char_counter = 0;

    while (left < (right)) {
        if ((new_char = getc(istream)) == EOF) {
            free(thread_args);
            fclose(istream);
            return NULL;
        }

        if (new_char == thread_args->simbol) {
            ++char_counter;
        }
        ++left;
    }

    mutex = &counter.mutex;
    errflag = pthread_mutex_lock(mutex);
    if (errflag != 0) {
        free(thread_args);
        fclose(istream);
        return NULL;
    }
    counter.value += char_counter;
    errflag = pthread_mutex_unlock(mutex);
    if (errflag != 0) {
        free(thread_args);
        fclose(istream);
        return NULL;
    }
    fclose(istream);
    free(thread_args);
    return starting_args;
}

enum my_error count(char *path_to_file, char simbol, size_t *count_of_simbols) {
    if (path_to_file == NULL) {
        return FAILURE;
    }

    args *starting_args = create_starting_args(path_to_file, simbol);
    if (starting_args == NULL) {
        return FAILURE;
    }

    pthread_t threadIds[starting_args->threads_amount];

    number_of_chunk.value = 0;
    counter.value = 0;

    for (int i = 0; i < starting_args->threads_amount; i++) {
        int errflag = pthread_create(&threadIds[i], NULL, thread_routine,
                                     (void *)starting_args);
        if (errflag != 0) {
            return FAILURE;
        }
    }

    for (int i = 0; i < starting_args->threads_amount; i++) {
        int errflag = pthread_join(threadIds[i], NULL);
        if (errflag != 0) {
            return FAILURE;
        }
    }

    *count_of_simbols = counter.value;
    free(starting_args);
    return SUCCESS;
}