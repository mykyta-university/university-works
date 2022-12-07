#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "dot.h"

int size;

void print_space(Space * space) {
    char * string;
    printf("\n_Dots_\n");
    for (int index = 0; index < size; ++index) {
        string = dot_to_string(space->dot_arr[index]);
        printf("i: %d, %s\n", index, string);
        free(string);
    }
    printf("_Dots_\n");
}

int main() {
    srand(time(NULL));

    printf("Enter size: ");
    scanf("%d", &size);

    Space * space = space_create(size);
    Dot * current_dot;
    Dot * closest_dot;

    for (int index = 0; index < size - 1; ++index) {
        print_space(space);
        current_dot = space_get_min_dot(space);
        closest_dot = space_get_closest_dot(space, current_dot);
        closest_dot->value += current_dot->value;
        current_dot->value = 0.0;
    }
    print_space(space);

    return 0;
}

