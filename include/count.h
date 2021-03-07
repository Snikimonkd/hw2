#ifndef INCLUDE_COUNT_H_
#define INCLUDE_COUNT_H_

#include <stdio.h>
#include <stdlib.h>

enum my_error { SUCCESS, FAILURE };

enum my_error input(int argc, char **argv, char **path_to_file, char *simbol);

enum my_error count(char *path_to_file, char simbol, size_t *counter);

#endif // INCLUDE_COUNT_H_