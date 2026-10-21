#ifndef EXPORT_H
#define EXPORT_H

#include <stdio.h>
#include "shapes.h"
#include "list.h"

/**
 * @brief Export all shapes to an 800x600 SVG with black outlines.
 * @param list List to export.
 * @param filename Output path; existing content is overwritten.
 * @return 1 on success, 0 on invalid arguments or file errors.
 */
int export_svg(const list_t* list, const char* filename);

#endif