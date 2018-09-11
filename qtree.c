
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "queue.h"
#include "qinfo.h"
#include "qtree.h"

/* CREATION FUNCTIONS */

/* create_qtree: create a qtree with memory allocated, yet we do not
 * allocate memory for qinfo in this function
 */
qtree* create_qtree()
{
	qtree *new = NULL;
	new = (qtree *)malloc(sizeof(qtree));

	// for precaution
	new->val = 1;
	new->info = NULL;
	new->lsub = NULL;
	new->rsub = NULL;

	return new;
}

/* free_qtree: free all the nodes of the qtree but not the items */
void free_qtree(qtree* tree)
{
	if (tree != NULL)
	{
		free_qtree(tree->lsub);
		free_qtree(tree->rsub);
		free(tree);
	}
}

/* INFORMATIONAL FUNCTIONS */

/* provide some generic functions that will apply the same
 * function to all nodes in a qtree. Use a preorder traversal.
 */
void do_to_all(qtree *tree, void (*func)(void*))
{
	// do nothing if tree is NULL
	if (tree == NULL)
		return;

	func((qinfo *)(tree->info)); // if struct contains qinfo* not void*
	do_to_all(tree->lsub,func);
	do_to_all(tree->rsub,func);
}

/* MODIFICATION FUNCTIONS */

/* qtree_insert: given the parent info of the sentence to be inserted,
 * given the info to be inserted, and the existing tree, insert the
 * sentence in the correct place
 */
qtree* qtree_insert(qtree *tree, qinfo *info, qinfo *parent,
			int (*compare)(void *, void *))
{
	if (info == NULL)
		return NULL;

	// this is not the init tree, tree gets to NULL if there
	// is no matching parent info along a path
	// this tree == NULL case is used for recursion base case
	if (tree == NULL)
		return NULL;
	// however this is for the init tree which tree is not NULL
	// but tree->info is NULL as defined by our creation process
	else if (tree->info == NULL) 
	{
		tree->info = info;
		return tree;
	}

	int result = compare(parent,tree->info);
	if (result != 0)
	{
		// recursion smaller case and general case
		qtree *sub;
		sub = qtree_insert(tree->lsub,info,parent,compare);
		if (sub != NULL) // if left sub has a match
		{
			tree->lsub = sub;
			return tree;
		}

		// if left subtree has no matches
		sub = qtree_insert(tree->rsub,info,parent,compare);
		if (sub != NULL) // if left sub not match but right does
		{
			tree->rsub = sub;
			return tree;
		}
	       	
		// if left and right sub does have not a match
		return NULL;
	}
	else
	{
		qtree *new = (qtree *)malloc(sizeof(qtree));
		new->info = info; 
		new->lsub = NULL; // for precaution
		new->rsub = NULL;
		// if left sub is empty insert to left, otherwise right
		if (tree->lsub == NULL)
		{
			tree->lsub = new;
			tree->lsub->val = 2*(tree->val);
			return tree;
		}
		else if (tree->rsub == NULL)
		{
			tree->rsub = new;
			tree->rsub->val = 2*(tree->val)+1;
			return tree;
		}
		else
			return NULL; // error
	}

}

/* qtree_remove: remove the qinfo given the tree, qinfo, and a compare
 * function pointer, and return the item being removed
 */
void* qtree_remove(qtree *tree, qinfo *info, 
		int (*compare)(void *, void *))
{
	if ((info == NULL) || (tree == NULL)) // tree NULL as base case
		return NULL;
	else if (tree->info == NULL) // this is for init tree NULL
		return NULL;

	int result = compare(info,tree->info);
	if (result == 0) // then tree has one node and it is the target
	{
		void *rm0 = tree->info;
		tree->info = NULL;	
		return rm0;
	}

	if (tree->lsub != NULL)
	{
		result = compare(info,tree->lsub->info);
		if (result != 0)
			qtree_remove(tree->lsub,info,compare);
		else
		{
			void *rm = tree->lsub->info;
			free(tree->lsub);
			tree->lsub = NULL;
			return rm;
		}
	}

	if (tree->rsub != NULL)
	{
		result = compare(info,tree->rsub->info);
		if (result != 0)
			qtree_remove(tree->rsub,info,compare);
		else
		{
			void *rm2 = tree->rsub->info;
			free(tree->rsub);
			tree->rsub = NULL;
			return rm2;
		}
	}

	return NULL;
}

/* ITERATOR */

/* aux_itr: return the pointer to the queue that stores every
 * node (qtree) in the order specified by preorder traversal
 */
queue* aux_itr(qtree *t, queue *thatq)
{
	if (t == NULL)
		return thatq;
	qv *new = (qv *)malloc(sizeof(qv));
	new->info = t->info;
	new->val = t->val;

	enqueue(thatq,new);
	thatq = aux_itr(t->lsub,thatq);
	thatq = aux_itr(t->rsub,thatq);

	return thatq;
}

/* iterate:
 * an iterator that navigates the tree with an preorder
 * traversal. If a non-NULL tree is passed in, then the
 * iterator resets to the first node. It returns the item in the
 * first node (as defined by preorder traversal). If a NULL tree
 * is passed in, then return the item in the next node. 
 */
void* iterate(qtree *t)
{
	static node *nptr = NULL;
	queue *thatq = create_queue(); // remember to free
	static queue *q = NULL;

	// if non-NULL tree is passed in, initialize
	if (t != NULL)
	{
		q = aux_itr(t,thatq);
		nptr = q->st->tail;
	}

	// check if nptr is NULL
	if (nptr == NULL)
		return NULL;

	// if NULL tree is passed in, return next item
	// in this case, qv
	void *nxt = dequeue(q);
	nptr = q->st->tail;

	return nxt;
}

