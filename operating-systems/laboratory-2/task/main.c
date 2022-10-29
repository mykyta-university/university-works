#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

extern char **environ;

void manual_print() {
    printf("\tякщо програма запущена без опцій, то в стандартний потік виводу выводиться\n"
           "інформація о поточном оточенні;\n"
           "\t якщо вказана коротка опція -h (або довга --help), то в стандартний потік выводу буде\n"
           "выведено інформацию по роботі із програмою;\n"
           "\t якщо вказана коротка опція -i <змінна> (або довга --info <змінна>), то в\n"
           "стандартний потік выводу буде выведено значення вказаної змінної або повідомлення\n"
           "про те, що вказаної змінної в оточенні немає;\n"
           "\t якщо вказана коротка опція -s <змінна=значення> (або довга --set\n"
           "<змінна=значення>), то вказана змінна оточення отримає нове значення та в\n"
           "стандартний потік виводу буде виведено встановлене значення вказаної змінної;\n"
           "\t якщо вказані короткі опції -a <змінна> та -v <значення> (або довгі --assign\n"
           "<змінна> та --value <значення>), то вказана змінна оточення отримає нове\n"
           "значення та в стандартний потік виводу буде виведено встановлене значення вказаної\n"
           "змінної; якщо значення не вказано, то буде присвоєно пустий рядок; якщо же не\n"
           "вказано змінну, то присвоєння не відбудається, а в стандартний потік помилок\n"
           "виводиться відповідне повідомлення;\n"
           "\t якщо вказана коротка опція -d <змінна> (або довга --del <змінна>), то вказана\n"
           "змінна видаляєтья з оточення;\n"
           "\t якщо вказана коротка опція -с (або довга --сlear), то програма повністю очищує\n"
           "оточення.\n");
}

void environment_print() {
    printf("l");
    for (int index = 0;; ++index) {
        if  (environ[index] == NULL) {
            break;
        }
        printf("\n%s\n", environ[index]);
    }
}

void environment_variable_print(char * name) {
    char * string = getenv(name);
    if  (string == NULL) {
        printf("\nVariable %s does not exist\n", name);
        return;
    }
    printf("\n%s = %s\n", name, string);
}

int main(int argc, char ** argv) {
    int option_next;
    char * options_short = "hi:s:a:v:d:c";
    const struct option options_long[] = {
        {"help", 0, 0, 'h'},
        {"info", 1, 0, 'i'},
        {"set", 1, 0, 's'},
        {"assign", 2, 0, 'a'},
        {"value", 2, 0, 'v'},
        {"delete", 1, 0, 'd'},
        {"clear", 0, 0, 'c'},
        {NULL, 0, NULL, 0}
    };
    char * assign_variable_name = NULL;
    char * assign_variable_value = NULL;

    if  (argc == 1) {
        environment_print();
        return 0;
    }

    while ((option_next = getopt_long(argc, argv, options_short, options_long, NULL)) != -1) {
        switch (option_next) {
            case 'h':
                manual_print();
                break;
            case 'i':
                environment_variable_print(optarg);
                break;
            case 's':
                putenv(optarg);
                break;
            case 'a':
                printf("\nd--\n");
                assign_variable_name = malloc(strlen(optarg) * sizeof(char));
                strcpy(assign_variable_name, optarg);
                break;
            case 'v':
                if  (assign_variable_name == NULL) {
                    fprintf(stderr, "Error: -a / --assign flag requires argument.");
                    break;
                } else if (optarg == NULL) {
                    assign_variable_value = "";
                } else {
                    assign_variable_value = malloc(strlen(optarg) * sizeof(char));
                    strcpy(assign_variable_value, optarg);
                }
                setenv(assign_variable_name, assign_variable_value, 1);
                environment_variable_print(assign_variable_name);
                //free(assign_variable_name);
                //free(assign_variable_value);
                break;
            case 'd':
                unsetenv(optarg);
                break;
            case 'c':
                clearenv();
                break;
            default:
                break;
        }
    }
}
















































//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>

//int main(int argc, char ** argv) {
//    char * opts = "a:b:c:";
//    int n_opt;
//
//    while ((n_opt = getopt(argc, argv, opts)) != -1) {
//        switch (n_opt) {
//            case 'a':
//                printf("\nAAAAA: %s\n", optarg);
//                break;
//            case 'b':
//                printf("\nBBBBB: %s\n", optarg);
//                break;
//            case 'c':
//                printf("\nC: %s\n", optarg);
//                break;
//        }
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <getopt.h>
//
//int main(int argc, char ** argv) {
//    int c;
//
//    const struct option long_opt[] = {
//            {"aflag", 1, 0, 'a'},
//            {NULL,0,NULL,0}
//    };
//
//    while ((c = getopt_long(argc, argv, "a:", long_opt, NULL)) != -1){
//        switch( c ){
//            case 'a':
//                printf("\nAAAAA: %s\n", optarg);
//                break;
//            default:
//                printf("\n___\n");
//                return(-1);
//        }
//    }
//}