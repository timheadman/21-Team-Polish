#ifndef DJ_H
#define DJ_H

int is_number(char ch);
int priority(char ch);
double calculate(char operation, double a, double b);
char *numberFromDigits(char *origLine, int *position);
char *toPostfix(char *origLine);
double dijkstra(char *postfix_string, double x);

#endif