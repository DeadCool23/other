#include "checker.h"

#include <string.h>

int is_digit(const char num) {
    int digit = num - '0';
    return (digit >= 0 && digit < 10) ? 1 : 0;
}

int is_alpha(const char letter) { return (letter >= 97 && letter <= 122) ? 1 : 0; }

int is_operator(const char oper) {
    int is_oper = 0;
    is_oper |= oper == '+';
    is_oper |= oper == '-';
    is_oper |= oper == '*';
    is_oper |= oper == '/';
    is_oper |= oper == '^';
    return is_oper;
}

int is_function(const char *func) {
    int is_func = 0;
    is_func |= !strcmp(func, "sin");
    is_func |= !strcmp(func, "cos");
    is_func |= !strcmp(func, "tg");
    is_func |= !strcmp(func, "ctg");
    is_func |= !strcmp(func, "ln");
    is_func |= !strcmp(func, "sqrt");
    return is_func;
}

int is_function_code(const char func) {
    int is_func = 0;
    is_func |= func == 's';
    is_func |= func == 'c';
    is_func |= func == 't';
    is_func |= func == 'k';
    is_func |= func == 'q';
    is_func |= func == 'l';
    return is_func;
}

int get_priority(const char c) {
    int result;
    if (c == '+' || c == '-')
        result = 1;
    else if (c == '*' || c == '/' || c == '~')
        result = 2;
    else if (c == '^' || c == 'q')
        result = 3;
    else if (c == 's' || c == 'c' || c == 't' || c == 'k' || c == 'l')
        result = 4;
    else
        result = 0;
    return result;
}

int is_unary(const char operation) {
    int result;
    switch (operation) {
        case 's':
        case 'c':
        case 't':
        case 'k':
        case 'l':
        case 'q':
        case '~':
            result = 1;
            break;
        default:
            result = 0;
    }
    return result;
}

int is_binary(const char operation) {
    int result;
    switch (operation) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            result = 1;
            break;
        default:
            result = 0;
    }
    return result;
}

int check_num(const char *num) {
    int point_cnt = 0;
    for (size_t i = 0; num[i] != '\0'; i++) {
        point_cnt += num[i] == '.' ? 1 : 0;
        if (!is_digit(num[i]) && num[i] != '.') return 0;
    }
    return point_cnt <= 1 ? 1 : 0;
}