#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "list.h"
#include "shapes.h"
#include "ask_int.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

/**
 * @brief Prompt for a fill color and replace the shape's current color.
 * @param shape Shape whose fill color is updated.
 * @return true if the color changed, false if color input fails or allocation fails.
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
 * @brief Read and replace the shape rotation in degrees.
 * @param shape Non-NULL shape to rotate.
 * @return true after updating the rotation.
 */
static bool modify_shape_rotation(shape_t* shape) {
    int new_rotation = ask_integer(COLOR_CYAN "New rotation (degrees): " COLOR_RESET);
    shape->style.rotation = new_rotation;
    return true;
}

/**
 * @brief Read and replace the position stored in the shape style.
 * @param shape Non-NULL shape; a line's second endpoint is unchanged.
 * @return true after updating the position.
 */
static bool modify_shape_position(shape_t* shape) {
    int new_x = ask_integer(COLOR_CYAN "New X position: " COLOR_RESET);
    int new_y = ask_integer(COLOR_CYAN "New Y position: " COLOR_RESET);

    shape->style.pos_x = new_x;
    shape->style.pos_y = new_y;
    return true;
}



/**
 * @brief Read and replace the circle radius.
 * @param shape Non-NULL circle to update.
 * @return true after updating the radius.
 */
static bool action_modify_circle(shape_t* shape) {
    int r = ask_integer(COLOR_CYAN "New radius: " COLOR_RESET);
    shape->data.circle.radius = r;
    return true;
}

/**
 * @brief Read and replace the rectangle width and height.
 * @param shape Non-NULL rectangle to update.
 * @return true after updating the dimensions.
 */
static bool action_modify_rectangle(shape_t* shape) {
    int w = ask_integer(COLOR_CYAN "New width: " COLOR_RESET);
    int h = ask_integer(COLOR_CYAN "New height: " COLOR_RESET);
    shape->data.rectangle.width = w;
    shape->data.rectangle.height = h;
    return true;
}

/**
 * @brief Read and replace the square side length.
 * @param shape Non-NULL square to update.
 * @return true after updating the size.
 */
static bool action_modify_square(shape_t* shape) {
    int size = ask_integer(COLOR_CYAN "New size: " COLOR_RESET);
    shape->data.square.size = size;
    return true;
}

/**
 * @brief Read and replace both ellipse radii.
 * @param shape Non-NULL ellipse to update.
 * @return true after updating the radii.
 */
static bool action_modify_ellipse(shape_t* shape) {
    int rx = ask_integer(COLOR_CYAN "New X radius: " COLOR_RESET);
    int ry = ask_integer(COLOR_CYAN "New Y radius: " COLOR_RESET);
    shape->data.ellipse.radius_x = rx;
    shape->data.ellipse.radius_y = ry;
    return true;
}

/**
 * @brief Read and replace the line's second endpoint.
 * @param shape Non-NULL line to update.
 * @return true after updating the endpoint.
 */
static bool action_modify_line(shape_t* shape) {
    int x2 = ask_integer(COLOR_CYAN "New ending X position: " COLOR_RESET);
    int y2 = ask_integer(COLOR_CYAN "New ending Y position: " COLOR_RESET);
    shape->data.line.pt2_x = x2;
    shape->data.line.pt2_y = y2;
    return true;
}


/**
 * @brief Call the dimension editor matching the shape type.
 * @param shape Shape to update.
 * @return true on update, false for a NULL shape or unknown type.
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

    int index = ask_integer(COLOR_CYAN "Enter the number of the shape to modify: " COLOR_RESET);

    if (index < 1 || (unsigned int) index > my_list->length) {
        printf(COLOR_RED "Invalid shape number.\n" COLOR_RESET);
        return;
    }

    node_t* current = my_list->start;
    for (int current_index = 1; current_index < index; current_index++) {
        current = current->next;
    }

    printf("\n" COLOR_BLUE "Choose what to modify:\n"
        "  1. Position (X and Y)\n"
        "  2. Shape dimensions\n"
        "  3. Fill color\n"
        "  4. Rotation\n" COLOR_RESET);
    int modification_choice = ask_integer("Your choice: ");

    bool modified = false;
    if (modification_choice == 1) {
        modified = modify_shape_position(current->shape);
    } else if (modification_choice == 2) {
        modified = modify_shape_geometry(current->shape);
    } else if (modification_choice == 3) {
        modified = modify_shape_fill(current->shape);
    } else if (modification_choice == 4) {
        modified = modify_shape_rotation(current->shape);
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
