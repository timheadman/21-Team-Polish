#ifndef DJ_H
#define DJ_H

int is_number(char ch);
int priority(char ch);
double calculate(char operation, double a, double b);
char *get_string_number(char *expr, int *pos);
char *to_postfix(char *input_string);
double dijkstra(char *postfix_string, double x);

#endif