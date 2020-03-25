#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <dlfcn.h>

#include "types.h"
#include "read_data.h"
/*#include "single_proc.h"*/
#include "multy_proc.h"

void test_print(position_t *pos_array, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("X = %f | Y = %f | Z = %f\n", pos_array[i].x, pos_array[i].y, pos_array[i].z);
    }
}

void error_handler(int err_code);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return -1;
    }

    char *file_name = argv[1];

    int err_code;

    position_t *pos_array = NULL;
    int len;

    err_code = read_data(&pos_array, &len, file_name);
    if (err_code != OK)
    {
        error_handler(err_code);
        return err_code;
    }
    /*test_print(pos_array, len);*/

    position_t result_sequential;
    err_code = average_value_sequential(&result_sequential, pos_array, len);
    if (err_code != OK)
    {
        free(pos_array);
        error_handler(err_code);
        return err_code;
    }
    test_print(&result_sequential, 1);

    position_t result_parallel;
    err_code = average_value_parallel(&result_parallel, pos_array, len);
    if (err_code != OK)
    {
        free(pos_array);
        error_handler(err_code);
        return err_code;
    }
    test_print(&result_parallel, 1);


    free(pos_array);

    return OK;
}

void error_handler(int err_code)
{
    switch (err_code)
    {
        case ERROR_DATA:
            printf("Err data\n");
            break;
        case ERROR_FILE:
            printf("Err file\n");
            break;
        case ERROR_ALLOC:
            printf("allerr\n");
            break;
        default:
            printf("err\n");
    }
}
