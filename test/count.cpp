#include "gtest/gtest.h"
#include <string>

extern "C" {
#include "count.h"
}

TEST(count_lib_test, input_test1) {
    char **test_argv = nullptr;
    char *path_to_file = nullptr;
    char simbol = 'a';
    EXPECT_EQ(input(2, test_argv, &path_to_file, &simbol), FAILURE);
}

TEST(count_lib_test, input_test2) {
    int test_argc = 3;
    char *test_argv[3] = {"sd", nullptr, "d"};
    char *path_to_file;
    char simbol;
    EXPECT_EQ(input(test_argc, test_argv, &path_to_file, &simbol), FAILURE);
}

TEST(count_lib_test, input_test3) {
    int test_argc = 3;
    char *test_argv[3] = {"", "", nullptr};
    char *path_to_file;
    char simbol;
    EXPECT_EQ(input(test_argc, test_argv, &path_to_file, &simbol), FAILURE);
}

TEST(count_lib_test, input_test4) {
    int test_argc = 3;
    char *test_argv[3] = {"main", "path_to_file", "t"};
    char *path_to_file;
    char simbol;
    EXPECT_EQ(input(test_argc, test_argv, &path_to_file, &simbol), SUCCESS);
    EXPECT_STREQ(path_to_file, "path_to_file");
    EXPECT_EQ(simbol, 't');
}