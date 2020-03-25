#include "multy_proc.h"

int *set_borders(int borders_qty, int len);
void border_sum(int left_border, int right_border, position_t *positions, position_t *result);
void child_work(position_t *positions, position_t *result, int *borders, int num_child);

int average_value_parallel(position_t *result, position_t *positions, int len)
{
    position_t *result_tmp = mmap(NULL, sizeof(position_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    result_tmp->x = 0;
    result_tmp->y = 0;
    result_tmp->z = 0;

    int child_qty = get_nprocs();

    pid_t pid, child_pids[child_qty];
// проверка на длину вектора и кол-во процессов
    int *borders = set_borders(child_qty, len);
    if (!borders)
    {
        return ERROR_ALLOC;
    }

    for (int i = 0; i < child_qty; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            free(borders);
            printf("Fork Err\n");
        }
        if (pid == 0)
        {
            child_work(positions, result_tmp, borders, i);
            exit(EXIT_SUCCESS);
        }
        else
        {
            child_pids[i] = pid;
        }
    }

    free(borders);

/*    for (int i = 0; i < child_qty; i++)*/
    /*{*/
        /*int status;*/

        /*if (wait(&status))*/
        /*{*/
            /*return -1;*/
        /*}*/
    /*}*/

    int status;

    for (int i = 0; i < child_qty; i++)
    {
        waitpid(child_pids[i], &status, 0);

        if (WIFSIGNALED(status))
        {
            printf("Wait error\n");
        }
    }

    result->x = result_tmp->x / len;
    result->y = result_tmp->y / len;
    result->z = result_tmp->z / len;

    munmap(result_tmp, sizeof(position_t));

    return OK;
}

void border_sum(int left_border, int right_border, position_t *positions, position_t *result)
{
    for (int i = left_border; i <= right_border; i++)
    {
        (*result).x += positions[i].x;
        (*result).y += positions[i].y;
        (*result).z += positions[i].z;
    }
}

void child_work(position_t *positions, position_t *result, int *borders, int num_child)
{
    if (num_child == 0)
    {
        border_sum(0, borders[0], positions, result);
    }
    else
    {
        border_sum(borders[num_child - 1] + 1, borders[num_child], positions, result);
    }
}

int *set_borders(int borders_qty, int len)
{
    int *borders = malloc(sizeof(int) * borders_qty);
    if (!borders)
    {
        return NULL;
    }

    int step = len / borders_qty;

    borders[0] = step - 1;
    for (int i = 1; i < borders_qty; i++)
    {
        if (i == borders_qty- 1)
        {
            borders[i] = len - 1;
        }
        else
        {
            borders[i] = borders[i - 1] + step;
        }
    }

    return borders;
}
