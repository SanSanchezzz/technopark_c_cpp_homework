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
#include <errno.h>

#include "types.h"


int set_borders(int **borders, int borders_qty, int len);
void border_sum(const int left_border, const int right_border, const position_t *positions, position_t *result);
void child_work(const position_t *positions, const int *borders, const int num_child, position_t *tmp_result);

int average_value_parallel(position_t *result, const position_t *positions, const int len);

#endif //MULTY_PROC_H
