#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void print_road_network(road_t *road_network, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("len = %d| road_quality = %d| num_Lan = %d| type_of_road = %d\n",
                road_network[i].lenght_of_road, road_network[i].road_quality,
                road_network[i].number_of_lanes, road_network[i].type_of_road);
    }
}

int main()
{
    road_t *road_network = NULL;
    int lenght;
    double result;
    int flag;

    flag = read_data(&road_network, &lenght);
    if (flag == OK)
    {
        int inquiry_type;
        int inquiry_number;

        if (read_inquiry(&inquiry_type, &inquiry_number) == OK)
        {
            result = average_quality(road_network, lenght, inquiry_type, inquiry_number);
            if (result != NO_ROADS)
            {
            printf("Result = %f\n", result);
            }
            else
            {
                printf("There are no roads with the given parameters.\n");
            }
        }
        else
        {
            printf("Error entering request for average road quality.\n");
        }

        free(road_network);
    }
    else if (flag == INCORRECT_INPUT)
    {
        printf("Error entering road network information.\n");
    }
    else if (flag == ALLOCATE_ERROR)
    {
        printf("Error allocating memory.\n");
    }

    return OK;
}
