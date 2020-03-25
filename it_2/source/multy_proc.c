#include "multy_proc.h"

int *set_borders(int borders_qty, int len);
void border_sum(const int left_border, const int right_border, const position_t *positions, position_t *result);
void child_work(const position_t *positions, const int *borders, const int num_child, position_t *tmp_result);

int simple_example(position_t *result, const position_t *positions, const int len)
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

int average_value_parallel(position_t *result, const position_t *positions, const int len)
{
    if (positions == NULL || len <= 0)
    {
        return ERROR_FUNC;
    }

    result->x = 0;
    result->y = 0;
    result->z = 0;

    int child_qty = get_nprocs();

    pid_t pid;

    if (len < child_qty)
    {
        simple_example(result, positions, len);
        return OK;
    }

    int *borders = set_borders(child_qty, len);
    if (!borders)
    {
        return ERROR_ALLOC;
    }

    position_t *tmp_result = mmap(NULL, sizeof(position_t) * child_qty, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < child_qty; i++)
    {
        tmp_result[i].x = 0;
        tmp_result[i].y = 0;
        tmp_result[i].z = 0;
    }

    for (int i = 0; i < child_qty; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Fork\n");

            exit(FORK_ERROR);
        }
        if (pid == 0)
        {
            child_work(positions, borders, i, &tmp_result[i]);
            exit(EXIT_SUCCESS);
        }
    }
    int status;
    pid_t child_pid;

    while ((child_pid = wait(&status)) != -1 && errno != ECHILD)
    {
        if (WIFEXITED(status))
        {
/*            printf("parent: child %d terminated normally with %d rc\n",*/
                   /*child_pid, WEXITSTATUS(status));*/
        }
        else
        {
            printf("parent: child %d terminated abnormally with %d rc\n",
                   child_pid, WEXITSTATUS(status));
        }
    }

    if (errno != ECHILD)
    {
        perror("wait");

        exit(1);
    }
    for (int i = 0; i < child_qty; i++)
    {
        result->x += tmp_result[i].x;
        result->y += tmp_result[i].y;
        result->z += tmp_result[i].z;
    }

    result->x = result->x / len;
    result->y = result->y / len;
    result->z = result->z / len;

    munmap(tmp_result, sizeof(position_t) * child_qty);
    free(borders);

    return OK;
}

void border_sum(const int left_border, const int right_border, const position_t *positions, position_t *result)
{
    for (int i = left_border; i <= right_border; i++)
    {
        (*result).x += positions[i].x;
        (*result).y += positions[i].y;
        (*result).z += positions[i].z;
    }
}

void child_work(const position_t *positions, const int *borders, const int num_child, position_t *tmp_result)
{
    if (num_child == 0)
    {
        border_sum(0, borders[0], positions, tmp_result);
    }
    else
    {
        border_sum(borders[num_child - 1] + 1, borders[num_child], positions, tmp_result);
    }
}

int *set_borders(int borders_qty, int len)
{
    if (borders_qty <= 0)
    {
        return NULL;
    }

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
