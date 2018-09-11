qgame: llist.c queue.c qinfo.h qinfo.c qtree.h qtree.c qgame.h qgame.c test_qgame.c
	clang -g -o qgame llist.c queue.c qinfo.c qtree.c qgame.c test_qgame.c
