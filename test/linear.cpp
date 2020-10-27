#include "gtest/gtest.h"
#include <string>

extern "C" {
#include "count.h"
}

TEST(count_lib_test, linear_count_test1) {
    size_t counter;
    char *path_to_file = NULL;
    char simbol;
    EXPECT_EQ(count(path_to_file, simbol, &counter), FAILURE);
}

TEST(count_lib_test, linear_count_test2) {
    FILE *istream = fopen("linear_count_test2", "w+r");
    EXPECT_NE(istream, nullptr);
    EXPECT_EQ(fprintf(istream, "a"), 1);
    fclose(istream);
    size_t counter = 0;
    char simbol = 'a';
    EXPECT_EQ(count("linear_count_test2", simbol, &counter), SUCCESS);
    EXPECT_EQ(counter, 1);
}
