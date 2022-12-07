#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

extern char **environ;

void manual_print() {
    printf("\t Напишіть свою версію спрощеного командного процесора. На самому початку роботи\n"
           "виводиться повідомлення про те, хто працює з командним процесором (виводиться повне ім'я\n"
           "користувача, який в даний момент працює з програмою). Потім на екран виводиться\n"
           "запрошення виду [user]$, (тут user – реєстраційне ім'я поточного користувача). Програма\n"
           "готова до прийому команд командної оболонки. Якщо команді не виконана, то на екран\n"
           "виводиться повідомлення, в іншому випадку - результат виконаної команди. Для завершення\n"
           "роботи програми призначена команда stop. При преждевременном завершении программы в\n"
           "результате какой-либо ошибки, а также при нормальном завершении программы, на экран\n"
           "выводится сообщение Wait 3 seconds..., програма чекає 3 сек., потім очищає екран і\n"
           "завершує свою роботу. Крім того, програма повинна працювати з двома опціями:\n"
           "\t -h та --help — опція без аргументу, призначена виведення довідкової інформації по\n"
           "роботі з програмою;\n"
           "\t -b та --buffer опція з аргументом - цілим числом, яке визначає розмір символьного\n"
           "буфера для зберігання введеної інформації команди; якщо користувач не вказав розмір\n"
           "при запуску програми, як значення за замовчуванням взяти 127.\n"
           "\t При написанні програми потрібно використовувати функцію system() і особливу\n"
           "увагу звернути на обробку помилок. Продумайте, які бібліотечні функції більше підійдуть\n"
           "для роботи. (Можна скористатись: gets(), краще fgets(), а найкраще getline() <stdio.h>\n"
           "для зчитування команди, sleep() <unistd.h> для затримки на вказану кількість секунд і\n"
           "команду оболонки clear для очишення экрану).\n");
}

int main(int argc, char ** argv) {
    int option_next;
    char * options_short = "hb:";
    const struct option options_long[] = {
            {"help", 0, 0, 'h'},
            {"buffer", 1, 0, 'b'},
            {NULL, 0, NULL, 0}
    };
    char * assign_variable_name = NULL;
    char * assign_variable_value = NULL;

    size_t buffer_size = 0;

    char * input_buffer;
    int input_buffer_size;
    while ((option_next = getopt_long(argc, argv, options_short, options_long, NULL)) != -1) {
        switch (option_next) {
            case 'h':
                manual_print();
                exit(1);
            case 'b':
                printf("\nBuffer size: %s\n", optarg);
                input_buffer_size = atoi(optarg);
                buffer_size = input_buffer_size;
                break;
            default:
                break;
        }
    }

    char * user_login = getlogin();
    printf("\nUser: %s\n", user_login);

    char * command = "command";

    size_t char_amount;
    char * buffer;

    if  (input_buffer_size == 0) {
        input_buffer_size = 127;
    }

    buffer = malloc(buffer_size * sizeof(char));
    command = buffer;
    while (strcmp(command, "stop\n") != 0) {
        printf("\n[%s]$ ", user_login);
        char_amount = getline(&buffer, &buffer_size, stdin);
        if  (strcmp(buffer, "stop\n") == 0) {
            continue;
        }
        system(buffer);
    }
    printf("\nWait 3 seconds...\n");
    sleep(3);
    system("clear");
    printf("\n");
}