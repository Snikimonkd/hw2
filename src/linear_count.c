#include "count.h"

enum my_error count(char *path_to_file, char simbol, size_t *counter) {
    if (path_to_file == NULL) {
        return FAILURE;
    }

    FILE *istream = fopen(path_to_file, "rt");
    if (istream == NULL) {
        return FAILURE;
    }

    char c = getc(istream);
    while (c != EOF) {
        if (c == simbol) {
            ++(*counter);
        }
        c = getc(istream);
    }

    if (ferror(istream)) {
        fclose(istream);
        return FAILURE;
    }

    fclose(istream);
    return SUCCESS;
}
