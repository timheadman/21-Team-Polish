#ifndef STACK
#define STACK

// ********* CHAR STACK *********
typedef struct char_node
{
    char c;
    struct char_node *ptr;
} char_node;

typedef struct char_head
{
    char_node *ptr;
} char_head;

char_node *new_char_node(char c);
char_head *new_char_head();
void push_char_node(char_head *head, char c);
char_node pull_char_node(char_head *head);
void destroy_char_stack(char_head *head);
int is_empty_char_stack(char_head *head);

// ********* DIGIT STACK *********
typedef struct digit_node
{
    double num;
    struct digit_node *ptr;
} digit_node;

typedef struct digit_head
{
    digit_node *ptr;
} digit_head;

digit_node *new_digit_node(double num);
digit_head *new_digit_head();
void push_digit_node(digit_head *s, double num);
digit_node pull_digit_node(digit_head *s);
void destroy_digit_stack(digit_head *s);
int is_empty_digit_stack(digit_head *s);

#endif
