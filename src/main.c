#include "count.h"

int main(int argc, char *argv[]) {
    char *path_to_file;
    char simbol;

    if (input(argc, argv, &path_to_file, &simbol) == FAILURE) {
        return EXIT_FAILURE;
    }

    size_t counter = 0;
    if (count(path_to_file, simbol, &counter) == FAILURE) {
        return EXIT_FAILURE;
    }

    return 0;
}