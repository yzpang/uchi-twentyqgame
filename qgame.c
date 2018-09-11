
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "qtree.h"
#include "qinfo.h"
#include "qgame.h"

/* SECTION I: READING FILE */

/* sentence_length: return the array of lengths of three sentences
 * given a line of three sentences whose format is as specified in
 * the requirement
 */
int* sentence_length(char *str)
{
	if (str == NULL)
		return NULL; // error
	str += 2;
	int this = 0; // which sentence we are at, 0, 1, or 2
	int *count = (int *)malloc(sizeof(int)*3); // for each sentence

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;

	for ( ; (*str != '\0') && (*str != '\0'); str++)
	{
		if (*str != ',')
			(count[this])++;
		else
			this++;
	}
	
	return count;
}

/* one_sentence: return the string of the specified sentence */
char* one_sentence(char *str, int which)
{
	int *lenarr = sentence_length(str);
        char *s = (char *)malloc(sizeof(char)*(lenarr[which]+1));

        int this = 0; // which sentence we are at

	str += 2; // skipping the first two numbers
	int i = 0;
        for ( ; (*str != '\0') && (*str != '\n'); str++)
        {
		if (*str == ',')
			this++;
		else if (which != this)
			;
		else
		{
			s[i] = *str;
			i++;
		}
	}
	s[i] = '\0';
	free(lenarr); // free memory
	return s;
}

/* info_from_line: given one line of string, and the number of sentence
 * we want to return, return the corresponding qinfo struct
 */
qinfo* info_from_line(char *str, int which)
{
	if (str == NULL)
		return NULL;
	
	// first store the two numbers
	int t;
	if (which == 0)
		t = 0; // question
	else if (which == 1)
		t = *str-'0';
	else if (which == 2)
	{
		str++;
		t = *str-'0';
		str--;
	}

	// now store the question
	char *sentence = one_sentence(str,which);
	qinfo *new = create_qinfo(sentence,t);
	
	return new;
}

/* PART II: BUILDING TREE */

/* create_qtree_from_file: create a qtree from a file given the
 * filename, and return the qtree
 */
qtree* create_qtree_from_file(char *filename)
{
	if (filename == NULL)
		return NULL;

	qtree *t = create_qtree();

	FILE *fp;
	char buf[BUFSIZ] = "Garbage";
	if ((fp = fopen(filename,"r")) == NULL)
	{
		fprintf(stderr,"Could not open file %s\n",filename);
		return NULL;
	}
	int line = 0; // delete later if not useful
	qinfo *info0, *info1, *info2;
	while (fgets(buf,sizeof(buf),fp) != NULL)
	{
		info0 = info_from_line(buf,0);
		info1 = info_from_line(buf,1);
		info2 = info_from_line(buf,2);

		if (line == 0)
			qtree_insert(t,info0,NULL,&compare_qinfo);
		
		qtree_insert(t,info1,info0,&compare_qinfo);
		qtree_insert(t,info2,info0,&compare_qinfo);

		line++;
	}
	return t;
}

/* SECTION III: STORING TREE TO FILE WHEN EXITING GAME */

int size_of_qtree(qtree *tree)
{
	int max = 0;
	qv *item = NULL;
	for (item = (qv *)(iterate(tree)); item != NULL;
				item = (qv *)(iterate(NULL)))
	{
		if (item->val > max)
			max = item->val;
	}
	return max; // think here how much space we need!
}

/* init_arr: initialize every *arr of a **arr to NULL */
void init_arr(void **arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = NULL;
}

/* writing_to_file: given the existing tree and a filename, write
 * the information of the tree to the file in the specifed format
 * as requried
 */
