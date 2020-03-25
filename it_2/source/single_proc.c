#include "single_proc.h"

int average_value_sequential(position_t *result, position_t *positions, int len)
{
    for (int i = 0; i < len; i++)
    {
        (*result).x += positions[i].x;
        (*result).y += positions[i].y;
        (*result).z += positions[i].z;
    }

    (*result).x /= len;
    (*result).y /= len;
    (*result).z /= len;

    return OK;
}
