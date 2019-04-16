/*
 * llistmacro.h - macros and types included by llist.h and _llist.h
 *
 * revision 2 
 * - split into llist.h, _llist.h, and llistmacro.h files. llist.h is 
 * for user programs, _llist.h is for library source, and llistmacro.h 
 * is common to both. Strong typing of new C compilers means that 
 * "void **" doesn't work, so has to be replaced with "void *" in user 
 * visible prototypes.
 */

#define LIST_HEAD *NEXT, *PREV; char HEAD

typedef struct LIST_TYPE {
        struct LIST_TYPE LIST_HEAD;
} LIST_TYPE;

#define add_node(list,node)    insert_node(head_node(list),node)
#define add_list(list1, list2) insert_list(head_node(list1),list2)

  /* isnext_node() gives 0 if tail of list */
#define isnext_node(node) ((node && node->NEXT && node->NEXT->HEAD) ? 0 : node->NEXT)
#define next_node(node)   (node ? node->NEXT : 0)
  /* isprev_node() gives 0 if head of list */
#define isprev_node(node) ((node && node->HEAD) ? 0 : node->PREV)
#define prev_node(node)   (node ? node->PREV : 0)

#define is_head(node)     (node ? node->HEAD : 0)
#define is_tail(node)     ((node && node->NEXT) ? node->NEXT->HEAD : 0)

/* compatability macros */
#define create_node(n) node_alloc(n); puts("create_node() use node_alloc()")
