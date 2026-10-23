#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "actions.h"
#include "shapes.h"
#include "list.h"
#include "export.h"
#include "ask_int.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

/**
 * @brief Read shape properties, fill and optional rotation, then append the shape.
 * @param my_list List receiving the shape; must not be NULL.
 */
void action_create_shape(list_t* my_list) {
    system("clear");
        printf("\n" COLOR_CYAN "+--------------------------------+\n"
            "|           CREATE SHAPE         |\n"
            "+--------------------------------+\n" COLOR_RESET);

    if (my_list == NULL) {
        printf("Invalid shape list.\n");
        return;
    }

    printf("\nChoose a shape:\n"
        COLOR_BLUE "  1. Circle\n"
        "  2. Rectangle\n"
        "  3. Square\n"
        "  4. Ellipse\n"
        "  5. Line\n" COLOR_RESET);
    int shape_choice = ask_integer("Your choice: ");

    if (shape_choice < 1 || shape_choice > 5) {
        printf("Erreur : Le choix %d n'existe pas ! (Choix valides : 1 à 5)\n", shape_choice);
        return;
    }

    char fill[8] = "none";
    if (shape_choice != 5) {
        printf("\n" COLOR_YELLOW "Fill the shape?\n"
            "  1. No\n"
            "  2. Yes\n" COLOR_RESET);
        int fill_choice = ask_integer("Your choice: ");
        if (fill_choice < 1 || fill_choice > 2) {
            printf("Invalid fill choice.\n");
            return;
        }

        if (fill_choice == 2) {
            if (!action_fill_color(fill)) {
                return;
            }
        }
    }

    printf("\n" COLOR_YELLOW "Rotate the shape?\n"
        "  1. No\n"
        "  2. Yes\n" COLOR_RESET);
    int rotation_choice = ask_integer("Your choice: ");
    if (rotation_choice < 1 || rotation_choice > 2) {
        printf("Invalid rotation choice.\n");
        return;
    }

    int rotation = 0;
    if (rotation_choice == 2) {
        rotation = ask_integer(COLOR_CYAN "Rotation (degrees): " COLOR_RESET);
    }

    int x = ask_integer(COLOR_CYAN "Starting X position: " COLOR_RESET);
    int y = ask_integer(COLOR_CYAN "Starting Y position: " COLOR_RESET);

    shape_t* new_shape = NULL;

    if (shape_choice == 1) {
        int r = ask_integer("Radius: ");
        new_shape = create_circle(x, y, r, "black", fill);
    }
    else if (shape_choice == 2) {
        int w = ask_integer("Width: ");
        int h = ask_integer("Height: ");
        new_shape = create_rectangle(x, y, w, h, "black", fill);
    }
    else if (shape_choice == 3) {
        int size = ask_integer("Square size: ");
        new_shape = create_square(x, y, size, "black", fill);
    }
    else if (shape_choice == 4) {
        int rx = ask_integer("X radius: ");
        int ry = ask_integer("Y radius: ");
        new_shape = create_ellipse(x, y, rx, ry, "black", fill);
    }
    else if (shape_choice == 5) {
        int x2 = ask_integer("Ending X position: ");
        int y2 = ask_integer("Ending Y position: ");
        new_shape = create_line(x, y, x2, y2, "black", fill);
    }

    if (new_shape != NULL) {
        new_shape->style.rotation = rotation;
        add_shape(my_list, new_shape);
        printf("\n" COLOR_GREEN "Shape added successfully! (Total in list: %u)\n" COLOR_RESET,
               my_list->length);
    }
}

/**
 * @brief Ask for a shape number and delete it from memory.
 * @param my_list List to update; NULL or empty lists are ignored.
 */
void action_delete_shape(list_t* my_list) {
    system("clear");
        printf("\n" COLOR_RED "+--------------------------------+\n"
            "|           DELETE SHAPE         |\n"
            "+--------------------------------+\n" COLOR_RESET);

    if (my_list == NULL || my_list->start == NULL) {
        printf("\nThe list is empty; there are no shapes to delete.\n");
        return;
    }

    action_visualize(my_list);

    int index = ask_integer("\nEnter the number of the shape to delete: ");

    if (delete_shape(my_list, index)) {
        printf("\n" COLOR_GREEN "Shape no. %d deleted successfully!\n" COLOR_RESET, index);
    } 
    else {
        printf("\n" COLOR_RED "Error: Invalid shape number.\n" COLOR_RESET);
    }
}

