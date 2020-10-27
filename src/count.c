#include "count.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum my_error input(int argc, char **argv, char **path_to_file, char *simbol) {
    if (argc != 3) {
        return FAILURE;
    }

    if (argv[1] == NULL) {
        return FAILURE;
    }

    *path_to_file = argv[1];

    if (argv[2] == NULL) {
        return FAILURE;
    }
    *simbol = argv[2][0];

    return SUCCESS;
}