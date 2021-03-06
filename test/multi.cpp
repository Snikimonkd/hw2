#include "gtest/gtest.h"
#include <chrono>
#include <string>

extern "C" {
#include "count.h"
#include "multithreding_count.h"
}

TEST(count_lib_test, multi_stress_test) {
    char *path_to_file = "multi_stress_test";
    char simbol = 'b';

    FILE *istream = fopen(path_to_file, "w+t");
    EXPECT_NE(istream, nullptr);
    for (size_t i = 0; i < 1024 * 1024 * 100; ++i) {
        if (i % (1024 * 1024) == 0) {
            EXPECT_EQ(fprintf(istream, "%c", simbol), 1);
        } else {
            EXPECT_EQ(fprintf(istream, "%c", simbol + 1), 1);
        }
    }
    fclose(istream);

    size_t counter = 0;

    std::chrono::duration<double> delta;

    double average_time = 0;

    for (size_t i = 0; i < 5; ++i) {
        auto start = std::chrono::steady_clock::now();
        EXPECT_NE(count(path_to_file, simbol, &counter), FAILURE);

        EXPECT_EQ(counter, (size_t)100);

        counter = 0;

        auto end = std::chrono::steady_clock::now();

        delta = end - start;
        average_time += delta.count();
    }

    istream = fopen(path_to_file, "w+t");
    EXPECT_NE(istream, nullptr);

    EXPECT_NE(fprintf(istream, "%s%f", "Время работы:", average_time / 5), 0);
    fclose(istream);
}

TEST(count_lib_test, multi_count_test1) {
    char *path_to_file = nullptr;
    char simbol = 'a';
    EXPECT_EQ(create_starting_args(path_to_file, simbol), nullptr);
}

TEST(count_lib_test, multi_count_test2) {
    FILE *istream = fopen("multi_count_test2", "w+t");
    EXPECT_NE(istream, nullptr);
    fclose(istream);
    char *path_to_file = "multi_count_test2";
    char simbol = 's';
    args *new_arg = create_starting_args(path_to_file, simbol);
    EXPECT_NE(new_arg, nullptr);
    EXPECT_EQ(new_arg->chunk_size, (size_t)0);
    EXPECT_EQ(new_arg->file_size, (long)0);
    EXPECT_STREQ(new_arg->path_to_file, "multi_count_test2");
    EXPECT_EQ(new_arg->simbol, 's');
    int i = sysconf(_SC_NPROCESSORS_ONLN);
    EXPECT_NE(i, -1);
    EXPECT_EQ(new_arg->threads_amount, i);
    free(new_arg);
}

TEST(count_lib_test, multi_count_test3) {
    args *new_args = NULL;
    EXPECT_EQ(create_thread_args(new_args), nullptr);
}

TEST(count_lib_test, multi_count_test4) {
    args new_args;
    new_args.path_to_file = NULL;
    EXPECT_EQ(create_thread_args(&new_args), nullptr);
}

TEST(count_lib_test, multi_count_test5) {
    args new_args;
    new_args.chunk_size = 1;
    new_args.file_size = 1;
    new_args.path_to_file = "1";
    new_args.simbol = '1';
    new_args.threads_amount = 1;
    args *thread_args = create_thread_args(&new_args);
    EXPECT_NE(thread_args, nullptr);
    EXPECT_EQ(thread_args->chunk_size, (size_t)1);
    EXPECT_EQ(thread_args->file_size, (long)1);
    EXPECT_STREQ(thread_args->path_to_file, "1");
    EXPECT_EQ(thread_args->simbol, '1');
    EXPECT_EQ(thread_args->threads_amount, 1);
    free(thread_args);
}

TEST(count_lib_test, multi_count_test6) {
    args *new_args = NULL;
    EXPECT_EQ(thread_routine(new_args), nullptr);
}

TEST(count_lib_test, multi_count_test7) {
    args new_args;
    new_args.path_to_file = NULL;
    EXPECT_EQ(thread_routine(&new_args), nullptr);
}

TEST(count_lib_test, multi_count_test9) {
    char *path_to_file = NULL;
    size_t in = 0;
    EXPECT_EQ(count(path_to_file, 'c', &in), FAILURE);
}

TEST(count_lib_test, multi_count_test10) {
    FILE *istream = fopen("multi_count_test10", "w+t");
    EXPECT_NE(istream, nullptr);
    EXPECT_EQ(fprintf(istream, "%s", "1234567890"), 10);
    fclose(istream);
    char *path_to_file = "multi_count_test10";
    size_t in = 0;
    EXPECT_EQ(count(path_to_file, '1', &in), SUCCESS);
}