/**
 * @brief Print each shape's number, position and dimensions.
 * @param my_list List to display; may be NULL or empty.
 */
void action_visualize(list_t* my_list) {
    system("clear");
        printf("\n" COLOR_CYAN "+--------------------------------+\n"
            "|       SHAPES IN MEMORY         |\n"
            "+--------------------------------+\n\n" COLOR_RESET);

    if (my_list == NULL || my_list->start == NULL) {
        printf("The list is completely empty.\n");
        return;
    }

    node_t* current = my_list->start;
    int count = 1;

    while (current != NULL) {
        shape_t* s = current->shape;

        if (s->type == CIRCLE) {
            printf("Shape %d: CIRCLE [X:%d, Y:%d, Radius:%d, Rotation:%d°]\n",
                   count, s->style.pos_x, s->style.pos_y,
                   s->data.circle.radius, s->style.rotation);
        }
        else if (s->type == RECTANGLE) {
            printf("Shape %d: RECTANGLE [X:%d, Y:%d, Width:%d, Height:%d, Rotation:%d°]\n",
                   count, s->style.pos_x, s->style.pos_y,
                   s->data.rectangle.width, s->data.rectangle.height, s->style.rotation);
        }
        else if (s->type == SQUARE) {
            printf("Shape %d: SQUARE [X:%d, Y:%d, Size:%d, Rotation:%d°]\n",
                   count, s->style.pos_x, s->style.pos_y,
                   s->data.square.size, s->style.rotation);
        }
        else if (s->type == ELLIPSE) {
            printf("Shape %d: ELLIPSE [X:%d, Y:%d, Rx:%d, Ry:%d, Rotation:%d°]\n",
                   count, s->style.pos_x, s->style.pos_y,
                   s->data.ellipse.radius_x, s->data.ellipse.radius_y, s->style.rotation);
        }
        else if (s->type == LINE) {
            printf("Shape %d: LINE [From X1:%d,Y1:%d to X2:%d,Y2:%d, Rotation:%d°]\n",
                   count, s->style.pos_x, s->style.pos_y,
                   s->data.line.pt2_x, s->data.line.pt2_y, s->style.rotation);
        }

        current = current->next;
        count++;
    }
}

/**
 * @brief Export the list to dessin.svg and print the result.
 * @param my_list List to export.
 */
void action_export_svg(list_t* my_list) {
    system("clear");
        printf("\n" COLOR_GREEN "+--------------------------------+\n"
            "|            EXPORT SVG          |\n"
            "+--------------------------------+\n\n" COLOR_RESET);

    if (export_svg(my_list, "dessin.svg")) {
         printf(COLOR_GREEN "Export réussi : dessin.svg\n\n" COLOR_RESET);

        printf(COLOR_YELLOW "Open the file?\n"
            "  1. No\n"
            "  2. Open SVG\n" COLOR_RESET);
        int open_choice = ask_integer("Your choice: ");
        if (open_choice == 2) {
            system("open dessin.svg");
        }

    } else {
        printf(COLOR_RED "Échec de l'export SVG.\n" COLOR_RESET);
    }
}


bool action_fill_color(char* fill) {
    if (fill == NULL) {
        return false;
    }

    char color_input[32];
    for (;;) {
        printf(COLOR_CYAN "Enter fill color (#RRGGBB) or 'help': " COLOR_RESET);
        if (scanf("%31s", color_input) != 1) {
            clear_input();
            printf("Invalid input.\n");
            return false;
        }
        clear_input();

        if (strcmp(color_input, "help") == 0) {
            system("open https://htmlcolorcodes.com/color-picker/");
            continue;
        }

        int valid_color = (strlen(color_input) == 7 && color_input[0] == '#');
        for (int i = 1; valid_color && i < 7; i++) {
            if (!isxdigit((unsigned char) color_input[i])) {
                valid_color = 0;
            }
        }

        if (!valid_color) {
            printf("Enter a hexadecimal color like #54ABF7.\n");
            continue;
        }

        strcpy(fill, color_input);
        return true;
    }
}
