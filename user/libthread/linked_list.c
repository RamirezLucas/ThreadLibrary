/** @file linked_list.c
 *
 *  @brief This file contains the definitions for functions which can be used
 *   to insert or delete elements from the generic linked kist with elements
 *   of type void*
 *
 *  @author akanjani, lramire1
 */

#include <data_structures.h>
#include <linked_list.h>
#include <stdlib.h>

/** @brief Initialize the linked list
 *
 *  The function must be called once before any other function in this file,
 *  otherwise the list's behavior is undefined.
 *
 *  @param queue  The linked list to initialize
 *  @param find   Generic function to find a particular element in the list
 *
 *  @return 0 on success, a negative error code on failure
 */
int linked_list_init(generic_linked_list_t *list, int (*find)(void *, void *)) {

  // Check validity of arguments
  if (list == NULL) {
    return -1;
  }

  // Initialize the linked list
  list->head = NULL;
  list->tail = NULL;
  list->find = find;
  return 0;
}

/** @brief Insert a new node at the end of the list
 *
 *  @param list   A linked list
 *  @param value  The new node's value
 *
 *  @return 0 on success, a negative error code on failure
 */
int linked_list_insert_node(generic_linked_list_t *list, void *value) {

  // Check validity of arguments
  if (list == NULL || value == NULL) {
    return -1;
  }

  // Allocate a new node
  generic_node_t *new_node = malloc(sizeof(generic_node_t));
  if (new_node == NULL) {
    return -1;
  }
  new_node->value = value;
  new_node->next = NULL;

  if (list->head == NULL && list->tail == NULL) {
    // Linked list is empty
    list->head = new_node;
    list->tail = new_node;
  } else {
    // Linked list is non-empty
    list->tail->next = new_node;
    list->tail = new_node;
  }

  return 0;
}

/** @brief Delete a node in the linked list
 *
 *  @param list   A linked list
 *  @param value  The element to delete
 *
 *  @return The deleted node's value if the element was found in the list.
 *  NULL otherwise
 */
void *linked_list_delete_node(generic_linked_list_t *list, void *value) {

  // Check validity of arguments
  if (list == NULL || value == NULL) {
    return NULL;
  }

  // Check that the find function exists
  if (list->find == NULL) {
    return NULL;
  }

  // Iterator on the list's elements
  generic_node_t *node = list->head, *prev = NULL;

  // Loop over the list
  while (node != NULL) {
    if (list->find(node->value, value)) {
      if (prev == NULL && node->next == NULL) {
        // Node is only element in linked list
        list->head = NULL;
        list->tail = NULL;
      } else if (prev == NULL) {
        // Node is list's head
        list->head = node->next;
      } else if (node->next == NULL) {
        // Node is list's tail
        list->tail = prev;
        list->tail->next = NULL;
      } else {
        // Node is between other nodes
        prev->next = node->next;
      }
      void *ret = node->value;
      free(node);
      return ret;
    }
    prev = node;
    node = node->next;
  }
  return NULL;
}

/** @brief Get a node in the linked list
 *
 *  @param list   A linked list
 *  @param value  The element to ger
 *
 *  @return The element if it was found in the list. NULL otherwise.
 */
void *linked_list_get_node(const generic_linked_list_t *list, void *value) {

  // Check validity of arguments
  if (list == NULL || value == NULL) {
    return NULL;
  }

  // Check that the find function exists
  if (list->find == NULL) {
    return NULL;
  }

  // Iterator on the list's elements
  generic_node_t *iterator = list->head;

  // Loop over the list
  while (iterator != NULL) {
    if (list->find(iterator->value, value)) {
      return iterator->value;
    }
    iterator = iterator->next;
  }

  return NULL;
}
