#ifndef TYPES_H
#define TYPES_H

#define OK 0

#define ERROR_FILE -1
#define ERROR_DATA -2
#define ERROR_ALLOC -3

typedef struct position position_t;
struct position
{
    double x;
    double y;
    double z;
};

int read_data(position_t **pos_array, int *len, char *file_name);

#endif //TYPES_H
