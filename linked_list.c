#include "common.h"

typedef struct Node_t {
    int data;
    struct Node_t *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

List *list_init(void);
void list_destroy(List *list);
void list_append(List *list, Node *node);
void list_print(List *list);
Node *node_create(int data);
void node_destroy(Node *node);

List *list_init(void)
{
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_destroy(List *list)
{
    Node *current = list->head;
    Node *next = NULL;

    while(current)
    {
        next = current->next;
        node_destroy(current);
        current = next;
    }

    free(list);
}

void list_append(List *list, Node *node)
{
    /* first in list */
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }

    /* end of list */
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

void list_print(List *list)
{
    Node *current = list->head;

    printf("| head | %p |\n", list->head);
    while(current)
    {
        printf("| %p: %d | %p |\n", current, current->data, current->next);
        current = current->next;
    }
    printf("| %p | tail |\n", list->tail);
}

Node *node_create(int data)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->data = data;

    return node;
}

void node_destroy(Node *node) {free(node);}

int main()
{
    List *list = list_init();

    Node *n0 = node_create(0);
    Node *n1 = node_create(1);
    Node *n2 = node_create(2);
    Node *n3 = node_create(3);
    Node *n4 = node_create(4);
    Node *n5 = node_create(5);
    Node *n6 = node_create(6);
    Node *n7 = node_create(7);
    Node *n8 = node_create(8);
    Node *n9 = node_create(9);

    list_append(list, n0);
    list_append(list, n1);
    list_append(list, n2);
    list_append(list, n3);
    list_append(list, n4);
    list_append(list, n5);
    list_append(list, n6);
    list_append(list, n7);
    list_append(list, n8);
    list_append(list, n9);

    list_print(list);
    list_destroy(list);
}