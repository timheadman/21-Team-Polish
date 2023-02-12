#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// ********* CHAR STACK *********
char_node *new_char_node(char c)
{
    char_node *n;
    n = (char_node *)malloc(sizeof(char_node));
    n->c = c;
    n->ptr = NULL;
    return n;
}

char_head *new_char_head()
{
    char_head *head;
    head = (char_head *)malloc(sizeof(char_head));
    head->ptr = NULL;
    return head;
}

void push_char_node(char_head *head, char c)
{
    char_node *n = new_char_node(c);
    n->ptr = head->ptr;
    head->ptr = n;
}

char_node pull_char_node(char_head *head)
{
    char_node n = {0, NULL};

    if (head->ptr != NULL)
    {
        char_node *aux;
        aux = head->ptr;
        head->ptr = head->ptr->ptr;
        n = *aux;
        free(aux);
    }

    return n;
}

void destroy_char_stack(char_head *node)
{
    while (node->ptr != NULL)
    {
        pull_char_node(node);
    }
    free(node);
}

int is_empty_char_stack(char_head *node)
{
    return node->ptr == NULL;
}

// ********* DIGIT STACK *********
digit_node *new_digit_node(double num)
{
    digit_node *n;
    n = (digit_node *)malloc(sizeof(digit_node));
    n->num = num;
    n->ptr = NULL;
    return n;
}

digit_head *new_digit_head()
{
    digit_head *head;
    head = (digit_head *)malloc(sizeof(digit_head));
    head->ptr = NULL;
    return head;
}

void push_digit_node(digit_head *head, double num)
{
    digit_node *n = new_digit_node(num);
    n->ptr = head->ptr;
    head->ptr = n;
}

digit_node pull_digit_node(digit_head *head)
{
    digit_node n = {0, NULL};

    if (head->ptr != NULL)
    {
        digit_node *tmp;
        tmp = head->ptr;
        head->ptr = head->ptr->ptr;
        n = *tmp;
        free(tmp);
    }

    return n;
}

void destroy_digit_stack(digit_head *node)
{
    while (node->ptr != NULL)
    {
        pull_digit_node(node);
    }
    free(node);
}

int is_empty_digit_stack(digit_head *node)
{
    return node->ptr == NULL;
}
