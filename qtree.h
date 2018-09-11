
#ifndef QTREE_H
#define QTREE_H

#include "queue.h"
#include "qinfo.h"

typedef struct _qtree qtree;

struct _qtree {
	int val;
	qinfo *info;
	qtree *lsub;
	qtree *rsub;
};

typedef struct {
	int val;
	qinfo *info;
} qv;

/* CREATION FUNCTIONS */

/* create_qtree: create a qtree with memory allocated, yet we do not
 * allocate memory for qinfo in this function
 */
qtree* create_qtree();

/* free_qtree: free all the nodes of the qtree but not the items */
void free_qtree(qtree* tree);

/* INFORMATIONAL FUNCTIONS */

/* provide some generic functions that will apply the same
 * function to all nodes in a qtree. Use a preorder traversal.
 */
void do_to_all(qtree *tree, void (*func)(void*));

/* MODIFICATION FUNCTIONS */

/* qtree_insert: given the parent info of the sentence to be inserted,
 * given the info to be inserted, and the existing tree, insert the
 * sentence in the correct place
 */
qtree* qtree_insert(qtree *tree, qinfo *info, qinfo *parent,
                        int (*compare)(void *, void *));

/* qtree_remove: remove the qinfo given the tree, qinfo, and a compare
 * function pointer, and return the item being removed
 */
void* qtree_remove(qtree *tree, qinfo *info,
                int (*compare)(void *, void *));

/* ITERATOR */

/* note that aux_itr is not put in this .h file because the function
 * is not used any other file than qtree.c
 */

/* iterate:
 * an iterator that navigates the tree with an preorder
 * traversal. If a non-NULL tree is passed in, then the
 * iterator resets to the first node. It returns the item in the
 * first node (as defined by preorder traversal). If a NULL tree
 * is passed in, then return the item in the next node.
 */
void* iterate(qtree *t);

#endif

