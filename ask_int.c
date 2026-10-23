#include <stdio.h>
#include "ask_int.h"

void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ask_integer(const char *message)
{
    int input_number;
    int result_input;

    do
    {
        printf("%s\n", message);
        result_input = scanf("%d", &input_number);
        clear_input();

        if (result_input != 1)
        {
            printf("Invalid input\n");
        }
    } while (result_input != 1);
    return input_number;
}