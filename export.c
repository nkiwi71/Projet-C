#include <stdio.h>
#include "export.h"
#include "svg.h"

/**
 * @brief Write the SVG element matching the shape type.
 * @param file Open output stream; NULL is ignored.
 * @param shape Shape to serialize; NULL is ignored.
 */
void svg_write_shape(FILE* file, const shape_t* shape) {
    if (file == NULL || shape == NULL) {
        return;
    }

    int x = shape->style.pos_x;
    int y = shape->style.pos_y;
    double center_x = x;
    double center_y = y;

    switch (shape->type) {
        case RECTANGLE:
            center_x += shape->data.rectangle.width / 2.0;
            center_y += shape->data.rectangle.height / 2.0;
            break;
        case SQUARE:
            center_x += shape->data.square.size / 2.0;
            center_y += shape->data.square.size / 2.0;
            break;
        case LINE:
            center_x = (x + (double) shape->data.line.pt2_x) / 2.0;
            center_y = (y + (double) shape->data.line.pt2_y) / 2.0;
            break;
        case CIRCLE:
        case ELLIPSE:
            break;
    }

    const char* fill = shape->style.fill_color;
    if (fill == NULL) {
        fill = "none";
    }

    if (shape->style.rotation != 0) {
        fprintf(file, "    <g transform=\"rotate(%d %.1f %.1f)\">\n",
                shape->style.rotation, center_x, center_y);
    }
    
    switch (shape->type) {
        case CIRCLE:
            fprintf(file,
                    "      <circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\" />\n", x, y,
                    shape->data.circle.radius, fill);
            break;

        case RECTANGLE:
            fprintf(file,
                    "      <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n", x, y,
                    shape->data.rectangle.width,
                    shape->data.rectangle.height, fill);
            break;

        case SQUARE:
            fprintf(file,
                    "      <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n", x, y,
                    shape->data.square.size,
                    shape->data.square.size, fill);
            break;

        case ELLIPSE:
            fprintf(file,
                    "      <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" fill=\"%s\" />\n", x, y,
                    shape->data.ellipse.radius_x,
                    shape->data.ellipse.radius_y, fill);
            break;

        case LINE:
            fprintf(file,
                    "      <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" fill=\"%s\" />\n", x, y,
                    shape->data.line.pt2_x,
                    shape->data.line.pt2_y, fill);
            break;
    }

    if (shape->style.rotation != 0) {
        fprintf(file, "    </g>\n");
    }
}


/**
 * @brief Write all shapes to an 800x600 SVG with black outlines.
 * @param list List to export without changing it.
 * @param filename Output path; an existing file is overwritten.
 * @return 1 on success, 0 on invalid arguments or file errors.
 */
int export_svg(const list_t* list, const char* filename) {
    if (list == NULL || filename == NULL) {
        return 0;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Impossible de creer le SVG\n");
        return 0;
    }

    fprintf(file,
            "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            "width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n");

    fprintf(file, "  <g fill=\"none\" stroke=\"black\">\n");

    const node_t* current = list->start;

    while (current != NULL) {
        svg_write_shape(file, current->shape);
        current = current->next;
    }

    fprintf(file, "  </g>\n");
    fprintf(file, "</svg>\n");

    int success = !ferror(file);

    if (fclose(file) != 0) {
        success = 0;
    }

    return success;
}
