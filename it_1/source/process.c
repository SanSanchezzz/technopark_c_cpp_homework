#include "types.h"
#include <stdio.h>

double average_quality(road_t *road_network, const int lenght, const int type_of_road, const int number_of_lanes)
{
    if (road_network == NULL || lenght < 0)
    {
        return NULL_PASSED;
    }

    double sum_road_len = 0;
    double result = 0;

    for (int i = 0; i < lenght; i++)
    {
          if (road_network[i].number_of_lanes == number_of_lanes &&
                road_network[i].type_of_road == type_of_road)
        {
            sum_road_len += road_network[i].lenght_of_road;
        }
    }

    if (sum_road_len == 0)
    {
        return NO_ROADS;
    }

    for (int i = 0; i < lenght; i++)
    {
        if (road_network[i].number_of_lanes == number_of_lanes &&
                road_network[i].type_of_road == type_of_road)
        {
            result += road_network[i].road_quality * (road_network[i].lenght_of_road / sum_road_len);
        }
    }

    return result;
}
