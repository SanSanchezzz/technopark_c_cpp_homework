#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int read_inquiry(int *type_of_road, int *number_of_lanes)
{
    printf("Type of road and number of lanes: ");
    if (scanf("%d", type_of_road) != 1 ||
        scanf("%d", number_of_lanes) != 1)
    {
        return INCORRECT_INPUT;
    }
    else if (*type_of_road <= 0 || *number_of_lanes <= 0)
    {
        return INCORRECT_INPUT;
    }
    return OK;
}

int read_record(road_t *record)
{
    if (scanf("%d", &record->lenght_of_road) != 1 ||
        scanf("%hd", &record->type_of_road) != 1 ||
        scanf("%hd", &record->road_quality) != 1 ||
        scanf("%hd", &record->number_of_lanes) != 1)
    {
        return INCORRECT_INPUT;;
    }
     if(record->lenght_of_road <= 0 ||
        record->road_quality < 0 || record->road_quality > 100 ||
        record->number_of_lanes < 1 ||
        record->type_of_road <= 0)
     {
         return INCORRECT_INPUT;
     }

    return OK;
}

int read_data(road_t **road_network, size_t *lenght_array)
{
    printf("Enter the number of entries: ");
    if (scanf("%ld", lenght_array) != 1)
    {
        return INCORRECT_INPUT;
    }

    if ((*lenght_array) <= 0)
    {
        return INCORRECT_INPUT;
    }

    *road_network = (road_t*)malloc(sizeof(road_t) * (*lenght_array));
    if (!(*road_network))
    {
        return ALLOCATE_ERROR;
    }

    printf("Record input format:\n");
    printf("<road length> <type of roadway> <coverage quality> <number of traffic lanes>\n");
    for (size_t i = 0; i < *lenght_array; i++)
    {
        printf("Record %ld: ", i + 1);
        if ((read_record(&(*road_network)[i]))!= 0)
        {
            free(*road_network);
            return INCORRECT_INPUT;
        }
        printf("\n");
    }

    return OK;
}
