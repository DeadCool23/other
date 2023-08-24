#include "polish.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../checker.h"
#include "../err_code.h"
#include "../functions.h"
#include "../input.h"
#include "../stack.h"

static int add_number(char ***parser, size_t *pos, int *iter, char *num_str) {
    char *number = NULL;
    int numberIndex = 0;

    while (is_digit(num_str[*iter]) || num_str[*iter] == '.') {
        char *temp = (char *)realloc(number, (numberIndex + 1) * sizeof(char));
        if (temp == NULL) {
            free(number);
            return ERR_MEM;
        }
        number = temp;
        number[numberIndex++] = num_str[(*iter)++];
    }
    number[numberIndex] = '\0';

    ALLOCATE_NEW_STR_DYN(*parser, strlen(number) + 1, *pos, number);
    strcpy((*parser)[*pos], number);
    (*pos)++;
    free(number);
    (*iter)--;
    return OK;
}

static int extract_token(char *str, int *index, char **token) {
    int tokenIndex = 0;
    char *tempToken = NULL;

    while (is_alpha(str[*index])) {
        tempToken = (char *)realloc(tempToken, (tokenIndex + 1) * sizeof(char));
        if (tempToken == NULL) {
            free(tempToken);
            return ERR_MEM;
        }
        tempToken[tokenIndex++] = str[(*index)++];
    }
    tempToken[tokenIndex] = '\0';
    *token = tempToken;

    return OK;
}

int str_parser(char *str, char ***parser) {
    int strLength = strlen(str);
    size_t parserIndex = 0;

    *parser = (char **)calloc(0, sizeof(char *));
    if (*parser == NULL) return ERR_MEM;
    for (int i = 0; i < strLength; i++) {
        if (str[i] == ' ') continue;
        if (is_digit(str[i])) {
            int err = add_number(parser, &parserIndex, &i, str);
            if (err != OK) return err;
        } else if (is_alpha(str[i])) {
            char *token = NULL;
            int err = extract_token(str, &i, &token);
            if (err != OK) {
                free(token);
                return err;
            }
            if (is_function(token)) {
                ALLOCATE_NEW_STR_DYN(*parser, SYMB_LEN, parserIndex, token);
                char code[SYMB_LEN];
                strcpy((*parser)[parserIndex], function_to_code(token, code));
            } else if (!strcmp(token, "x")) {
                ALLOCATE_NEW_STR(*parser, SYMB_LEN, parserIndex);
                *parser = (char **)realloc((*parser), (parserIndex + 1) * sizeof(char *));
                strcpy((*parser)[parserIndex], token);
            } else {
                free(token);
                return ERR_IO;
            }
            parserIndex++;
            free(token);
            i--;
        } else if (is_operator(str[i])) {
            ALLOCATE_NEW_STR(*parser, SYMB_LEN, parserIndex);
            strncpy((*parser)[parserIndex], &str[i], 2);
            (*parser)[parserIndex++][1] = '\0';
        } else if (str[i] == '(') {
            ALLOCATE_NEW_STR(*parser, SYMB_LEN, parserIndex);
            strcpy((*parser)[parserIndex++], "(");
        } else if (str[i] == ')') {
            ALLOCATE_NEW_STR(*parser, SYMB_LEN, parserIndex);
            strcpy((*parser)[parserIndex++], ")");
        }
    }
    *parser = (char **)realloc((*parser), (parserIndex + 1) * sizeof(char *));
    (*parser)[parserIndex] = NULL;
    return OK;
}

