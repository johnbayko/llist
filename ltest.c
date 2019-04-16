#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"

#define TRUE 1
#define FALSE 0

typedef struct testlist {
        struct testlist LIST_HEAD;
        char            *tstring;
} testlist;

#ifdef OMIT /* standard Xenix/SAS function */
char *strdup(char *instring);

char *strdup(instring)
char *instring;
{
char *newstring;

    if((newstring = (char *)malloc(strlen(instring) + 1)))
        strcpy(newstring,instring);
    return(newstring);
}
#endif

main()
{
char buffer[80];
testlist *list, *node;

    list = NULL;
    for(;;) {
        putchar('>');
        gets(buffer);
        switch(buffer[0]) {
            case 'l':
                if( ((int)(node =
                        (testlist *)head_node((LIST_TYPE *)list)) ) > 0) {
                    /* not NULL */
                    do {
                        if(node == list)
                            putchar('*');
                        else
                            putchar(' ');
                        
                        puts(node->tstring);
                        node = node->NEXT;
                    } while(node->HEAD != TRUE);
                }
                break;
            case 'a':
                node = (testlist *)node_alloc(sizeof(testlist));
                node->tstring = strdup(buffer+1);
                list = (testlist *)insert_node((LIST_TYPE *)list,
                        (LIST_TYPE *)node);
                break;
            case 't':
                node = (testlist *)node_alloc(sizeof(testlist));
                node->tstring = strdup(buffer+1);
                list = (testlist *)add_node((LIST_TYPE *)list,
                        (LIST_TYPE *)node);
                break;
            case 'b':
                node = (testlist *)node_alloc(sizeof(testlist));
                node->tstring = strdup(buffer+1);
                list = (testlist *)append_node((LIST_TYPE *)list,
                        (LIST_TYPE *)node);
                break;
            case 'p':
                puts(list->tstring);
                break;
            case 'd':
		if(list == NULL) {
    		    puts("NULL list\n");
		} else {
                    node = list;
                    list = (testlist *)del_node((LIST_TYPE *)list);
                    if(node) {
                        free(node->tstring);
                        free(node);
                    }
		}
                break;
            case '+':
                list = list->NEXT;
                puts(list->tstring);
                break;
            case '-':
                list = list->PREV;
                puts(list->tstring);
                break;
            case 'q':
                puts("goodbye");
                exit(0);
                break;
            default:
                puts("a[txt] b[txt] t[txt] dlpq+-");
        }
    }
}
