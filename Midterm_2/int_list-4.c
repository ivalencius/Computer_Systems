/*
 * Program to build and represent a linked list of integers.
 *
 * Author: Ilan Valencius - valencig@bc.edu
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define USAGE "Please enter one of the following commands:\n" \
    "\ta <int> -- add <int> to the end of the list\n" \
    "\ti <int> <index> -- insert <int> at position <index>\n" \
    "\ti <int> <index> -- insert <int> at position <index>\n" \
    "\tr <index> -- remove element from position <index>\n" \
    "\tq -- quit.\n"

typedef struct Node {
    int value;
    struct Node * next;
} Node;

typedef struct List {
    Node * head;
    int length;
} List;

/*
 * Returns a Node object allocated on the heap.
 */
Node * make_node(int value) {
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

/*
 * Allocates a new List object on the stack.
 */
List make_list() {
    List new_list;
    new_list.head = NULL;
    new_list.length = 0;
    return new_list;
}

/*
 * Adds a new element with the given value to the end of the list.
 */
void add_element(List * list, int value) {
    Node * new_node = make_node(value);
    if (! list->head) {
        list->head = new_node;
    } else {
        Node * current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    ++list->length;
}

/*
 * Inserts a new element into the list with the given value at the position given by index.
 * If the index reaches beyond the end of the list, appends the new element to the end.
 */
void insert_element(List * list, int value, int index) {
    // If the index is nonsensical, just ignore it.
    if (index < 0) {
        return;
    }
    if (index >= list->length) {
        add_element(list, value);
        return;
    }
    Node * new_node = make_node(value);
    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        Node * current = list->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node * rest = current->next;
        current->next = new_node;
        new_node->next = rest;
    }
    ++list->length;
}

/*
* Removes an element from the list specified at list index
*/
void remove_element(List * list, int index) {
    // If the index is nonsensical, just ignore it.
    if ((index < 0)) {
        printf("Invalid Index\n");
        return;
    }
    // Remove last item
    else if ((index >= list->length)) {
        Node * current = list->head;
        // Stop at second to last element
         for (int i = 0; i < list->length - 2; ++i) {
            current = current->next;
        }
        Node* removable = current-> next;
        current->next = NULL;
        free(removable);
    }
    // Index 0
    else if (index == 0) {
        Node* removable = list->head;
        list->head = list->head->next;
        free(removable);
    }
    // Index 
    else {
        Node * current = list->head;
        int index_counter = 0;
        // Stop 1 before index
        while (index_counter != index-1) {
            current = current-> next;
            index_counter++;
        }
        Node* removable = current-> next;
        current->next = current->next->next;
        free(removable);
    }
    // Decrement list length
    --list->length;
}

/*
 * Prints a visualization of the list.
 */
void print_list(List * list) {
    Node * current = list->head;
    while (current) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("null\n");
    printf("\tList Length: %d\n",list->length);
}

/*
 * De-allocates heap memory allocated for the Node objects in the list.
 */
void free_list(List * list) {
    Node * head = list->head;
    Node * current;
    while (head) {
        current = head;
        head = head->next;
        free(current);
    }
    list->head = NULL;
    list->length = 0;
}

/*
 * Takes user input to build and manipulate the list and print the results.
 */
int main(int argc, char * argv[]) {
    char c;
    int value;
    int index;
    List list = make_list();
    printf(USAGE);
    printf("> ");
    while (scanf("%c", &c) != EOF) {
        if (c == 'q') {
            while (getchar() != (int)'\n');
            break;
        }
        switch (c) {
            case 'a':
                scanf("%d", &value);
                add_element(&list, value);
                print_list(&list);
                break;
            case 'i':
                scanf("%d %d", &value, &index);
                insert_element(&list, value, index);
                print_list(&list);
                break;
            case 'r':
                scanf("%d", &index);
                remove_element(&list,index);
                print_list(&list);
                break;
            default:
                break;
        }
        while (getchar() != (int)'\n');
        printf("> ");
    }
    free_list(&list);
    return EXIT_SUCCESS;
}