int to_polish_note(char **parse_str, char ***polish) {
    stack st;
    char type = 'c';
    init(&st, type);
    *polish = malloc(0 * sizeof(char *));
    int polishIndex = 0;

    for (int i = 0; parse_str[i] != NULL; i++) {
        if (is_digit(parse_str[i][0]) || strcmp(parse_str[i], "x") == 0) {
            ALLOCATE_NEW_STR(*polish, strlen(parse_str[i]) + 1, polishIndex);
            strcpy((*polish)[polishIndex], parse_str[i]);
            polishIndex++;
        } else if (is_function_code(parse_str[i][0]) || strcmp(parse_str[i], "(") == 0) {
            push(&st, (void *)&parse_str[i][0], type);
        } else if (strcmp(parse_str[i], ")") == 0) {
            while (st.size != 0 && *(char *)peek(&st, type) != '(') {
                ALLOCATE_NEW_STR(*polish, SYMB_LEN, polishIndex);
                (*polish)[polishIndex][0] = *(char *)pop(&st, type);
                (*polish)[polishIndex][1] = '\0';
                polishIndex++;
            }
            if (st.size == 0) return ERR_SYNTAX;
            pop(&st, type);
        } else if (strcmp(parse_str[i], "-") == 0) {
            while (st.size != 0 && get_priority(*(char *)peek(&st, type)) >= get_priority('~')) {
                ALLOCATE_NEW_STR(*polish, SYMB_LEN, polishIndex);
                (*polish)[polishIndex][0] = *(char *)pop(&st, type);
                (*polish)[polishIndex][1] = '\0';
                polishIndex++;
            }
            push(&st, (void *)"~", type);
        } else if (is_operator(parse_str[i][0])) {
            while (st.size != 0 && get_priority(*(char *)peek(&st, type)) >= get_priority(parse_str[i][0])) {
                ALLOCATE_NEW_STR(*polish, SYMB_LEN, polishIndex);
                (*polish)[polishIndex][0] = *(char *)pop(&st, type);
                (*polish)[polishIndex][1] = '\0';
                polishIndex++;
            }
            push(&st, (void *)&parse_str[i][0], type);
        }
    }

    while (st.size != 0) {
        if (*(char *)peek(&st, type) == '(') return ERR_SYNTAX;
        ALLOCATE_NEW_STR(*polish, SYMB_LEN, polishIndex);
        (*polish)[polishIndex][0] = *(char *)pop(&st, type);
        (*polish)[polishIndex][1] = '\0';
        polishIndex++;
    }

    *polish = (char **)realloc(*polish, (polishIndex + 1) * sizeof(char *));
    (*polish)[polishIndex] = NULL;

    return OK;
}

double polish_calc(char **polish_not, int *err, double to_x) {
    stack st;
    char type = 'd';
    init(&st, type);
    double num1, num2, result = -1;
    char curr;
    int i = 0;
    for (i = 0; (polish_not[i] != NULL) && (*err == OK); i++) {
        curr = polish_not[i][0];
        int is_x = !strcmp(polish_not[i], "x");
        if (is_digit(curr) || is_x) {
            // If first character in line num -> push it into stack
            char *str_num = (char *)calloc(strlen(polish_not[i]) + 1, sizeof(char));
            strcpy(str_num, polish_not[i]);
            double num = is_x ? to_x : check_num(str_num) ? atof(str_num) : -1;
            if (num != -1 || check_num(str_num)) {
                push(&st, (void *)&num, type);
                result = num;
            } else
                *err = ERR_IO;
            free(str_num);
        } else if (is_unary(curr)) {
            // If it's unary operator - take one number and make operation
            num1 = *(double *)pop(&st, type);
            result = count_unary(curr, num1, err);
            push(&st, (void *)&result, type);
        } else if (is_binary(curr)) {
            // If it's binary operator, take two numbers and make operation
            num2 = *(double *)pop(&st, type);
            num1 = *(double *)pop(&st, type);
            printf("%lf %lf", num1, num2);
            result = count_binary(curr, num1, num2, err);
            push(&st, (void *)&result, type);
        } else {
            *err = UNKNOWN_OP;
        }
    }
    if ((polish_not[i] != NULL) && (st.size != 1)) {
        *err = UNCALCED;
    }
    destroy(&st);
    return result;
}

void free_data(char **data) {
    for (int i = 0; data[i] != NULL; i++) free(data[i]);
    free(data);
}
