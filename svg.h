#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "shapes.h"

/**
 * @brief Write the SVG element matching the shape type.
 * @param file Open output stream; NULL is ignored.
 * @param shape Shape to write; NULL is ignored.
 */
void svg_write_shape(FILE* file, const shape_t* shape);

#endif