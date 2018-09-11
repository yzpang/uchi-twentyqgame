
#ifndef QUEUE_H
#define QUEUE_H
#include "llist.h"

typedef struct _queue {
	llist *st;
} queue;

/* create_queue
 * purpose: create and initialize queue with no items in it
 * inputs: none
 * output: pointer to the newly created and initialized queue
 */
queue* create_queue();

/* enqueue
 * purpose: insert an item into the queue
 * inputs: queue* the queue on which to enqueue the data
 * void* the item to enqueue on the queue
 * return value: none
 */
void enqueue(queue*, void*);

/* dequeue
 * purpose: return the item that was enqueue least recently
 * inputs: queue from which to dequeue the item
 * output: item that used to be the top of the queue
 */
void* dequeue(queue*);

/* queue_is_empty
 * purpose: pseudoboolean function that returns whether or not a queue is empty
 * inputs: queue
 * output: pseudoboolean value - 0 for false, nonzero for true
 */
int queue_is_empty(queue*);

#endif