void writing_to_file(qtree *tree, char *filename)
{
	FILE *fp;
	fp = fopen(filename,"w"); // old contents discarded

	void **auxarr = NULL; // arr storing all nodes
	int size_arr = size_of_qtree(tree)+1;
	auxarr = (void **)malloc(sizeof(qv *)*size_arr);
	init_arr(auxarr,size_arr);

	int i;
	qv *item = NULL;
	for (i = 1, item = (qv *)(iterate(tree)); item != NULL;
				item = (qv *)(iterate(NULL)), i++)
		auxarr[i] = item;

	// now we get the array, and we want an array that is sorted
	// by value in the qv struct
	void **arr = NULL;
	arr = (void **)malloc(sizeof(qv *)*size_arr);
	init_arr(arr,size_arr);

	for (i = 1; i < size_arr; i++)
	{
		if (auxarr[i] != NULL)
		{
			int v = ((qv *)auxarr[i])->val;
			arr[v] = auxarr[i];
		}
	}

	// now we get the array
	for (i = 1; (2*i+1) < size_arr; i++)
	{
	
	    qv *qv0 = arr[i];
	    if (qv0 == NULL)
		;
	    else
	    {
		qv *qv1 = arr[2*i];
		qv *qv2 = arr[2*i+1];
		if ((qv1 != NULL) && (qv2 != NULL))
		{	
			int qv1_tag = qv1->info->tag;
			int qv2_tag = qv2->info->tag;
			fprintf(fp,"%d",qv1_tag);
			fprintf(fp,"%d",qv2_tag);
			fprintf(fp,"%s,",qv0->info->str.question);
			if (qv1_tag == 0)
				fprintf(fp,"%s,",qv1->info->str.question);
			else
				fprintf(fp,"%s,",qv1->info->str.guess);
			if (qv2_tag == 0)
				fprintf(fp,"%s\n",qv2->info->str.question);
			else
				fprintf(fp,"%s\n",qv2->info->str.guess);
		}
	    }
	}

	// we now free everything, what about the qvs?
	for (i = 1; i < size_arr; i++)
	{
		if (arr[i] != NULL)
			free(arr[i]);
	}
	free(auxarr);
	free(arr);

	fclose(fp);
}
	


/* PART IV: PLAY GAME */

/* get_word_input: read user input, given the input is string, and
 * return the string (char pointer) as a result
 */
char* get_word_input()
{
	char buffer[BUFSIZ];
	char *response;
	fgets(buffer,100,stdin);
	response = strdup(buffer);
	int length = strlen(response);
	response[length-1] = '\0';

	return response;
}


/* guessing: print guessings to screen, process input, and return 1
 * if user inputs yes, 0 otherwise. 
 */
unsigned int guessing(qinfo *info)
{
	int again = 1;
	while (again == 1)
	{
		printf("Now, wait, don't tell me - %s ",info->str.guess);
		printf("(yes or no): ");

		char *response = get_word_input();

		char *yes = "yes";
		char *no = "no";
		if ((strcmp(response,yes) != 0) && 
				(strcmp(response,no) != 0))
			; // again through while loop
		else
		{
			again = 0;
			if (strcmp(response,yes) == 0)
			{
				printf("Great! I got it! \n");
				return 1;
			}
			else
			{
				printf("Oh, no, I was so sure...\n");
				return 0;
			}
				
		}
	}

	return 0; // error
}

/* middle_question: print the a question, instead of a guess, to screen,
 * process input, and return 1 if yes, return 0 if no
 */
int middle_question(qinfo *info)
{
	int again = 1;
	while (again == 1)
	{
		printf("%s (yes or no): ",(info->str).question);
		char *response = get_word_input();
		char *yes = "yes";
		char *no = "no";
		if ((strcmp(response,yes) != 0) &&
				(strcmp(response,no) != 0))
			; // again through while loop
		else
		{
			again = 0;
			if (strcmp(response,yes) == 0)
				return 1;
			else
				return 0;
		}
	}
	return 0; // error
}


/* would_you_play_again: ask the question would you play again, read
 * and process input, and return 1 if the player would like to play
 * again, and 0 if the player does not want to
 */
