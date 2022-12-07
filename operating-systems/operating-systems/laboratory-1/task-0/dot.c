#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "dot.h"

// Private
Dot * __dot_create(double value, double x, double y, double z) {
    Dot* dot = malloc(sizeof(Dot));
    dot->value = value;
    dot->y = y;
    dot->x = x;
    dot->z = z;
    return dot;
}

Dot * __dot_create_random(int max_value) {
    double value = (double) (rand() % max_value) + 1.0;
    double x = (double) (rand() % max_value) + 1.0;
    double y = (double) (rand() % max_value) + 1.0;
    double z = (double) (rand() % max_value) + 1.0;
    return __dot_create(value, x, y, z);
}

// Public
double dot_get_distance(Dot * start, Dot * finish) {
    double result;
    result = sqrt(pow(finish->x - start->x, 2) + pow(finish->y - start->y, 2) + pow(finish->z - start->z, 2));
    return result;
}

char * dot_to_string(Dot * dot) {
    char * string = malloc(55 * sizeof(char));
    sprintf(string, "value:%lf, x: %lf, y: %lf, z:%lf", dot->value, dot->x, dot->y, dot->z);
    return string;
}

Space * space_create(int dot_amount) {
    Space * space = malloc(sizeof(Space));
    Dot ** dot_arr = malloc(dot_amount * sizeof(Dot));
    for (int index = 0; index < dot_amount; ++index) {
        dot_arr[index] = __dot_create_random(100);
    }
    space->dot_arr = dot_arr;
    space->size = dot_amount;
    return space;
}

Dot * space_get_closest_dot(Space * space,  Dot * start) {
    double distance;
    double min_distance = DBL_MAX;
    Dot * result;

    for (int index = 0; index < space->size; ++index) {
        if  (start == space->dot_arr[index]) {
            continue;
        }
        if  (0 == space->dot_arr[index]->value) {
            continue;
        }
        distance = dot_get_distance(start, space->dot_arr[index]);
        if  (distance < min_distance) {
            min_distance = distance;
            result = space->dot_arr[index];
        }
    }

    return result;
}

Dot * space_get_min_dot(Space * space) {
    Dot * result;

    for (int index = 0; index < space->size; ++index) {
        if  (space->dot_arr[index]->value != 0) {
            result = space->dot_arr[index];
            break;
        }
    }

    for (int index = 0; index < space->size; ++index) {
        if  (space->dot_arr[index]->value < result->value && space->dot_arr[index]->value != 0) {
            result = space->dot_arr[index];
        }
    }
    return result;
}