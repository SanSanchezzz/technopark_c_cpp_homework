#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <dlfcn.h>

#include "types.h"
#include "read_data.h"

void test_print(const position_t *pos_array, const int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("X = %f | Y = %f | Z = %f\n", pos_array[i].x, pos_array[i].y, pos_array[i].z);
    }
}

void print_pos(const position_t *pos)
{
    if (pos)
        printf("| %lf | %lf | %lf |\n", pos->x, pos->y, pos->z);
}

void error_handler(int err_code);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return -1;
    }

    void *my_lib;
    my_lib = dlopen("../build/libmulty_proc.so", RTLD_LAZY);
    if (!my_lib)
    {
        error_handler(ERROR_LIB);
    }

    char *file_name = argv[1];

    int err_code;

    position_t *pos_array = NULL;
    int len;

    err_code = read_data(&pos_array, &len, file_name);
    if (err_code != OK)
    {
        error_handler(err_code);
        dlclose(my_lib);
        return err_code;
    }

    position_t result_sequential;
    err_code = average_value_sequential(&result_sequential, pos_array, len);
    if (err_code != OK)
    {
        free(pos_array);
        error_handler(err_code);
        dlclose(my_lib);
        return err_code;
    }
    printf("sequential = ");
    print_pos(&result_sequential);

    position_t result_parallel;
    int(*parallel_proc)(position_t *, const position_t *, const int) = dlsym(my_lib, "average_value_parallel");
    if (!parallel_proc)
    {
        free(pos_array);
        error_handler(ERROR_LIB);
        dlclose(my_lib);
        return ERROR_LIB;
    }
    err_code = parallel_proc(&result_parallel, pos_array, len);
    if (err_code != OK)
    {
        free(pos_array);
        error_handler(err_code);
        dlclose(my_lib);
        return err_code;
    }
    printf("parallel = ");
    print_pos(&result_parallel);

    dlclose(my_lib);
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
        case ERROR_LIB:
            printf("liberr\n");
            break;
        default:
            printf("err\n");
    }
}
