#include "gtest/gtest.h"
#include <chrono>
#include <string>

extern "C" {
#include "count.h"
}

TEST(count_lib_test, linear_stress_test) {
    char *path_to_file = "linear_stress_test";
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

        EXPECT_EQ(counter, 100);

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
