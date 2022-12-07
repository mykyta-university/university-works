#ifndef __DOT_H
#define __DOT_H

typedef struct dot {
    double value;
    double x;
    double y;
    double z;
} Dot;

typedef struct space {
    int size;
    Dot ** dot_arr;
} Space;

// Private
Dot * __dot_create(double value, double x, double y, double z);

Dot * __dot_create_random(int max_value);

// Public
double dot_get_distance(Dot * start, Dot * finish);

char * dot_to_string(Dot * dot);

Space * space_create(int dot_amount);

Dot * space_get_closest_dot(Space * space,  Dot * start);

Dot * space_get_min_dot(Space * space);

#endif