#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "list.h"
#include "shapes.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

/**
 * @brief Prompt for a fill color and replace the shape's current color.
 * @param shape Shape whose fill color is updated.
 * @return true if the color changed, false on invalid input or allocation failure.
 */
static bool modify_shape_fill(shape_t* shape) {
    if (shape == NULL) {
        return false;
    }

    char fill[8];
    if (!action_fill_color(fill)) {
        return false;
    }

    char* new_fill = malloc(strlen(fill) + 1);
    if (new_fill == NULL) {
        printf(COLOR_RED "Memory allocation error.\n" COLOR_RESET);
        return false;
    }
    strcpy(new_fill, fill);

    free(shape->style.fill_color);
    shape->style.fill_color = new_fill;
    return true;
}

/**
 * @brief Read and replace the position stored in the shape style.
 * @param shape Non-NULL shape; a line's second endpoint is unchanged.
 * @return true on update, false on invalid input.
 */
static bool modify_shape_position(shape_t* shape) {
    int new_x = 0, new_y = 0;
    printf(COLOR_CYAN "New X position: " COLOR_RESET);
    if (scanf("%d", &new_x) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    printf(COLOR_CYAN "New Y position: " COLOR_RESET);
    if (scanf("%d", &new_y) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }

    shape->style.pos_x = new_x;
    shape->style.pos_y = new_y;
    return true;
}



/**
 * @brief Read and replace the circle radius.
 * @param shape Non-NULL circle to update.
 * @return true on update, false on invalid input.
 */
static bool action_modify_circle(shape_t* shape) {
    int r = 0;
    printf(COLOR_CYAN "New radius: " COLOR_RESET);
    if (scanf("%d", &r) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    shape->data.circle.radius = r;
    return true;
}

/**
 * @brief Read and replace the rectangle width and height.
 * @param shape Non-NULL rectangle to update.
 * @return true on update, false on invalid input.
 */
static bool action_modify_rectangle(shape_t* shape) {
    int w = 0, h = 0;
    printf(COLOR_CYAN "New width: " COLOR_RESET);
    if (scanf("%d", &w) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    printf(COLOR_CYAN "New height: " COLOR_RESET);
    if (scanf("%d", &h) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    shape->data.rectangle.width = w;
    shape->data.rectangle.height = h;
    return true;
}

/**
 * @brief Read and replace the square side length.
 * @param shape Non-NULL square to update.
 * @return true on update, false on invalid input.
 */
static bool action_modify_square(shape_t* shape) {
    int size = 0;
    printf(COLOR_CYAN "New size: " COLOR_RESET);
    if (scanf("%d", &size) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    shape->data.square.size = size;
    return true;
}

/**
 * @brief Read and replace both ellipse radii.
 * @param shape Non-NULL ellipse to update.
 * @return true on update, false on invalid input.
 */
static bool action_modify_ellipse(shape_t* shape) {
    int rx = 0, ry = 0;
    printf(COLOR_CYAN "New X radius: " COLOR_RESET);
    if (scanf("%d", &rx) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    printf(COLOR_CYAN "New Y radius: " COLOR_RESET);
    if (scanf("%d", &ry) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    shape->data.ellipse.radius_x = rx;
    shape->data.ellipse.radius_y = ry;
    return true;
}

/**
 * @brief Read and replace the line's second endpoint.
 * @param shape Non-NULL line to update.
 * @return true on update, false on invalid input.
 */
static bool action_modify_line(shape_t* shape) {
    int x2 = 0, y2 = 0;
    printf(COLOR_CYAN "New ending X position: " COLOR_RESET);
    if (scanf("%d", &x2) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    printf(COLOR_CYAN "New ending Y position: " COLOR_RESET);
    if (scanf("%d", &y2) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return false;
    }
    shape->data.line.pt2_x = x2;
    shape->data.line.pt2_y = y2;
    return true;
}


/**
 * @brief Call the dimension editor matching the shape type.
 * @param shape Shape to update.
 * @return true on update, false on invalid input, NULL or unknown type.
 */
bool modify_shape_geometry(shape_t* shape) {
    if (shape == NULL) return false;

    switch (shape->type) {
        case CIRCLE:
            return action_modify_circle(shape);
        case RECTANGLE:
            return action_modify_rectangle(shape);
        case SQUARE:
            return action_modify_square(shape);
        case ELLIPSE:
            return action_modify_ellipse(shape);
        case LINE:
            return action_modify_line(shape);
        default:
            printf(COLOR_RED "Unknown shape type.\n" COLOR_RESET);
            return false;
    }
}

/**
 * @brief Select a shape and edit its position or dimensions in memory.
 * @param my_list List containing the shape; may be NULL or empty.
 */
void action_modify_shape(list_t* my_list) {
        printf("\n" COLOR_YELLOW "+--------------------------------+\n"
            "|           MODIFY SHAPE         |\n"
            "+--------------------------------+\n" COLOR_RESET);
    if (my_list == NULL || my_list->start == NULL) {
        printf("The list is empty; there are no shapes to modify.\n");
        return;
    }

    action_visualize(my_list);

    int index = 0;
    printf(COLOR_CYAN "Enter the number of the shape to modify: " COLOR_RESET);
    if (scanf("%d", &index) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (index < 1 || (unsigned int) index > my_list->length) {
        printf(COLOR_RED "Invalid shape number.\n" COLOR_RESET);
        return;
    }

    node_t* current = my_list->start;
    for (int current_index = 1; current_index < index; current_index++) {
        current = current->next;
    }

    int modification_choice = 0;
        printf("\n" COLOR_BLUE "Choose what to modify:\n"
            "  1. Position (X and Y)\n"
            "  2. Shape dimensions\n" 
            "  3. Fill color\n" COLOR_RESET
            "Your choice: ");
    if (scanf("%d", &modification_choice) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    bool modified = false;
    if (modification_choice == 1) {
        modified = modify_shape_position(current->shape);
    } else if (modification_choice == 2) {
        modified = modify_shape_geometry(current->shape);
    } else if (modification_choice == 3) {
        modified = modify_shape_fill(current->shape);
    } else {
        printf(COLOR_RED "Invalid modification choice.\n" COLOR_RESET);
        return;
    }

    if (modified) {
        printf(COLOR_GREEN "Shape no. %d modified successfully.\n" COLOR_RESET, index);
    } else {
        printf(COLOR_RED "Failed to modify shape no. %d.\n" COLOR_RESET, index);
    }
}
