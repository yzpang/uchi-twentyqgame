
#ifndef QINFO_H
#define QINFO_H

union info{
	char *question;
	char *guess;
}; 

enum Q_Tag {QUESTION=0, GUESS};

typedef struct {
	enum Q_Tag tag;
	union info str;
} qinfo;

/* create_qinfo: create a qinfo given the string qinfo will contain
 * and the tag (either question or guess) that qinfo has
 */
qinfo* create_qinfo(char *str, enum Q_Tag tag);

/* print_qinfo: print out the tag and the string of the qinfo */
void print_qinfo(void *);

/* compare_qinfo: return 0 if two qinfos are the same, that is, they
 * have the same strings and the same tags, and return -1 if either of
 * the two differs
 */
int compare_qinfo(void *, void *);

#endif

