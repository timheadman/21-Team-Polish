#include "dj.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int is_number(char ch) { return ('0' <= ch && ch <= '9') || (ch == 'x'); }

int priority(char ch) {
    int result = -1;

    if (ch == '(') result = 0;
    if (ch == '+' || ch == '-') result = 1;
    if (ch == '*' || ch == '/') result = 2;
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'q' || ch == 'l') result = 3;
    if (ch == '~') result = 4;

    return result;
}

double calculate(char operation, double a, double b) {
    double result = 0;

    if (operation == '+') {
        result = a + b;
    } else if (operation == '-') {
        result = a - b;
    } else if (operation == '*') {
        result = a * b;
    } else if (operation == '/') {
        result = a / b;
    } else if (operation == 's') {
        result = sin(b);
    } else if (operation == 'c') {
        result = cos(b);
    } else if (operation == 't') {
        result = tan(b);
    } else if (operation == 'g') {
        result = cos(b) / sin(b);
    } else if (operation == 'q') {
        result = sqrt(b);
    } else if (operation == 'l') {
        result = log(b);
    }

    return result;
}

// Getting number with lots of digits from string
//"c(123.45)+blabla" => "123.45"
// Tested!
char *numberFromDigits(char *origLine, int *position) {
    char *finalNumber = NULL;
    int size = 0;

    for (; *position < (int)strlen(origLine); (*position)++) {
        char num = origLine[*position];
        if (is_number(num) || num == '.') {
            size++;

            char *temp = (char *)realloc(finalNumber, sizeof(char) * size);
            // TODO - work with leaks and right "free" functions in
            // main functions
            if (temp != NULL) finalNumber = temp;

            finalNumber[size - 1] = num;
        } else {
            (*position)--;
            break;
        }
    }

    char *temp = (char *)realloc(finalNumber, sizeof(char) * ++size);
    // FREE FROM LEAKS IN MAIN!!!

    if (temp != NULL) finalNumber = temp;
    if (finalNumber) finalNumber[size - 1] = '\0';

    return finalNumber;
}

char *toPostfix(char *origLine) {
    char *finalLine = malloc(strlen(origLine) * sizeof(char) * 2);
    int n = 0;
    char_head *head = new_char_head();

    for (int i = 0; i < (int)strlen(origLine); i++) {
        char c = origLine[i];  // current symbol

        // Possible cases:

        // 1) Symbol is a digit => then grab all
        // IDEA: Number until not digit(or 'x') to
        // the final output

        // 2) Symbol is an opening bracket, then
        // IDEA: Push it to the stack

        // 3) Symbol is a closing bracket
        // IDEA: While head of the stack is not
        // an opening bracket - from stack to the
        // final line!

        // 4) Symbol stands for operation
        // IDEA: some operations need 2 arguments
        // like '+', '-' and etc,
        // some needs only one like cos, sin and etc
        if (is_number(c)) {  // Case 1
            char *temp = numberFromDigits(origLine, &i);

            for (int j = 0; j < (int)strlen(temp); j++) {
                finalLine[n] = temp[j];
                n++;
            }

            finalLine[n] = ' ';
            n++;
            free(temp);
        } else if (c == '(') {  // Case 2
            push_char_node(head, '(');
        } else if (c == ')') {  // Case 3
            while (!is_empty_char_stack(head) && head->ptr->c != '(') {
                finalLine[n] = pull_char_node(head).c;
                n++;
                finalLine[n] = ' ';
                n++;
            }
            pull_char_node(head);
        } else if (priority(c) != -1) {  // case 4
            char op = c;

            // If minus => check if it is suppose to change sign of the operand(unary).
            // If it is, than change it for tilda to distinguish it from binary minus
            if (op == '-' && (i == 0 || (i > 1 && priority(origLine[i - 1]) != -1))) op = '~';

            // While priority of the opeartion at the head is above or equal to
            // the priority of our current operation => push head to final line
            while (!is_empty_char_stack(head) && priority(head->ptr->c) >= priority(op)) {
                finalLine[n] = pull_char_node(head).c;
                n++;
                finalLine[n] = ' ';
                n++;
            }

            // Push operation to the stack with corrsponding letter
            // And make shift for needed number of letters
            // Example : 1+3 for "sqrt", 1+1 for "ln"
            if (op == 'c' && origLine[i + 1] == 'o')
                push_char_node(head, 'c');
            else if (op == 'c' && origLine[i + 1] == 't')
                push_char_node(head, 'g');
            else if (op == 's' && origLine[i + 1] == 'q')
                push_char_node(head, 'q');
            else if (op == 'l')
                push_char_node(head, 'l');
            else  // sin and tan now are unique based on their first letter
                push_char_node(head, op);

            // Shift for "for" cycle
            if ((op == 's' && origLine[i + 1] == 'i') || op == 'c' || op == 't' || op == 'g')
                i += 2;
            else if (op == 's' && origLine[i + 1] == 'q')
                i += 3;
            else if (op == 'l')
                i += 1;
        }
    }

    // Push all stack to the final line
    while (!is_empty_char_stack(head)) {
        finalLine[n] = pull_char_node(head).c;
        n++;
    }

    // Clear stack
    destroy_char_stack(head);

    return finalLine;
}
double dijkstra(char *postfix_string, double x) {
    digit_head *d = new_digit_head();
    int counter = 0;

    for (int i = 0; i < (int)strlen(postfix_string); i++) {
        char c = postfix_string[i];

        if (is_number(c)) {
            if (c != 'x') {
                char *str_number = numberFromDigits(postfix_string, &i);
                char *ptr;
                double num = strtod(str_number, &ptr);

                push_digit_node(d, num);
                free(str_number);
            } else {
                push_digit_node(d, x);
            }
        } else if (priority(c) != -1) {
            counter += 1;
            if (c == '~') {
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
