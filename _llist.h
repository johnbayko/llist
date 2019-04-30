/*
 * _llist.h - linked list library header - library version.
 *
 * See llist.h for revision history.
 */

#ifndef _LLIST_H
#define _LLIST_H

/* include macros and typedefs for llist */
#include <stdlib.h>
#include "llistmacro.h"

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

LIST_TYPE *create_list(LIST_TYPE *node);
LIST_TYPE *init_node(LIST_TYPE *node);
LIST_TYPE *node_alloc(size_t size);
LIST_TYPE *head_node(LIST_TYPE *node);
LIST_TYPE *tail_node(LIST_TYPE *node);
LIST_TYPE *insert_node(LIST_TYPE *list, LIST_TYPE *node);
LIST_TYPE *_insert_node(LIST_TYPE *list, LIST_TYPE *node);
LIST_TYPE *append_node(LIST_TYPE *list, LIST_TYPE *node);
LIST_TYPE *del_node(LIST_TYPE *node);
LIST_TYPE *free_node(LIST_TYPE *node);

/* prototypes for llist_l.c functions */

LIST_TYPE *insert_list(LIST_TYPE *list1, LIST_TYPE *list2);
LIST_TYPE *append_list(LIST_TYPE *list1, LIST_TYPE *list2);

/* prototypes for llscan.c functions */

LIST_TYPE *scan_list(LIST_TYPE *list, bool (*func)(LIST_TYPE *) );

#endif  // _LLIST_H
