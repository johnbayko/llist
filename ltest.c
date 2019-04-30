#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"

typedef struct testlist {
        struct testlist LIST_HEAD;
        char            *tstring;
} testlist;

static bool _print_nodes(void * node)
{
    testlist * const test_node = (testlist *)node;
    putchar(' ');
    puts(test_node->tstring);
    return false;
}

void in_loop(
    char ** in_line,
    size_t * in_line_size
) {
    testlist *list = NULL;

    for (;;) {
        putchar('>');
        ssize_t const in_line_len = getline(in_line, in_line_size, stdin);
        switch (*in_line[0]) {
        case 'l':
        {
            testlist * node = head_node(list);
            if (NULL != node) {
                do {
                    if (node == list) {
                        putchar('*');
                    } else {
                        putchar(' ');
                    }
                    puts(node->tstring);
                    node = node->NEXT;
                } while(node->HEAD != true);
            }
            break;
        }
        case 's':
            (void)scan_list(head_node(list), _print_nodes);
            break;
        case 'a':
        {
            testlist * const node = node_alloc(sizeof(testlist));
            node->tstring = strdup(*in_line+1);
            list = insert_node(list, node);
            break;
        }
        case 't':
        {
            testlist * const node = node_alloc(sizeof(testlist));
            node->tstring = strdup(*in_line+1);
            list = add_node(list, node);
            break;
        }
        case 'b':
        {
            testlist * const node = node_alloc(sizeof(testlist));
            node->tstring = strdup(*in_line+1);
            list = append_node(list, node);
            break;
        }
        case 'p':
            if (NULL == list) {
                puts("NULL list\n");
            } else {
                puts(list->tstring);
            }
            break;
        case 'd':
            if (NULL == list) {
                puts("NULL list\n");
            } else {
                testlist * const node = list;
                list = del_node(list);
                if (NULL != node) {
                    free(node->tstring);
                    free(node);
                }
            }
            break;
        case '+':
            if (NULL == list) {
                puts("NULL list\n");
            } else {
                list = list->NEXT;
                puts(list->tstring);
            }
            break;
        case '-':
            if (NULL == list) {
                puts("NULL list\n");
            } else {
                list = list->PREV;
                puts(list->tstring);
            }
            break;
        case 'q':
            // TODO: List should be freed.
            while (NULL != list) {
                list = free_node(list);
            }
            puts("goodbye");
            return;
        case '?':
            puts(
                "[a]dd txt\n"
                "[b]ottom txt\n"
                "[t]op txt\n"
                "[d]el current\n"
                "[l]ist\n"
                "[p]rint current\n"
                "[s]can print all\n"
                "[+] next\n"
                "[-] previous.\n"
                "[?] help.\n"
                "[q]uit"
            );
            // Fall through.
        default:
            puts("a[txt] b[txt] t[txt] dlps+-?q");
        }
    }
}

int main(const int argc, const char * const argv[])
{
    char * in_line;
    size_t in_line_size = 0;

    in_loop(&in_line, &in_line_size);

    free(in_line);
    exit(EXIT_SUCCESS);
}
