#include <gtest/gtest.h>

extern "C"
{
#include "types.h"
};

void compare_array(road_t *array_1, int len_1, road_t *array_2, int len_2)
{
    ASSERT_EQ(len_1, len_2);

    for (int i = 0; i < len_1; i++)
    {
        ASSERT_EQ(array_1[i].lenght_of_road, array_2[i].lenght_of_road);
        ASSERT_EQ(array_1[i].road_quality, array_2[i].road_quality);
        ASSERT_EQ(array_1[i].number_of_lanes, array_2[i].number_of_lanes);
        ASSERT_EQ(array_1[i].type_of_road, array_2[i].type_of_road);
    }
}


TEST(process_func, input_nullptr)
{
    road_t *road_network = NULL;
    double result = average_quality(road_network, 1, 1, 1);
    EXPECT_EQ(result, NULL_PASSED);
}

TEST(process_func, correct_work)
{
    freopen("../test_in/in_1.txt", "r", stdin);

    road_t *road_network;
    int len;
    int result;

    read_data(&road_network, &len);

    result = average_quality(road_network, len, 1, 2);

    ASSERT_EQ(result, 70);

    free(road_network);
}

TEST(process_func, no_roads)
{
    freopen("../test_in/in_2.txt", "r", stdin);

    road_t *road_network;
    int len;
    int result;

    read_data(&road_network, &len);

    result = average_quality(road_network, len, 2, 2);

    ASSERT_EQ(result, NO_ROADS);

    free(road_network);
}

TEST(read_func, correct_input)
{
    freopen("../test_in/in_1.txt", "r", stdin);

    road_t *road_network;
    int len_1;
    int len_2 = 2;
    road_t expect_array[len_2];

    expect_array[0].lenght_of_road = 50000;
    expect_array[0].road_quality = 70;
    expect_array[0].number_of_lanes = 2;
    expect_array[0].type_of_road = 1;

    expect_array[1].lenght_of_road = 5000;
    expect_array[1].road_quality = 70;
    expect_array[1].number_of_lanes = 2;
    expect_array[1].type_of_road = 1;

    int result = read_data(&road_network, &len_1);

    ASSERT_EQ(result, OK);
    compare_array(road_network, len_1, expect_array, len_2);

    free(road_network);
}

TEST(read_func, incorrect_input_1)
{
    freopen("../test_in/in_3.txt", "r", stdin);

    road_t *road_network;
    int len;

    int result = read_data(&road_network, &len);

    ASSERT_EQ(result, INCORRECT_INPUT);
}

TEST(read_func, incorrect_input_2)
{
    freopen("../test_in/in_4.txt", "r", stdin);

    road_t *road_network;
    int len;

    int result = read_data(&road_network, &len);

    ASSERT_EQ(result, INCORRECT_INPUT);
}

TEST(read_func, incorrect_input_3)
{
    freopen("../test_in/in_5.txt", "r", stdin);

    road_t *road_network;
    int len;

    int result = read_data(&road_network, &len);

    ASSERT_EQ(result, INCORRECT_INPUT);
}

TEST(read_func, incorrect_input_4)
{
    freopen("../test_in/in_6.txt", "r", stdin);

    road_t *road_network;
    int len;

    int result = read_data(&road_network, &len);

    ASSERT_EQ(result, INCORRECT_INPUT);
}

TEST(read_func_inquiry, correct_work)
{
    freopen("../test_in/in_7.txt", "r", stdin);

    int flag;
    int type_of_road, number_of_lanes;

    flag = read_inquiry(&type_of_road, &number_of_lanes);

    ASSERT_EQ(flag, OK);
    ASSERT_EQ(type_of_road, 2);
    ASSERT_EQ(number_of_lanes, 2);
}

TEST(read_func_inquiry, incorrect_input_1)
{
    freopen("../test_in/in_8.txt", "r", stdin);

    int flag;
    int type_of_road, number_of_lanes;

    flag = read_inquiry(&type_of_road, &number_of_lanes);

    ASSERT_EQ(flag, INCORRECT_INPUT);
}

TEST(read_func_inquiry, incorrect_input_2)
{
    freopen("../test_in/in_9.txt", "r", stdin);

    int flag;
    int type_of_road, number_of_lanes;

    flag = read_inquiry(&type_of_road, &number_of_lanes);

    ASSERT_EQ(flag, INCORRECT_INPUT);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
