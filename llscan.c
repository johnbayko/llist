/*
 * A linked list library
 * llscan.c - routines to scan or search a list
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
   Apply a function to each node of a list, until the function
   returns TRUE or the end of the list is reached.
   scan_list() returns node that was true, or NULL
   if the scan reached the end first.
*/
LIST_TYPE *scan_list(list, func)
LIST_TYPE *list;
int       (*func)(LIST_TYPE *);
{
LIST_TYPE *listscan;

    if(list) {
        listscan = list;
        do {
            if( (*func)(listscan) ) {
                return(listscan);
            }
            listscan = listscan->NEXT;
        } while(listscan->HEAD == FALSE);
    }
    return( (LIST_TYPE *)NULL );
}
