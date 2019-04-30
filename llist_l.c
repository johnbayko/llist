/*
 * A linked list library
 * llist_l.c - list functions (insert/append one list in/to another)
 *
 * revision 1
 * - I decided to add a revision number, so I know which version is the
 * most recent (and hopefully, bug-free).
 */
#include <stdbool.h>
#include "_llist.h"

/*
 * Insert list2 within list1 without changing HEAD of either.
 * HEAD must be adjusted by calling function. For this reason,
 * _ins_list() is not visible outside this file.
 */
static LIST_TYPE *_ins_list(LIST_TYPE * const list1, LIST_TYPE * const list2)
{
    if ( (NULL != list1)
      && ( (NULL == list1->NEXT) || (NULL == list1->PREV) )
    ) {
        /* not a valid list - initialise it */
        /* if caused by program error, may drop nodes */
        create_list(list1);
    }
    if ( (list2 != NULL)
      && ( (list2->NEXT == NULL) || (list2->PREV == NULL) )
    ) {
        /* not a valid list - initialise it */
        /* if caused by program error, may drop nodes */
        create_list(list2);
    }
    if (NULL == list2) {
        /* return list 1 */
        return(list1);
    }
    if(list1 == NULL) {
        /* return list 2 */
        return(list2);
    }
    /* neither list is null */
    /* insert list2 into list1 before list1 pointer */
    LIST_TYPE * const temp = list2->PREV;
    list2->PREV->NEXT = list1;
    list2->PREV = list1->PREV;
    list1->PREV->NEXT = list2;
    list1->PREV = temp;
    return(list1);
}

/*
 * Insert list2 in list1 - return new list, reset HEAD if needed.
 */
LIST_TYPE *insert_list(LIST_TYPE * const list1, LIST_TYPE * const list2)
{
    LIST_TYPE * const list_head2 = head_node(list2);
    LIST_TYPE * const new_list = _ins_list(list1, list_head2);
    if( (list1 != NULL) && (list_head2 != NULL) ) {
        if (list1->HEAD) {
            // Replacing list1 head, list2 head becomes the new one.
            list1->HEAD = false;
            return (list_head2);
        } else {
            // Only list1 head can stay.
            list_head2->HEAD = false;
            return (list1);
        }
    }
    return (new_list);
}

/*
 * Append list2 to list1 - return new list, HEAD.
 */
LIST_TYPE *append_list(LIST_TYPE * const list1, LIST_TYPE * const list2)
{
    LIST_TYPE * const list_head1 = head_node(list1);
    LIST_TYPE * const list_head2 = head_node(list2);
    LIST_TYPE * const new_list = _ins_list(list_head1, list_head2);
    if (NULL != new_list) {
        if ( (NULL != list_head1) && (NULL != list_head2) ) {
            list_head2->HEAD = false;
        }
    }
    return(new_list);
}

