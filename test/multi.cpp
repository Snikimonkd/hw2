#include "gtest/gtest.h"
#include <string>

extern "C" {
#include "count.h"
#include "multithreding_count.h"
}

TEST(count_lib_test, multi_count_test1) {
    size_t counter;
    char *path_to_file = nullptr;
    char simbol;
    EXPECT_EQ(create_starting_args(path_to_file, simbol), nullptr);
}

TEST(count_lib_test, multi_count_test2) {
    size_t counter;
    FILE *istream = fopen("multi_count_test3", "w+t");
    EXPECT_NE(istream, nullptr);
    fclose(istream);
    char *path_to_file = "multi_count_test3";
    char simbol = 's';
    args *new_arg = create_starting_args(path_to_file, simbol);
    EXPECT_NE(new_arg, nullptr);
    EXPECT_EQ(new_arg->chunk_size, 0);
    EXPECT_EQ(new_arg->file_size, 0);
    EXPECT_STREQ(new_arg->path_to_file, "multi_count_test3");
    EXPECT_EQ(new_arg->simbol, 's');
    int i = sysconf(_SC_NPROCESSORS_ONLN);
    EXPECT_NE(i, -1);
    EXPECT_EQ(new_arg->threads_amount, i);
    free(new_arg);
}

TEST(count_lib_test, multi_count_test4) {
    args *new_args = NULL;
    EXPECT_EQ(create_thread_args(new_args), nullptr);
}

TEST(count_lib_test, multi_count_test5) {
    args new_args;
    new_args.path_to_file = NULL;
    EXPECT_EQ(create_thread_args(&new_args), nullptr);
}

TEST(count_lib_test, multi_count_test6) {
    args new_args;
    new_args.chunk_size = 1;
    new_args.file_size = 1;
    new_args.path_to_file = "1";
    new_args.simbol = '1';
    new_args.threads_amount = 1;
    args *thread_args = create_thread_args(&new_args);
    EXPECT_NE(thread_args, nullptr);
    EXPECT_EQ(thread_args->chunk_size, 1);
    EXPECT_EQ(thread_args->file_size, 1);
    EXPECT_STREQ(thread_args->path_to_file, "1");
    EXPECT_EQ(thread_args->simbol, '1');
    EXPECT_EQ(thread_args->threads_amount, 1);
    free(thread_args);
}

TEST(count_lib_test, multi_count_test7) {
    args *new_args = NULL;
    EXPECT_EQ(thread_routine(new_args), nullptr);
}

TEST(count_lib_test, multi_count_test8) {
    args new_args;
    new_args.path_to_file = NULL;
    EXPECT_EQ(thread_routine(&new_args), nullptr);
}

TEST(count_lib_test, multi_count_test9) {
    char *path_to_file = "multi_count_test9";
    char simbol = '1';
    FILE *istream = fopen(path_to_file, "w+t");
    EXPECT_NE(istream, nullptr);
    EXPECT_EQ(fprintf(istream, "%s", "1234567890"), 10);
    fclose(istream);
    args *starting_args = create_starting_args(path_to_file, simbol);
    EXPECT_NE(starting_args, nullptr);
    EXPECT_EQ(starting_args->file_size, 10);
    EXPECT_STREQ(starting_args->path_to_file, path_to_file);
    EXPECT_EQ(starting_args->simbol, '1');
    int i = sysconf(_SC_NPROCESSORS_ONLN);
    EXPECT_NE(i, -1);
    EXPECT_EQ(starting_args->threads_amount, i);
    EXPECT_NE(thread_routine(starting_args), nullptr);
    free(starting_args);
}

TEST(count_lib_test, multi_count_test10) {
    char *path_to_file = NULL;
    size_t in = 0;
    EXPECT_EQ(count(path_to_file, 'c', &in), FAILURE);
}

TEST(count_lib_test, multi_count_test11) {
    FILE *istream = fopen("multi_count_test11", "w+t");
    EXPECT_NE(istream, nullptr);
    EXPECT_EQ(fprintf(istream, "%s", "1234567890"), 10);
    fclose(istream);
    char *path_to_file = "multi_count_test11";
    size_t in = 0;
    EXPECT_EQ(count(path_to_file, '1', &in), SUCCESS);
}
