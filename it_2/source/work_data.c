#include <types.h>
#include <stdio.h>
#include <stdlib.h>

int read_data(position_t **pos_array, int *len, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        return ERROR_FILE;
    }

    if (fscanf(file, "%d", len) != 1)
    {
        fclose(file);
        return ERROR_DATA;
    }

    if (*len <= 0)
    {
        fclose(file);
        return ERROR_DATA;
    }

    printf("len = %d\n", *len);

    *pos_array = malloc(sizeof(position_t) * (*len));
    if (!(*pos_array))
    {
        fclose(file);
        return ERROR_ALLOC;
    }

    for (int i = 0; i < *len; i++)
    {
        if (fscanf(file, "%lf", &(*pos_array)[i].x) != 1 ||
            fscanf(file, "%lf", &(*pos_array)[i].y) != 1 ||
            fscanf(file, "%lf", &(*pos_array)[i].z) != 1)
        {
            fclose(file);
            free(*pos_array);

            return ERROR_DATA;
        }
    }

    fclose(file);

    return OK;
}
