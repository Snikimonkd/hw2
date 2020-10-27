#include "count.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *istream = fopen("stress_test", "w+t");
    for (size_t i = 0; i < 1024 * 1024 * 100; ++i) {
        if (i % (1024 * 1024) == 0) {
            fprintf(istream, "%c", 't');
        } else {
            fprintf(istream, "%c", 'a');
        }
    }
    fclose(istream);
    char *path_to_file = "stress_test";
    char simbol = 't';

    /*if (input(argc, argv, &path_to_file, &simbol) == FAILURE) {
        return EXIT_FAILURE;
    }*/

    size_t counter = 0;

    if (count(path_to_file, simbol, &counter) == FAILURE) {
        return EXIT_FAILURE;
    }

    printf("%ld", counter);
    return 0;
}