#include "count.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

long mtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    long mt = (long)t.tv_sec * 1000 + t.tv_usec / 1000;
    return mt;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    /*FILE *istream = fopen("stress_test2", "w+t");
    for (size_t i = 0; i < 1024 * 1024 * 100; ++i) {
        fprintf(istream, "%c", rand() % 120 + 65);
    }
    fclose(istream);*/
    char *path_to_file = "stress_test1";
    char simbol = 't';

    /*if (input(argc, argv, &path_to_file, &simbol) == FAILURE) {
        return EXIT_FAILURE;
    }*/

    size_t counter = 0;

    long t0 = mtime();

    if (count(path_to_file, simbol, &counter) == FAILURE) {
        return EXIT_FAILURE;
    }
    t0 = mtime() - t0;

    printf("Время работы прогаммы: %ld\n", t0);
    printf("Количество символов в файле: %ld\n", counter);
    return 0;
}