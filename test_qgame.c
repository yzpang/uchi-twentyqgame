
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "queue.h"
#include "qinfo.h"
#include "qtree.h"
#include "qgame.h"

int main(int argc, char *argu[])
{
	if (argc == 1)
		gameplay(NULL);
	else
		gameplay(argu[1]);
/*
	char *q0 = "Eagle?";
	qinfo *qi0 = create_qinfo(q0,0);
        char *q1 = "Richard?";
        qinfo *qi1 = create_qinfo(q1,0);
        char *q2 = "Grace?";
        qinfo *qi2 = create_qinfo(q2,0);
        char *q3 = "Michael?";
        qinfo *qi3 = create_qinfo(q3,0);
        char *q4 = "Anya?";
        qinfo *qi4 = create_qinfo(q4,0);
        char *q5 = "Michelle?";
        qinfo *qi5 = create_qinfo(q5,0);
        char *q6 = "Yvonne?";
        qinfo *qi6 = create_qinfo(q6,0);
//	print_qinfo((qinfo *)qi0);

//	char *ln0 = "00Is it alive?,Is it smaller than a breadbox?,Does it live in the ocean?";
//	printf("this is sentence length %d\n",(sentence_length(ln0))[2]);

//printf("this is sentence %s\n",one_sentence(ln0,0));
//printf("this is sentence %s\n",one_sentence(ln0,1));
//printf("this is sentence %s\n",one_sentence(ln0,2));

//info_from_line(ln0,0);

qtree *init = create_qtree();
init = qtree_insert(init,qi0,NULL,&compare_qinfo);
//print_qinfo(init->info);
init = qtree_insert(init,qi1,qi0,&compare_qinfo);
//print_qinfo(init->info);
//print_qinfo(init->lsub->info);
init = qtree_insert(init,qi2,qi1,&compare_qinfo);
//print_qinfo(init->info);
//print_qinfo(init->lsub->info);
//print_qinfo(init->lsub->lsub->info);
init = qtree_insert(init,qi3,qi2,&compare_qinfo);
//print_qinfo(init->lsub->lsub->lsub->info);
init = qtree_insert(init,qi4,qi1,&compare_qinfo); // Anya
//print_qinfo(init->lsub->rsub->info);
init = qtree_insert(init,qi5,qi0,&compare_qinfo);
//print_qinfo(init->rsub->info); // Michelle
init = qtree_insert(init,qi6,qi5,&compare_qinfo);
//print_qinfo(init->rsub->lsub->info); // Yvonne

print_qinfo(init->info);
print_qinfo(init->rsub->info);
qtree_remove(init,qi6,&compare_qinfo);
print_qinfo(init->info);
print_qinfo(init->lsub->lsub->lsub->info);
print_qinfo(init->rsub->info);
//print_qinfo(init->rsub->lsub->info);

// testing create_qtree_from_file
char *file0 = "gameinfo.txt";
qtree *ffile = create_qtree_from_file(file0);
//print_qinfo(ffile->rsub->lsub->info);
//printf("%d this is val\n",ffile->rsub->lsub->val);

queue *thatq = create_queue();
queue *q = aux_itr(ffile,thatq);
void *item = iterate(ffile);
//print_qinfo(((qv *)item)->info);
//printf("%s this is first question\n",(((qv *)item)->info->str).question);


qtree *t = create_qtree();
t = qtree_insert(t,qi0,NULL,&compare_qinfo);
qtree_remove(t,qi0,&compare_qinfo);
printf("is t NULL? %d \n",(t == NULL));
*/


}

