#include <stdio.h>
#include <stdlib.h>
#define COLOR_RESET "\033[0m"
#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE   "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#include "actions.h"
#include "list.h"

/**
 * @brief Create the shape list and dispatch menu choices until quit.
 * @return EXIT_SUCCESS on exit, EXIT_FAILURE if list allocation fails.
 */
int main(void) {
    int choice = 0;
    list_t* my_list = create_list();
    if (my_list == NULL) return EXIT_FAILURE;

    system("clear");

    do {
        printf("\n" COLOR_YELLOW "+--------------------------------+\n"
            "|           SVG MENU             |\n"
            "+--------------------------------+\n" COLOR_RESET);
        printf("|" COLOR_BLUE " 1. Create a shape  " COLOR_RESET "|\n");
        printf("|" COLOR_RED " 2. Modify a shape  " COLOR_RESET "|\n");
        printf("|" COLOR_YELLOW " 3. Delete a shape  " COLOR_RESET "|\n");
        printf("|" COLOR_GREEN " 4. Export          " COLOR_RESET "|\n");
        printf("|" COLOR_MAGENTA " 5. Visualize       " COLOR_RESET "|\n");
        printf("|" COLOR_CYAN " 0. Quit            " COLOR_RESET "|\n");
        printf("Your choice: ");
        
        scanf("%d", &choice); 

        switch (choice) {

            case 1: system("clear"); action_create_shape(my_list); break;
            case 2: system("clear"); action_modify_shape(my_list); break;
            case 3: system("clear"); action_delete_shape(my_list); break;
            case 4: system("clear"); action_export_svg(my_list); break;
            case 5: system("clear"); action_visualize(my_list); break;
            case 0: system("make clean"); system("clear"); printf("Thank you!\n"); break;
            default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 0);
        
    return EXIT_SUCCESS;
}