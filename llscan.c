/*
 * A linked list library
 * llscan.c - routines to scan or search a list
 *
 * revision 1
 * - I decided to add a revision number, so I know which version is the
 * most recent (and hopefully, bug-free).
 */

#include <stdbool.h>
#include "_llist.h"

/*
   Apply a function to each node of a list, until the function
   returns true or the end of the list is reached.
   scan_list() returns node that was true, or NULL
   if the scan reached the end first.
*/
LIST_TYPE *scan_list(
    LIST_TYPE * const list,
    bool (*func)(LIST_TYPE *)
) {
    if (NULL == list) {
        return NULL;
    }
    for (LIST_TYPE * listscan = list;;listscan = listscan->NEXT) {
        if ( (*func)(listscan) ) {
            return (listscan);
        }
        if (list == listscan->NEXT) {
            return NULL;
        }
    }
    // shouldn't get here
    return NULL;
}
