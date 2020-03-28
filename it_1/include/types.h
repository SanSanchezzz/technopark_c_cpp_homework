#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

#define OK 0

#define INCORRECT_DATA -1
#define ALLOCATE_ERROR -2
#define INCORRECT_INPUT -3
#define NO_ROADS -4
#define NULL_PASSED -5

typedef struct road road_t;
struct road
{
    unsigned int lenght_of_road;
    short int road_quality;
    short int number_of_lanes;
    short int type_of_road;
};

int read_data(road_t **road_network, size_t *lenght_array);
double average_quality(road_t *road_network, const int lenght, const int type_of_road, const int number_of_lanes);
int read_inquiry(int *type_of_road, int *number_of_lanes);

#endif
