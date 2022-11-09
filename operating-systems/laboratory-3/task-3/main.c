#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char * message = "Number: ";
int number = 0;

void exit_massage_writer(void) {
    sleep(2);
    printf("\n%s%d\n", message, number);
    number++;
}

int main(int argc, char ** argv) {
    char * options = "c:";
    int option_next;
    int message_count;

    setbuf(stdout, NULL);

    while ((option_next = getopt(argc, argv, options)) != -1) {
        switch (option_next) {
            case 'c':
                message_count = atoi(optarg);
                for (int index = 0; index < message_count; ++index) {
                    atexit(exit_massage_writer);
                }
                break;
        }
    }
    return 0;
}