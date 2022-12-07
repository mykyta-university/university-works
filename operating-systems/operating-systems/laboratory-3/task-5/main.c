#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char ** argv) {
    int c;
    int process_amount = 0;
    char command[100];

    const struct option long_opt[] = {
            {"file", required_argument, 0, 'f'},
            {"number", required_argument, 0, 'n'},
            {NULL,0,NULL,0}
    };

    while ((c = getopt_long(argc, argv, "f:n:", long_opt, NULL)) != -1){
        switch(c){
            case 'f':
                setenv("FILE_NAME", optarg, 1);
                break;
            case 'n':
                process_amount = atoi(optarg);
                for (int index = 1; index < process_amount + 1; ++index) {
                    sprintf(command, "./extra %d", index);
                    system(command);
                }
                break;
            default:
                printf("\n___\n");
                return(-1);
        }
    }
}