
#ifndef LLIST_H
#define LLIST_H

typedef struct _node node;

struct _node {
	void *item;
	node *next;
};

typedef struct _llist {	
	node *head;
	node *tail;
} llist;

/* create_list
 * purpose: create a linked list structure and initialize to empty list
 * inputs: none
 * outputs: pointer to newly created and initialized linked list
 */
llist *create_llist();

/* insert_head
 * purpose: insert an item to become the first item in a linked list.
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 *   item - a pointer to the item to be inserted into the linked list
 * return: nothing
 */

void insert_head(llist *list, void *item);
/* remove_head
 * purpose: remove the item that is at the beginning of a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 */

void remove_head(llist *list);
/* peek_head
 * purpose: return the first item in a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 *   void * - the first item stored in the linked list 
 */
void *peek_head(llist *list);


/* insert_tail
 * purpose: insert an item to become the last item in a linked list.
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 *   item - a pointer to the item to be inserted into the linked list
 * return: nothing
 */
void insert_tail(llist *list, void *item);

/* remove_tail
 * purpose: remove the item that is at the beginning of a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return: nothing
 */
void remove_tail(llist *list);

/* peek_tail
 * purpose: return the last item in a linked list
 * inputs: 
 *   list - pointer to llist struct in which to insert item
 * return:
 *   void * - the last item stored in the linked list (which is a pointer)
 */
void *peek_tail(llist *list);

/* list_is_empty
 * purpose: return a pseudo-boolean indicating whether or not the 
 *          list is empty
 * input: list
 * output: 0 if not empty, nonzero if empty
 */
int list_is_empty(llist *list);

#endif

