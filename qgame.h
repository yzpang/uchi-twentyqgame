
#ifndef QGAME_H
#define QGAME_H

#include "qinfo.h"
#include "qtree.h"


/* SECTION I: READING FILE */

/* note that some functions are ignored in this .h file becuase 
 * they will note be called in other files
 */

/* info_from_line: given one line of string, and the number of sentence
 * we want to return, return the corresponding qinfo struct
 */
qinfo* info_from_line(char *str, int which);


/* SECTION II: BUILDING TREE */

/* create_qtree_from_file: create a qtree from a file given the
 * filename, and return the qtree
 */
qtree* create_qtree_from_file(char *filename);


/* SECTION III: STORING TREE TO FILE WHEN EXITING GAME */

/* writing_to_file: given the existing tree and a filename, write
 * the information of the tree to the file in the specifed format
 * as requried
 */
void writing_to_file(qtree *tree, char *filename);


/* SECTION IV: GAME PLAY */

void gameplay(char *filename);


#endif

