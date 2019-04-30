/*
 * A linked list library
 * llist.c - basic node functions (create, add, delete, etc.)
 *
 * revision 1
 * - I decided to add a revision number, so I know which version is the
 * most recent (and hopefully, bug-free).
 */

#include <stdbool.h>
#include "_llist.h"    /* contains the real prototypes for llist.c */

/*
    Initializes a node to be a list (return value can be ignored)
    No NULL check.
 */
LIST_TYPE *create_list(LIST_TYPE * const node)
{
    node->NEXT = node->PREV = node; /* link node to self */
    node->HEAD = true;
    return(node);
}

/*
    Initialize a node to be not in a list.
    No NULL check.
 */
LIST_TYPE *init_node(LIST_TYPE * const node)
{
    node->NEXT = node->PREV = NULL;
    node->HEAD = false;
    return(node);
}

/*
    Allocate a node and clear all node information so it's not mistaken for a
    llist.
 */
LIST_TYPE *node_alloc(const size_t size)
{
    LIST_TYPE * const node = malloc(size);
    if (NULL != node) {
        init_node(node);
    }
    return node;
}

/*
 * Find the head of the list by travelling back to the beginning.
 * If the node is not in a list, head_node calls create_list and returns
 * the node.
 * If HEAD is not set anywhere, head_node returns node.
 * If node is NULL, returns NULL.
 */
LIST_TYPE *head_node(LIST_TYPE * const node)
{
    LIST_TYPE *temp, *mark;

    if (NULL == node) {
        // Does not exist.
        return (NULL);
    }
    if (NULL == node->NEXT) {
        create_list(node);  /* node not in list, make one */
        return (node);       /* it's now the head */
    }
    /* node is linked to a list */
    /* scan_list() scans forward, this scans backwards on the theory that if
       the code is interested in the head, the node it keeps track of is
       probably pretty close, so it's faster that way. */
    for (LIST_TYPE * scan = node;;scan = scan->PREV) {
        if (scan->HEAD) {
            return scan;
        }
        if (node == scan->PREV) {
            return node;
        }
    }
    // Shouldn't get here.
    return (node);
}

/* Find the tail of the list (prev of head_node() ) */
LIST_TYPE *tail_node(LIST_TYPE * const list)
{
    LIST_TYPE * const node = head_node(list);
    if (NULL == node) {
        return NULL;
    }
    return (node->PREV);
}

/*
 * Add a node to a list - return new node, reset HEAD if needed.
 */
LIST_TYPE *insert_node(LIST_TYPE * const list, LIST_TYPE * const node)
{
    LIST_TYPE * const temp = _insert_node(list,node);
    if (temp->NEXT->HEAD) {
        temp->NEXT->HEAD = false;
        temp->HEAD = true;
    }
    return(temp);
}

/*
 * Insert a node within a list without checking HEAD.
 */
LIST_TYPE *_insert_node(LIST_TYPE * const list, LIST_TYPE * const node)
{
    if (NULL == list) {
        /* no list, create list from node */
        return create_list(node);
    }
    if ( (NULL == list->NEXT) || (NULL == list->PREV) ) {
        /* not a list - initialise it */
        /* if caused by program error, may drop nodes */
        create_list(list);
    }
    node->HEAD = false;
    node->NEXT = list;
    node->PREV = list->PREV;
    list->PREV->NEXT = node;
    list->PREV = node;
    return (node);        /* new head of list */
}

/*
   Link node to list tail, return list pointer (even if it's not the
   list head), or node if list is NULL. In other words, you can use
   "list = append_node(list, node)" any time.
 */
LIST_TYPE *append_node(LIST_TYPE * const list, LIST_TYPE * const node)
{
    _insert_node(head_node(list), node);
    return (NULL != list) ? list : node;
}

/*
   Remove a node from a list and return the following node.
   node is not deallocated, and must be kept track of by the
   program.
   You can use something like:
       while(list) { node=del_node(list); free(node); }
   to free a list.
 */
LIST_TYPE *del_node(LIST_TYPE * const node)
{
    if (NULL == node) {
        return(NULL);
    }
    if ( (NULL == node->NEXT) || (NULL == node->PREV) ) {
        /* not a valid list node, can't unlink */
        return(NULL);
    }
    if (node->NEXT == node) {
        /* only one node */
        init_node(node);  /* not in list anymore */
        return(NULL);
    }
    node->NEXT->PREV = node->PREV;
    node->PREV->NEXT = node->NEXT;

    LIST_TYPE * const remaining_list = node->NEXT;
    if (node->HEAD) {
        /* removing head node, set new head */
        remaining_list->HEAD = true;
    }
    init_node(node);  /* not in list anymore */
    return remaining_list;
}

/*
   Remove and free a node from a list and return the following node
   (or NULL if last node).
   You can use:
       while(list) list = free_node(list);
   to free a simple list.
 */
LIST_TYPE *free_node(LIST_TYPE * const node)
{
    if (NULL == node) {
        return (NULL);
    }
    LIST_TYPE * remaining_list = del_node(node);
    free(node);
    return remaining_list;
}

