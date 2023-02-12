#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dj.h"
#include "stack.h"

char *get_stdin();
int check_string(char *expression);
void fill(int *screen, char *postfix_expr);
void draw(const int *array);

int main() {
    char *input_string = NULL;
    input_string = get_stdin();

    if (input_string != NULL && !check_string(input_string)) {
        int *screen = NULL;
        char *postfix_string = toPostfix(input_string);

        fill(screen, postfix_string);

        free(postfix_string);
    } else {
        printf("n/a");
    }

    free(input_string);

    return 0;
}

char *get_stdin() {
    char *buffer = NULL;
    size_t buffer_size = 0;
    int c;
    int error_flag = 0;

    while ((c = fgetc(stdin)) != 10 && c != -1) {
        if (!error_flag) {
            buffer_size++;
            char *temp = realloc(buffer, buffer_size);
            if (temp == NULL) {
                free(buffer);
                error_flag = 1;
            }
            buffer = temp;
        }

        if (error_flag) break;

        buffer[buffer_size - 1] = c;
    }

    return buffer;
}

int check_string(char *input_string) {
    int error_flag = 0;
    char *alpha = "sincotargqlx()+-*/.0123456789 ";
    for (int i = 0; i < (int)strlen(input_string); i++) {
        if (strchr(alpha, input_string[i]) == NULL) {
            error_flag = 1;
            break;
        }
    }
    return error_flag;
}

void draw(const int *array) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) array[j] == i ? printf("*") : printf(".");
        printf("\n");
    }
}

void fill(int *screen, char *postfix_string) {
    screen = malloc(sizeof(int) * 80);
    if (screen != NULL) {
        for (int i = 0; i < 80; i++)
            screen[i] = round(12 * dijkstra(postfix_string, (4 * M_PI / 79) * i) + 12);
        draw(screen);
    }
    free(screen);
}
