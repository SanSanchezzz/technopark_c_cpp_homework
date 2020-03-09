#include <stdlib.h>
#include "types.h"

road_t *allocate_struct(int number)
{
    road_t *road_network;

    road_network = (road_t*)malloc(sizeof(road_t) * number);

    return road_network;
}
