/*
   llist.h - linked list library header - user version.
  
   revision 1
   - I decided to add a revision number, so I know which version is the
   most recent (and hopefully, bug-free).
   revision 2 
   - split into llist.h, _llist.h, and llistmacro.h files. llist.h is 
   for user programs, _llist.h is for library source, and llistmacro.h 
   is common to both. Strong typing of new C compilers means that 
   "void **" doesn't work, so has to be replaced with "void *" in user 
   visible prototypes.
   revision 3
   - create_list() now returns the node.
   - replaced create_node() with node_alloc(), added create_node() macro
   for compatibility.
 */

#ifndef _LLIST
#define _LLIST 1

/* include macros and typedefs for llist */
#include <llistmacro.h>

/* function definitions */
/*
 * create_list();    returns nothing
 *
 * LIST_TYPE *insert_node(),
 *           *_insert_node(),
 *           *create_node(),
 *           *del_node(),
 *           *free_node(),
 *           *head_node(),
 *           *insert_list(),
 *           *append_list(),
 *           *scanlist();
 */

/* prototypes for llist.c functions */

void *create_list(void *node);
void *node_alloc(int size);
void *head_node(void *node);
void *tail_node(void *node);
void *insert_node(void *list, void *node);
void *_insert_node(void *list, void *node);
void *append_node(void *list, void *node);
void *del_node(void *node);
void *free_node(void *node);

/* prototypes for llist_l.c functions */

void *insert_list(void *list1, void *list2);
void *append_list(void *list1, void *list2);

/* prototypes for llscan.c functions */

void *scan_list(void *list, int (*func)(void *) );

#endif
