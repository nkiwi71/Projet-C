#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapes.h"

/**
 * @brief Allocate a shape and set only its position and color pointer.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return Allocated shape, or NULL on allocation failure.
 */
shape_t* allocate_shape(int x, int y, char* stroke, char* fill) {
    shape_t* shape = malloc(sizeof(*shape));
    if (shape == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return NULL;
    }

    shape->style.pos_x = x;
    shape->style.pos_y = y;
    shape->style.rotation = 0;
    shape->style.stroke_color = stroke;
    shape->style.fill_color = NULL;
    if (fill != NULL) {
        size_t fill_length = strlen(fill) + 1;
        shape->style.fill_color = malloc(fill_length);
        if (shape->style.fill_color == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            free(shape);
            return NULL;
        }
        memcpy(shape->style.fill_color, fill, fill_length);
    }

    return shape;
}

/**
 * @brief Allocate a shape and set its circle type and radius.
 * @param x Center X coordinate.
 * @param y Center Y coordinate.
 * @param radius Circle radius.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New circle, or NULL on allocation failure.
 */
shape_t* create_circle(int x, int y, int radius, char* stroke, char* fill) {
    shape_t* shape = allocate_shape(x, y, stroke, fill);
    if (shape == NULL) {
        return NULL;
    }

    shape->type = CIRCLE;
    shape->data.circle.radius = radius;
    return shape;
}

/**
 * @brief Allocate a shape and set its rectangle type and dimensions.
 * @param x Left edge position.
 * @param y Top edge position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New rectangle, or NULL on allocation failure.
 */
shape_t* create_rectangle(int x, int y, int width, int height, char* stroke, char* fill) {
    shape_t* shape = allocate_shape(x, y, stroke, fill);
    if (shape == NULL) {
        return NULL;
    }

    shape->type = RECTANGLE;
    shape->data.rectangle.width = width;
    shape->data.rectangle.height = height;
    return shape;
}

/**
 * @brief Allocate a shape and set its square type and side length.
 * @param x Left edge position.
 * @param y Top edge position.
 * @param size Side length.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New square, or NULL on allocation failure.
 */
shape_t* create_square(int x, int y, int size, char* stroke, char* fill) {
    shape_t* shape = allocate_shape(x, y, stroke, fill);
    if (shape == NULL) {
        return NULL;
    }

    shape->type = SQUARE;
    shape->data.square.size = size;
    return shape;
}

/**
 * @brief Allocate a shape and set its ellipse type and radii.
 * @param x Center X coordinate.
 * @param y Center Y coordinate.
 * @param rx Horizontal radius.
 * @param ry Vertical radius.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New ellipse, or NULL on allocation failure.
 */
shape_t* 
create_ellipse(int x, int y, int rx, int ry, char* stroke, char* fill) {
    shape_t* shape = allocate_shape(x, y, stroke, fill);
    if (shape == NULL) {
        return NULL;
    }

    shape->type = ELLIPSE;
    shape->data.ellipse.radius_x = rx;
    shape->data.ellipse.radius_y = ry;
    return shape;
}

/**
 * @brief Allocate a shape and store the line's two endpoints.
 * @param x1 Start X coordinate.
 * @param y1 Start Y coordinate.
 * @param x2 End X coordinate.
 * @param y2 End Y coordinate.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New line, or NULL on allocation failure.
 */
shape_t* create_line(int x1, int y1, int x2, int y2, char* stroke, char* fill) {
    shape_t* shape = allocate_shape(x1, y1, stroke, fill);
    if (shape == NULL) {
        return NULL;
    }

    shape->type = LINE;
    shape->data.line.pt2_x = x2;
    shape->data.line.pt2_y = y2;
    return shape;
}