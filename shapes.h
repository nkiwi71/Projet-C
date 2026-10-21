#ifndef SHAPES_H
#define SHAPES_H

#include <stdbool.h> 

/** @file shapes.h
 * @brief Shape types, properties and constructors.
 */

/** @brief Supported geometric shape kinds. */
typedef enum shape_type_e {
    CIRCLE,     /**< Circle, described by a radius. */
    RECTANGLE,  /**< Rectangle, described by width and height. */
    SQUARE,     /**< Square, described by its side length. */
    ELLIPSE,    /**< Ellipse, described by horizontal and vertical radii. */
    LINE        /**< Line segment, described by its second endpoint. */
} shape_type_t;

/** @brief Common position and visual attributes of a shape. */
typedef struct style_s {
    int pos_x;             /**< X coordinate of the shape origin. */
    int pos_y;             /**< Y coordinate of the shape origin. */
    char* stroke_color;    /**< Outline color string. */
    int rotation;          /**< Rotation value in degrees. */
    char* fill_color;       /**< Fill color string. */
    bool flip_x;           /**< Whether the shape is flipped horizontally. */
    bool flip_y;           /**< Whether the shape is flipped vertically. */
} style_t;

/** @brief Circle-specific data. */
typedef struct circle_data_s {
    int radius; /**< Circle radius. */
} circle_data_t;

/** @brief Rectangle-specific data. */
typedef struct rect_data_s {
    int width;  /**< Rectangle width. */
    int height; /**< Rectangle height. */
} rect_data_t;

/** @brief Square-specific data. */
typedef struct square_data_s {
    int size; /**< Length of each side. */
} square_data_t;

/** @brief Ellipse-specific data. */
typedef struct ellipse_data_s {
    int radius_x; /**< Horizontal radius. */
    int radius_y; /**< Vertical radius. */
} ellipse_data_t;

/** @brief Line-specific data; the first endpoint is stored in style_t. */
typedef struct line_data_s {
    int pt2_x; /**< X coordinate of the second endpoint. */
    int pt2_y; /**< Y coordinate of the second endpoint. */
} line_data_t;

/** @brief Shape data selected by shape_t.type. */
typedef union shape_data_u {
    circle_data_t circle;      /**< Circle data. */
    rect_data_t rectangle;     /**< Rectangle data. */
    square_data_t square;      /**< Square data. */
    ellipse_data_t ellipse;    /**< Ellipse data. */
    line_data_t line;          /**< Line data. */
} shape_data_t;

/** @brief Shape type, style and dimensions. */
typedef struct shape_s {
    shape_type_t type;    /**< Kind of shape; selects the valid data member. */
    style_t style;        /**< Shared position and visual attributes. */
    shape_data_t data;    /**< Data specific to the selected shape kind. */
} shape_t;

/**
 * @brief Allocate a circle with the given radius.
 * @param x Center X coordinate.
 * @param y Center Y coordinate.
 * @param radius Circle radius.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New circle, or NULL on allocation failure.
 */
shape_t* create_circle(int x, int y, int radius, char* stroke, char* fill);

/**
 * @brief Allocate a rectangle with the given dimensions.
 * @param x Left edge position.
 * @param y Top edge position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New rectangle, or NULL on allocation failure.
 */
shape_t* create_rectangle(int x, int y, int width, int height, char* stroke, char* fill);

/**
 * @brief Allocate a square with the given side length.
 * @param x Left edge position.
 * @param y Top edge position.
 * @param size Side length.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New square, or NULL on allocation failure.
 */
shape_t* create_square(int x, int y, int size, char* stroke, char* fill);

/**
 * @brief Allocate an ellipse with the given radii.
 * @param x Center X coordinate.
 * @param y Center Y coordinate.
 * @param rx Horizontal radius.
 * @param ry Vertical radius.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New ellipse, or NULL on allocation failure.
 */
shape_t* create_ellipse(int x, int y, int rx, int ry, char* stroke, char* fill);

/**
 * @brief Allocate a line between two endpoints.
 * @param x1 Start X coordinate.
 * @param y1 Start Y coordinate.
 * @param x2 End X coordinate.
 * @param y2 End Y coordinate.
 * @param stroke Outline color pointer stored as provided.
 * @param fill Fill color copied into the shape.
 * @return New line, or NULL on allocation failure.
 */
shape_t* create_line(int x1, int y1, int x2, int y2, char* stroke, char* fill);



#endif
