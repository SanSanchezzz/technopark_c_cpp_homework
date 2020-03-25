#ifndef MULTY_PROC_H
#define MULTY_PROC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <ctype.h>

#include "types.h"

int *set_borders(int borders_qty, int len);
void border_sum(int left_border, int right_border, position_t *positions, position_t *result);
void child_work(position_t *positions, position_t *result, int *borders, int num_child);

int average_value_parallel(position_t *result, position_t *positions, int len);

#endif //MULTY_PROC_H
