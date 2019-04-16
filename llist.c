/*
 * A linked list library
 * llist.c - basic node functions (create, add, delete, etc.)
 *
 * revision 1
 * - I decided to add a revision number, so I know which version is the
 * most recent (and hopefully, bug-free).
 */

#include <stdlib.h>
#include "_llist.h"    /* contains the real prototypes for llist.c */

#define TRUE 1
#define FALSE 0

#ifndef NULL
#define NULL 0
#endif

/*
 * Initializes a node to be a list (return value can be ignored)
 */
LIST_TYPE *create_list(node)
LIST_TYPE *node;
{
    node->NEXT = node->PREV = node; /* link node to self */
    node->HEAD = TRUE;
    return(node);
}

/*
 * Clear all node information so it's not mistaken for a llist
 */
LIST_TYPE *node_alloc(size)
int size;
{
LIST_TYPE *temp;

    if( temp = (LIST_TYPE *)malloc((size_t)size) ) {
        temp->NEXT = temp->PREV = NULL;
        temp->HEAD = FALSE;
    }
    return(temp);
}

/*
 * Find the head of the list by travelling back to the beginning.
 * If the node is not in a list, head_node calls create_list and returns
 * the node.
 * If HEAD is not set anywhere, head_node returns node.
 * If node is NULL, returns NULL.
 */
LIST_TYPE *head_node(node)
LIST_TYPE *node;
{
LIST_TYPE *temp, *mark;

    if(node) {            /* node exists */
        if(node->NEXT) {  /* node linked to a list */
            mark = node->NEXT;
            for(temp = node;
                    (temp->HEAD == 0) && (temp != mark);
                    temp = temp->PREV);
                return(temp);
        } else {
            create_list(node);  /* node not in list, make one */
            return(node);       /* it's now the head */
        }
    } else
        return((LIST_TYPE *)NULL);
}

/* Find the tail of the list (prev of head_node() ) */
LIST_TYPE *tail_node(node)
LIST_TYPE *node;
{
    node = head_node(node);
    if(node) {
        return(node->PREV);
    } else {
        return((LIST_TYPE *)NULL);
    }
}

/*
 * Add a node to a list - return new node, reset HEAD if needed.
 */
LIST_TYPE *insert_node(list,node)
LIST_TYPE *list,
          *node;
{
LIST_TYPE *temp;

    temp = _insert_node(list,node);
    if(temp->NEXT->HEAD) {
        temp->NEXT->HEAD = FALSE;
        temp->HEAD = TRUE;
    }
    return(temp);
}

/*
 * Insert a node within a list without checking HEAD.
 */
LIST_TYPE *_insert_node(list,node)
LIST_TYPE *list,
          *node;
{
    if(list == NULL) {    /* create list from node if no list */
        list = create_list(node);
    } else {
        if( (list->NEXT == NULL) || (list->PREV == NULL) ) {
            /* not a list - initialise it */
            /* if caused by program error, may drop nodes */
            create_list(list);
        }
        node->HEAD = FALSE;
        node->NEXT = list;
        node->PREV = list->PREV;
        list->PREV->NEXT = node;
        list->PREV = node;
    }
    return(node);        /* new head of list */
}

/*
   Link node to list tail, return list pointer (even if it's not the
   list head), or node if list is NULL. In other words, you can use
   "list = append_node(list, node)" any time.
 */
LIST_TYPE *append_node(list,node)
LIST_TYPE *list,
          *node;
{
LIST_TYPE *retnode;

    if(list) {
        retnode = list;
    } else {
        retnode = node;
    }
    _insert_node(head_node(list), node);
    return(retnode);
}

/*
   Remove a node from a list and return the following node.
   node is not deallocated, and must be kept track of by the
   program.
   You can use something like:
       while(list) { node=del_node(list); free(node); }
   to free a list.
 */
LIST_TYPE *del_node(node)
LIST_TYPE *node;
{
    if(node) {
        if( (node->NEXT == NULL) || (node->PREV == NULL) ) {
            /* not a valid list node, can't unlink */
            return(NULL);
        }
        if(node->NEXT == node) { /* only one node */
            node->HEAD = FALSE;  /* not in list anymore */
            return(NULL);
        } else {
            node->NEXT->PREV = node->PREV;
            node->PREV->NEXT = node->NEXT;
            
            if(node->HEAD) {  /* if removing head node */
                node->HEAD = FALSE; /* set new head */
                node->NEXT->HEAD = TRUE;
            }
            return(node->NEXT);
        }
    } else
        return((LIST_TYPE *)NULL);
}

/*
   Remove and free a node from a list and return the following node
   (or NULL if last node).
   You can use:
       while(list) free_node(list);
   to free a simple list.
 */
LIST_TYPE *free_node(node)
LIST_TYPE *node;
{
LIST_TYPE *temp;

    if(node) {
        if( (node->NEXT == NULL) || (node->PREV == NULL) ) {
            /* not a valid list node, can't unlink so just free it */
            free(node);
            return(NULL);
        }
        if(node->NEXT == node) { /* only one node */
            free(node);
            return(NULL);
        } else {
            node->NEXT->PREV = node->PREV;
            node->PREV->NEXT = node->NEXT;
            temp = node->NEXT;   /* save node to return */
            
            if(node->HEAD) {    /* if removing head node */
                node->HEAD = FALSE; /* set new head */
                temp->HEAD = TRUE;
            }
            free(node);
            return(temp);
        }
    } else
        return((LIST_TYPE *)NULL);
}