unsigned int would_you_play_again()
{
	int again = 1;
	while (again == 1)
	{
		printf("Would you like to play again ");
                printf("(yes or no)? ");
		char *response = get_word_input();

		char *yes = "yes";
		char *no = "no";
		if ((strcmp(response,yes) != 0) &&
				(strcmp(response,no) != 0))
			; // again through while loop
		else
		{
			again = 0;
			if (strcmp(response,yes) == 0)
				return 1;
			else
				return 0;
		}
	}

	return 0; // error
}

/* turn_to_question: given a word and turn into a question, for
 * example, given "cat", return "Is it a cat?"
 */
char* turn_to_question(char *str)
{
	int length = strlen(str);
	char *new = (char *)malloc(sizeof(char)*(10+length));
	char *insert1 = "Is it a ";
	char *insert2 = "?";
	strcat(new,insert1);
	strcat(new,str);
	strcat(new,insert2);
	
	return new;
}

/* free_with_item: not only free every node in the qtree, but also free
 * the qinfo contained in every qtree node
 */
void free_with_item(qtree *tree)
{
	// base case
	if ((tree == NULL) || (tree->info == NULL))
		return;

	// smaller case
	if (tree->lsub != NULL)
		free_with_item(tree->lsub);
	if (tree->rsub != NULL)
		free_with_item(tree->rsub);

	// general case
	if (tree->info != NULL)
		free(tree->info);
	free(tree);
}

void gameplay(char *filename)
{
	qtree *tree = NULL;
	unsigned int play_again = 1;
	unsigned int machine_score = 0;
	unsigned int player_score = 0;

	// if there is a file, read from file
	if (filename != NULL)
	{
		// Part 2: build tree from file
		tree = create_qtree_from_file(filename);
	}
	// otherwise, create default tree
	else
	{
		tree = create_qtree();
		// insert starting question: Is it a crocodile?
		char *strcro = "Is it a crocodile?";
		qinfo* crocodile = create_qinfo(strcro,1);

		// insert in tree
		tree = qtree_insert(tree,crocodile,NULL,&compare_qinfo);
	}

	// now start the game play
	while(play_again)
	{
		// go through the tree one question at a time.
		// ask the user yes or no. When you get to a guess,
		// then look carefully at the guess.
		
		qv *item = NULL;
		int exp = 1; // exp value of the question to get to next
		int answer; // answer of yes or no question
		qinfo *oldparent; // old parent of incorrect guess

		for (item = (qv *)(iterate(tree)); item != NULL; 
					item = ((qv *)iterate(NULL)))
		{
			if (exp != (item->val))
				; // loop next time
			else if (item->info->tag == 0)
			{
				answer = middle_question(item->info);
				oldparent = item->info;

				if (answer == 1)
					exp = exp*2+1;
				else
					exp *= 2;
			}
			else if (item->info->tag == 1)
			{
			    char *actual; // new item
			    char *newq; // new question should be asked
			    answer = guessing(item->info);
		            if (answer == 1)
		                machine_score++;
               		    else
			    {
		                player_score++;

				printf("What was it? ");
				actual = get_word_input();
				printf("What extra question could ");
				printf("I have asked that would ");
				printf("have identified %s?\n",actual);
				newq = get_word_input();

				// remove old guess
				qtree_remove(tree,item->info,&compare_qinfo);

				// build new answer and parent qinfo
				char *actualguess = turn_to_question(actual);
				qinfo *newans = create_qinfo(actualguess,1);
				qinfo *newparent = create_qinfo(newq,0);
				
				// add new question
				qtree_insert(tree,newparent,oldparent,
						&compare_qinfo);
				
				// add old guess first given no is on
				// left side
				qtree_insert(tree,item->info,newparent,
						&compare_qinfo);

				// add new guess under new question
				qtree_insert(tree,newans,newparent,
						&compare_qinfo);

			    }
			    // afterward, score and whether again
               		    printf("Score: You %U, Me %U\n",
					player_score,machine_score);
		            play_again = would_you_play_again();
                	    if (!play_again)
		                printf("Bye!\n");
			}
		}
	}
	
	// write out the game to the file
	// but if filename is NULL then do not save the tree
        if (filename != NULL)
        	writing_to_file(tree,filename);

	free_with_item(tree);
}

