#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dj.h"
#include "stack.h"

int is_number(char ch)
{
    return ('0' <= ch && ch <= '9') || (ch == 'x');
}

int priority(char ch)
{
    int result = -1;

    if (ch == '(')
        result = 0;

    if (ch == '+' || ch == '-')
        result = 1;

    if (ch == '*' || ch == '/')
        result = 2;

    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'q' || ch == 'l')
        result = 3;

    if (ch == '~')
        result = 4;

    return result;
}

double calculate(char operation, double a, double b)
{
    double result = 0;

    if (operation == '+')
    {
        result = a + b;
    }
    else if (operation == '-')
    {
        result = a - b;
    }
    else if (operation == '*')
    {
        result = a * b;
    }
    else if (operation == '/')
    {
        result = a / b;
    }
    else if (operation == 's')
    {
        result = sin(b);
    }
    else if (operation == 'c')
    {
        result = cos(b);
    }
    else if (operation == 't')
    {
        result = tan(b);
    }
    else if (operation == 'g')
    {
        result = cos(b) / sin(b);
    }
    else if (operation == 'q')
    {
        result = sqrt(b);
    }
    else if (operation == 'l')
    {
        result = log(b);
    }

    return result;
}

char *get_string_number(char *expr, int *pos)
{
    char *str_number = NULL;
    int size = 0;

    for (; *pos < (int)strlen(expr); (*pos)++)
    {
        char num = expr[*pos];
        if (is_number(num) || num == '.')
        {
            size++;

            char *temp = (char *)realloc(str_number, sizeof(char) * size);
            if (temp != NULL)
                str_number = temp;

            str_number[size - 1] = num;
        }
        else
        {
            (*pos)--;
            break;
        }
    }

    char *temp = (char *)realloc(str_number, sizeof(char) * ++size);

    if (temp != NULL)
        str_number = temp;
    if (str_number)
        str_number[size - 1] = '\0';

    return str_number;
}

char *to_postfix(char *input_string)
{
    char *postfix_expr = malloc(strlen(input_string) * sizeof(char) * 2);
    int n = 0;
    char_head *head = new_char_head();

    for (int i = 0; i < (int)strlen(input_string); i++)
    {
        char c = input_string[i];

        if (is_number(c))
        {
            char *temp = get_string_number(input_string, &i);

            for (int j = 0; j < (int)strlen(temp); j++)
            {
                postfix_expr[n] = temp[j];
                n++;
            }

            postfix_expr[n] = ' ';
            n++;
            free(temp);
        }
        else if (c == '(')
        {
            push_char_node(head, '(');
        }
        else if (c == ')')
        {
            while (!is_empty_char_stack(head) && head->ptr->c != '(')
            {
                postfix_expr[n] = pull_char_node(head).c;
                n++;
                postfix_expr[n] = ' ';
                n++;
            }
            pull_char_node(head);
        }
        else if (priority(c) != -1)
        {
            char op = c;

            if (op == '-' && (i == 0 || (i > 1 && priority(input_string[i - 1]) != -1)))
                op = '~';

            while (!is_empty_char_stack(head) && priority(head->ptr->c) >= priority(op))
            {
                postfix_expr[n] = pull_char_node(head).c;
                n++;
                postfix_expr[n] = ' ';
                n++;
            }

            if (op == 'c' && input_string[i + 1] == 'o')
                push_char_node(head, 'c');
            else if (op == 'c' && input_string[i + 1] == 't')
                push_char_node(head, 'g');
            else if (op == 's' && input_string[i + 1] == 'q')
                push_char_node(head, 'q');
            else if (op == 'l')
                push_char_node(head, 'l');
            else
                push_char_node(head, op);

            if ((op == 's' && input_string[i + 1] == 'i') || op == 'c' || op == 't' || op == 'g')
                i += 2;
            else if (op == 's' && input_string[i + 1] == 'q')
                i += 3;
            else if (op == 'l')
                i += 1;
        }
    }

    while (!is_empty_char_stack(head))
    {
        postfix_expr[n] = pull_char_node(head).c;
        n++;
    }

    destroy_char_stack(head);

    return postfix_expr;
}

double dijkstra(char *postfix_string, double x)
{
    digit_head *d = new_digit_head();
    int counter = 0;

    for (int i = 0; i < (int)strlen(postfix_string); i++)
    {
        char c = postfix_string[i];

        if (is_number(c))
        {
            if (c != 'x')
            {
                char *str_number = get_string_number(postfix_string, &i);
                char *ptr;
                double num = strtod(str_number, &ptr);

                push_digit_node(d, num);
                free(str_number);
            }
            else
            {
                push_digit_node(d, x);
            }
        }
        else if (priority(c) != -1)
        {
            counter += 1;
            if (c == '~')
            {
                double last;
                if (is_empty_digit_stack(d))
                    last = 0;
                else
                    last = pull_digit_node(d).num;

                push_digit_node(d, calculate('-', 0, last));

                continue;
            }

            double second;
            if (is_empty_digit_stack(d))
                second = 0;
            else
                second = pull_digit_node(d).num;

            double first;
            if (is_empty_digit_stack(d))
                first = 0;
            else if (c != 's' && c != 'c' && c != 't' && c != 'g' && c != 'l')
                first = pull_digit_node(d).num;
            else
                first = 0;

            push_digit_node(d, calculate(c, first, second));
        }
    }

    double result = pull_digit_node(d).num;
    destroy_digit_stack(d);
    return result;
}
