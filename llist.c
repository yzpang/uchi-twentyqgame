
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

/* create_list
 * purpose: create a linked list structure and initialize to empty list
 * inputs: none
 * outputs: pointer to newly created and initialized linked list
 */
llist *create_llist()
{
	llist *newlist = NULL;
	newlist = (llist *)malloc(sizeof(llist));
	
	newlist->head = NULL;
	newlist->tail = NULL;

	return newlist;
}

/* insert_head
 * purpose: insert an item to become the first item in a linked list.
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 *   item - a pointer to the item to be inserted into the linked list
 * return: nothing
 */
void insert_head(llist *list, void *item)
{
	node *fst = NULL;
	fst = (node *)malloc(sizeof(node));
	fst->item = item;
	fst->next = list->head;

	list->head = fst;

	// if tail is NULL
	if (list->tail == NULL)
		list->tail = fst;
}

/* remove_head
 * purpose: remove the item that is at the beginning of a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 */
void remove_head(llist *list)
{
	if (list->head == NULL)
		return;
	else if (list->head->next == NULL)
	{
		list->head->item = NULL;
		list->tail->item = NULL;
		list->head = NULL;
		list->tail = NULL;

		return;
	}

	// if more than one elements in the list, draw picture
	list->head->item = NULL;
	list->head = list->head->next;
}

/* peek_head
 * purpose: return the first item in a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 *   void * - the first item stored in the linked list 
 */
void *peek_head(llist *list)
{
	if (list->head == NULL)
		return NULL;
	else
		return (list->head->item);
}


/* insert_tail
 * purpose: insert an item to become the last item in a linked list.
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 *   item - a pointer to the item to be inserted into the linked list
 * return: nothing
 */
void insert_tail(llist *list, void *item)
{
	// if original list is empty
	if (list->head == NULL)
	{
		insert_head(list,item);
		return;
	}

	// if the original list is not empty
	node *last = NULL;
	last = (node *)malloc(sizeof(node));
	last->item = item;
	last->next = NULL;

	list->tail->next = last; // the old tail
	list->tail = last; // now update tail to last
}

/* remove_tail
 * purpose: remove the item that is at the beginning of a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return: nothing
 */
void remove_tail(llist *list)
{
	// if llist empty

	if (list->head == NULL)
		return;
	
	// if only one element

	if (list->head->next == NULL)
	{
		list->head->item = NULL;
		list->tail->item = NULL;
		list->tail->next = NULL;
		list->head = NULL;
		list->tail = NULL;

		return;
	}
	
	// if there are more than one element

	list->tail->item = NULL;
	list->tail = NULL;
	
	// make tail pointer to previous one

	node *tmp;
	for (tmp = list->head; (tmp->next != NULL) && (tmp != NULL) &&
		(tmp->next->next != NULL); tmp = tmp->next)
		;
	list->tail = tmp;
	list->tail->next = NULL;
}

/* peek_tail
 * purpose: return the last item in a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 *   void * - the last item stored in the linked list (which is a pointer)
 */
void *peek_tail(llist *list)
{
	if (list->tail == NULL)
		return NULL;
	else
		return list->tail->item;
}

/* list_is_empty
 * purpose: return a pseudo-boolean indicating whether or not the 
 *          list is empty
 * input: list
 * output: 0 if not empty, nonzero if empty
 */
int list_is_empty(llist *list)
{
	return ((list->head == NULL) && (list->tail == NULL));
}

