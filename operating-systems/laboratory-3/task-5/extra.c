#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

double random_double(double min, double max) {
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(int argc, char ** argv) {
    char * file_name_prefix = getenv("FILE_NAME");
    char file_name[100];
    int program_number = atoi(argv[argc - 1]);
    FILE * file;

    if  (NULL == file_name_prefix) {
        file_name_prefix = "DEFAULT_FILE_NAME";
    }

    sprintf(file_name, "%s_NUMBER_%d", file_name_prefix, program_number);

    srand(time(NULL));

    file = fopen(file_name, "wb");

    for (int index = 0; index < program_number; ++index) {
        fprintf(file, ": %lf :", random_double(0, 1));
    }

    fclose(file);

    return 0;
}