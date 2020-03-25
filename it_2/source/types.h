#ifndef TYPES_H
#define TYPES_H

#define OK 0

#define ERROR_FILE -1
#define ERROR_DATA -2
#define ERROR_ALLOC -3
#define ERROR_LIB -4

typedef struct position position_t;
struct position
{
    double x;
    double y;
    double z;
};

#endif //TYPES_H
