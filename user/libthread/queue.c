/** @file queue.c
 *
 *  @brief This file contains the definitions for functions which can be used
 *   to insert or delete elements from the generic queue with elements of type
 *   void*
 *
 *  @author akanjani, lramire1
 */


#include <queue.h>
#include <stdlib.h>

/** @brief Makes a generic_node_t type node to be added in the queue
 *
 *  @param value The value to be stored in the list casted as void*
 *
 *  @return NULL on error, or a pointer to the generic_node_t type new node
 */
generic_node_t *make_node( void *value ) {

  // Allocate the space for the new node
  generic_node_t *new_node = ( generic_node_t *) malloc(
    sizeof( generic_node_t ) );

  if ( !new_node ) {
    // malloc error
    return NULL;
  }

  // Set the appropriate values for the node
  new_node->value = value;
  new_node->next = NULL;

  return new_node;
}

/** @brief Inserts a generic_node_t type node at the tail end of the queue
 *
 *  @param value The value to be stored in the list casted as void*
 *  @param list A pointer to a generic_queue_t structure which holds
 *   the head and tail pointer of a queue
 *
 *  @return 0 on success, a negative error code on failure
 */
int insert_node( generic_queue_t *list, void *value ) {

  generic_node_t **head = &list->head;
  generic_node_t **tail = &list->tail;

  if ( !head || !tail ) {
    // Invalid double pointer
    return -1;
  }

  // Make a new node
  generic_node_t *new_node = make_node( value );

  if ( !new_node ) {
    // Error creating a new node
    return -1;
  }

  if ( *tail == NULL && *head == NULL ) {
    // head is NULL. This is the first element of the list
    *tail = new_node;
    *head = new_node;
    return 0;
  }

  // Add the new node to the end of the list 
  (*tail)->next = new_node;

  return 0;
}

/** @brief Deletes a generic_node_t type node from the front end of the queue
 *
 *  @param list A pointer to a generic_queue_t structure which holds
 *   the head and tail pointer of a queue
 *
 *  @return void* The value of the element in the deleted node cast as a void*
 *   or NULL on error
 */
void *delete_node( generic_queue_t *list ) {

  generic_node_t **head = &list->head;
  generic_node_t **tail = &list->tail;

  if ( !head || !tail ) {
    // Invalid double pointer
    return NULL;
  }

  if ( *head == NULL || *tail == NULL ) {
    // list is empty or the tail/head pointer is messed up
    return NULL;
  }

  if ( *head == *tail ) {
    // The only element in the list
    *tail = NULL;
  }

  // Store the current head
  generic_node_t *tmp = *head;
  void *ret = (*head)->value;

  // Update head
  *head = ( *head )->next;

  // Free the space for deleted node
  free( tmp );
  tmp = NULL;

  return ret;
} 