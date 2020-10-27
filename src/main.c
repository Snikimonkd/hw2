#include "count.h"
#include <sys/time.h>

long mtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    long mt = (long)t.tv_sec * 1000 + t.tv_usec / 1000;
    return mt;
}

int main(int argc, char *argv[]) {
    char *path_to_file;
    char simbol;

    if (input(argc, argv, &path_to_file, &simbol) == FAILURE) {
        return EXIT_FAILURE;
    }

    FILE *istream = fopen(path_to_file, "w+t");
    for (size_t i = 0; i < 1024 * 1024 * 100; ++i) {
        if (i % (1024 * 1024) == 0) {
            if (fprintf(istream, "%c", simbol) != 1) {
                fclose(istream);
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(istream, "%c", simbol + 1) != 1) {
                fclose(istream);
                return EXIT_FAILURE;
            }
        }
    }
    fclose(istream);

    size_t counter = 0;

    long average_time = 0;

    for (size_t i = 0; i < 5; ++i) {
        long time = mtime();
        if (count(path_to_file, simbol, &counter) == FAILURE) {
            return EXIT_FAILURE;
        }

        if (counter != 100) {
            return EXIT_FAILURE;
        }
        counter = 0;

        time = mtime() - time;
        average_time += time;
    }

    istream = fopen(path_to_file, "w+t");
    if (istream == NULL) {
        return EXIT_FAILURE;
    }

    if (fprintf(istream, "%s%ld", "Время работы:", average_time / 5) < 0) {
        fclose(istream);
        return EXIT_FAILURE;
    }

    fclose(istream);
    return 0;
}