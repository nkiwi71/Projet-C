#ifndef LIST_H
#define LIST_H

/** @file list.h
 * @brief Linked list of shapes.
 */

#include "shapes.h"

/** @brief One shape and a link to the next node. */
typedef struct node_s {
    shape_t* shape;       /**< Shape owned by this node. */
    struct node_s* next;  /**< Next node in the list, or NULL. */
} node_t;

/** @brief List endpoints and node count. */
typedef struct list_s {
    node_t* start;        /**< First node, or NULL when empty. */
    node_t* last;         /**< Last node, or NULL when empty. */
    unsigned int length;  /**< Number of nodes in the list. */
} list_t;

/**
 * @brief Allocate an empty list.
 * @return New list, or NULL on allocation failure.
 */
list_t* create_list(void);

/**
 * @brief Allocate a node and append it to the list.
 * @param list List to update; NULL is ignored.
 * @param new_shape Shape owned by the list only after successful insertion.
 */
void add_shape(list_t* list, shape_t* new_shape);

/**
 * @brief Unlink a node and free both the node and its shape.
 * @param list List to update.
 * @param index Shape position, starting at 1.
 * @return true on deletion, false for an invalid list or index.
 */
bool delete_shape(list_t* list, int index);

#endif
