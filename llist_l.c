/*
 * A linked list library
 * llist_l.c - list functions (insert/append one list in/to another)
 *
 * revision 1
 * - I decided to add a revision number, so I know which version is the
 * most recent (and hopefully, bug-free).
 */
#include "_llist.h"

#define TRUE 1
#define FALSE 0
#define NULL 0

/*
 * Insert list2 within list1 without changing HEAD of either.
 * HEAD must be adjusted by calling function. For this reason,
 * _ins_list() is not visible outside this file.
 */
static LIST_TYPE *_ins_list(LIST_TYPE *list1, LIST_TYPE *list2);
static LIST_TYPE *_ins_list(list1, list2)
LIST_TYPE *list1, *list2;
{
LIST_TYPE *temp;

    if(list2 == NULL) {
        /* return list 1 */
        if( (list1 != NULL) &&
            ((list1->NEXT == NULL) || (list1->PREV == NULL)) ) {
            /* not a valid list - initialise it */
            /* if caused by program error, may drop nodes */
            create_list(list1);
        }
        return(list1);
    }
    if(list1 == NULL) {
        /* return list 2 */
        if( (list2 != NULL) &&
            ((list2->NEXT == NULL) || (list2->PREV == NULL)) ) {
            /* not a valid list - initialise it */
            /* if caused by program error, may drop nodes */
            create_list(list2);
        }
        return(list2);
    }
    /* neither list is null */
    /* make sure both are valid lists */
    if( (list1->NEXT == NULL) || (list1->PREV == NULL) ) {
        /* not a valid list - initialise it */
        /* if caused by program error, may drop nodes */
        create_list(list1);
    }
    if( (list2->NEXT == NULL) || (list2->PREV == NULL) ) {
        /* not a valid list - initialise it */
        /* if caused by program error, may drop nodes */
        create_list(list2);
    }
    /* insert list2 into list1 before list1 pointer */
    temp = list2->PREV;
    list2->PREV->NEXT = list1;
    list2->PREV = list1->PREV;
    list1->PREV->NEXT = list2;
    list1->PREV = temp;
    return(list1);
}

/*
 * Insert list2 in list1 - return new list, reset HEAD if needed.
 */
LIST_TYPE *insert_list(list1,list2)
LIST_TYPE *list1, *list2;
{
LIST_TYPE *temp;

    list2 = head_node(list2);
    temp = _ins_list(list1, list2);
    if( (list1 != NULL) && (list2 != NULL) ) {
        if(list1->HEAD) {
            list1->HEAD = FALSE;
            return(list2);
        } else {
            list2->HEAD = FALSE;
            return(list1);
        }
    }
    return(temp);
}

/*
 * Append list2 to list1 - return new list, HEAD.
 */
LIST_TYPE *append_list(list1, list2)
LIST_TYPE *list1, *list2;
{
LIST_TYPE *temp;

    list1 = head_node(list1);
    list2 = head_node(list2);
    if( (temp = _ins_list(list1, list2)) != NULL) {
        if( (list1 != NULL) && (list2 != NULL) ) {
            list2->HEAD = FALSE;
        }
    }
    return(temp);
}

