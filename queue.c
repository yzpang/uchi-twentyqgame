
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* create_queue
 * purpose: create and initialize queue with no items in it
 * inputs: none
 * output: pointer to the newly created and initialized queue
 */
queue* create_queue()
{
	llist *empty_llist = create_llist();
	queue *new = NULL;
	new = (queue *)malloc(sizeof(queue));
	new->st = empty_llist;
	return new;
}

/* enqueue
 * purpose: insert an item into the queue
 * inputs: queue* the queue on which to enqueue the data
 * void* the item to enqueue on the queue
 * return value: none
 */
void enqueue(queue* q, void* item)
{
	insert_head(q->st,item); // here we enq to the beginning
}

/* dequeue
 * purpose: return the item that was enqueue least recently
 * inputs: queue from which to dequeue the item
 * output: item that used to be the top of the queue
 */
void* dequeue(queue* q)
{
	if (q->st->head == NULL)
		return NULL;

	void *thing = peek_tail(q->st);
	remove_tail(q->st); // here we deq from the end
	return thing;
}

/* queue_is_empty
 * purpose: pseudoboolean function that returns whether or not a queue is empty
 * inputs: queue
 * output: pseudoboolean value - 0 for false, nonzero for true
 */
int queue_is_empty(queue* q)
{
	return ((q->st->head == NULL) && (q->st->tail == NULL));
}

