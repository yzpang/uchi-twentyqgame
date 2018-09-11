
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qinfo.h"

/* create_qinfo: create a qinfo given the string qinfo will contain
 * and the tag (either question or guess) that qinfo has
 */
qinfo* create_qinfo(char *str, enum Q_Tag tag)
{
	if (str == NULL)
		return NULL;
	qinfo *new = NULL;
	new = (qinfo *)malloc(sizeof(qinfo));
	new->tag = tag;
	if (tag == 0)
		(new->str).question = str;
	else
		(new->str).guess = str;
	return new;
}

/* print_qinfo: print out the tag and the string of the qinfo */
void print_qinfo(void *v)
{
	qinfo *q = (qinfo *)v;
	printf("%d: %s\n",q->tag, q->str.question);

	// what about the guesses? 
}

/* get_string: return the string (either question or guess) of qinfo,
 * given the qinfo struct
 */
char* get_string(void *v)
{
	int tag = ((qinfo *)v)->tag;
	char *s;
	if (tag == 0)
		s = ((qinfo *)v)->str.question;
	else
		s = ((qinfo *)v)->str.guess;
	return s;
}

/* compare_qinfo: return 0 if two qinfos are the same, that is, they
 * have the same strings and the same tags, and return -1 if either of
 * the two differs
 */
int compare_qinfo(void *v1, void *v2)
{
	int tag1 = ((qinfo *)v1)->tag;
	int tag2 = ((qinfo *)v2)->tag;
	char *s1 = get_string(v1);
	char *s2 = get_string(v2);

	if ((tag1 == tag2) && (strcmp(s1,s2) == 0))
		return 0;
	else
		return -1;
}

