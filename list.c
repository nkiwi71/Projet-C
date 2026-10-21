#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "shapes.h"


/**
 * @brief Allocate a list with no nodes.
 * @return Empty list, or NULL if allocation fails.
 */
list_t* create_list(void) {
    list_t* list = malloc(sizeof(list_t));
    if (list != NULL) {
        list->start = NULL;
        list->last = NULL;
        list->length = 0;
    }
    return list;
}

/**
 * @brief Allocate a node and append it to the list.
 * @param list List to update; NULL is ignored.
 * @param new_shape Shape owned by the list after successful insertion.
 */
void add_shape(list_t* list, shape_t* new_shape) {
    if (list == NULL || new_shape == NULL) return;

    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Memory allocation error for the list node.\n");
        return;
    }

    new_node->shape = new_shape;
    new_node->next = NULL;

    if (list->start == NULL) {
        list->start = new_node;
        list->last = new_node;
    } else {
        list->last->next = new_node;
        list->last = new_node;
    }

    list->length++;
}

/**
 * @brief Unlink a node, free its shape and update the list ends.
 * @param list List to update.
 * @param index Shape position, starting at 1.
 * @return true on deletion, false for an invalid list or index.
 */
bool delete_shape(list_t* list, int index) {
    if (list == NULL || index < 1 || (unsigned int) index > list->length) {
        return false;
    }

    node_t* node_to_delete = list->start;
    node_t* previous = NULL;

    for (int current_index = 1; current_index < index; current_index++) {
        previous = node_to_delete;
        node_to_delete = node_to_delete->next;
    }

    if (previous == NULL) {
        list->start = node_to_delete->next;
    } else {
        previous->next = node_to_delete->next;
    }

    if (node_to_delete == list->last) {
        list->last = previous;
    }

    free(node_to_delete->shape->style.fill_color);
    free(node_to_delete->shape);
    free(node_to_delete);
    list->length--;

    if (list->length == 0) {
        list->start = NULL;
        list->last = NULL;
    }

    return true;
}

