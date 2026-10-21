#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>

/** @file actions.h
 * @brief Interactive shape actions.
 */

#include "list.h"

/**
 * @brief Read properties and append a new black shape.
 * @param my_list Non-NULL destination list.
 */
void action_create_shape(list_t* my_list);

/**
 * @brief Select and delete a shape from memory.
 * @param my_list List to update; may be NULL or empty.
 */
void action_delete_shape(list_t* my_list);

/**
 * @brief Select a shape and edit its position or dimensions.
 * @param my_list List to update; may be NULL or empty.
 */
void action_modify_shape(list_t* my_list);

/**
 * @brief Print shape numbers, positions and dimensions.
 * @param my_list List to display; may be NULL or empty.
 */
void action_visualize(list_t* my_list);

/**
 * @brief Export to dessin.svg and report the result.
 * @param my_list List to export.
 */

void action_export_svg(list_t* my_list);

/**
 * @brief Select a fill color for shapes.
 * @param fill Buffer to store the selected color.
 */
bool action_fill_color(char* fill);



#endif
