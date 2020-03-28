#include <gtest/gtest.h>

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

using namespace std;

using NanoSecs = std::chrono::duration<unsigned long long, std::nano>;
using TimePoint = std::chrono::steady_clock::time_point;

inline static TimePoint tick()
{
    return std::chrono::steady_clock::now();
}

inline static NanoSecs toNanoSecs(std::chrono::steady_clock::duration dur)
{
    return std::chrono::duration_cast<NanoSecs>(dur);
}
void test_print(position_t *pos_array, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("X = %lf | Y = %lf | Z = %lf\n", pos_array[i].x, pos_array[i].y, pos_array[i].z);
    }
}

TEST(test_realisation, data) {
    const char *file_name = "../other/data.txt";
    position_t result_parallel, result_sequential;
   int len;
    position_t *pos_array;

    read_data(&pos_array, &len, file_name);

    TimePoint begin;
    TimePoint end;

    begin = tick();
    average_value_sequential(&result_sequential, pos_array, len);
    end = tick();

    cout << "Sequential: " << toNanoSecs(end - begin).count() << '\n';

    begin = tick();
    average_value_parallel(&result_parallel, pos_array, len);
    end = tick();

    cout << "Parallel:   " << toNanoSecs(end - begin).count() << '\n';

    EXPECT_EQ((float)result_parallel.x, (float)result_sequential.x);
    EXPECT_EQ((float)result_parallel.y, (float)result_sequential.y);
    EXPECT_EQ((float)result_parallel.z, (float)result_sequential.z);

    free(pos_array);
}

TEST(test_realisation, data_big) {
    const char *file_name = "../other/data_big.txt";
    position_t result_parallel, result_sequential;
    int len;
    position_t *pos_array;

    read_data(&pos_array, &len, file_name);

    TimePoint begin;
    TimePoint end;

    begin = tick();
    average_value_sequential(&result_sequential, pos_array, len);
    end = tick();

    cout << "Sequential: " << toNanoSecs(end - begin).count() << '\n';

    begin = tick();
    average_value_parallel(&result_parallel, pos_array, len);
    end = tick();

    cout << "Parallel:   " << toNanoSecs(end - begin).count() << '\n';

    EXPECT_EQ((float)result_parallel.x, (float)result_sequential.x);
    EXPECT_EQ((float)result_parallel.y, (float)result_sequential.y);
    EXPECT_EQ((float)result_parallel.z, (float)result_sequential.z);

    free(pos_array);
}

TEST(test_realisation, data_big_big) {
    const char *file_name = "../other/data_big_big.txt";
    position_t result_parallel, result_sequential;
    int len;
    position_t *pos_array;

    read_data(&pos_array, &len, file_name);

    TimePoint begin;
    TimePoint end;

    begin = tick();
    average_value_sequential(&result_sequential, pos_array, len);
    end = tick();

    cout << "Sequential: " << toNanoSecs(end - begin).count() << '\n';

    begin = tick();
    average_value_parallel(&result_parallel, pos_array, len);
    end = tick();

    cout << "Parallel:   " << toNanoSecs(end - begin).count() << '\n';

    EXPECT_EQ((float)result_parallel.x, (float)result_sequential.x);
    EXPECT_EQ((float)result_parallel.y, (float)result_sequential.y);
    EXPECT_EQ((float)result_parallel.z, (float)result_sequential.z);

    free(pos_array);
}

TEST(test_realisation, data_big_big_big) {
    const char *file_name = "../other/data_big_big_big.txt";
    position_t result_parallel, result_sequential;
    int len;
    position_t *pos_array;

    read_data(&pos_array, &len, file_name);

    TimePoint begin;
    TimePoint end;

    begin = tick();
    average_value_sequential(&result_sequential, pos_array, len);
    end = tick();

    cout << "Sequential: " << toNanoSecs(end - begin).count() << '\n';

    begin = tick();
    average_value_parallel(&result_parallel, pos_array, len);
    end = tick();

    cout << "Parallel:   " << toNanoSecs(end - begin).count() << '\n';

    EXPECT_EQ((float)result_parallel.x, (float)result_sequential.x);
    EXPECT_EQ((float)result_parallel.y, (float)result_sequential.y);
    EXPECT_EQ((float)result_parallel.z, (float)result_sequential.z);

    free(pos_array);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
