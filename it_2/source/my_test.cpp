#include <gtest/gtest.h>
#include "my_test.h"

extern "C" {
    #include "types.h"
    #include "read_data.h"
    #include "multy_proc.h"
    #include "single_proc.h"
    #include "single_proc.h"
    #include <sys/sysinfo.h>
}

#include <iostream>
#include <chrono>
#include <string>

void test_print(position_t *pos_array, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("X = %f | Y = %f | Z = %f\n", pos_array[i].x, pos_array[i].y, pos_array[i].z);
    }
}

TEST(test_realisation, big_data) {
    const char *file_name = "../other/simple_test.txt";
    position_t result_parallel,
            result_sequential;
    int len;
    position_t *pos_array;

    read_data(&pos_array, &len, file_name);

    //for (int i = 0; i < len;)

    {
        Timer();
        average_value_sequential(&result_sequential, pos_array, len);
    }

    {
        Timer();
        average_value_parallel(&result_sequential, pos_array, len);
    }

    EXPECT_EQ(result_parallel.x, result_sequential.x);
    EXPECT_EQ(result_parallel.y, result_sequential.y);
    EXPECT_EQ(result_parallel.z, result_sequential.z);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
