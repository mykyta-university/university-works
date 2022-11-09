#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    char * options = "c:";
    int option_next;
    int execute_result;

    while ((option_next = getopt(argc, argv, options)) != -1) {
        switch (option_next) {
            case 'c':
                printf("\nExecute: %s\n", optarg);
                execute_result = system(optarg);
                if  (execute_result == 0) {
                    printf("\nResult: Success\n");
                } else {
                    printf("\nResult: Error\n");
                }
                break;
        }
    }
    return 0;
}