#include "functions.h"

#include <math.h>
#include <string.h>

#include "checker.h"
#include "err_code.h"

double count_unary(const char oper, const double num1, int *err) {
    double result = -1;
    switch (oper) {
        case 's':
            result = sin(num1);
            break;
        case 'c':
            result = cos(num1);
            break;
        case 't':
            if (cos(num1) != 0)
                result = tan(num1);
            else
                *err = DIVIZIO_BY_ZERO;
            break;
        case 'k':
            if (sin(num1) != 0)
                result = 1. / tan(num1);
            else
                *err = DIVIZIO_BY_ZERO;

            break;
        case 'q':
            if (num1 >= 0)
                result = sqrt(num1);
            else
                *err = IMAG_NUM;
            break;
        case 'l':
            if (num1 > 0)
                result = log(num1);
            else
                *err = UNCALCED;
            break;
        case '~':
            result = -num1;
            break;
    }
    return result;
}

double count_binary(char oper, double num1, double num2, int *err) {
    double result = -1;
    switch (oper) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else
                *err = DIVIZIO_BY_ZERO;
            break;
        case '^':
            result = pow(num1, num2);
            break;
    }
    return result;
}

char *function_to_code(const char *func, char *code) {
    if (!strcmp(func, "cos"))
        strcpy(code, "c");
    else if (!strcmp(func, "sin"))
        strcpy(code, "s");
    else if (!strcmp(func, "tg"))
        strcpy(code, "t");
    else if (!strcmp(func, "ctg"))
        strcpy(code, "k");
    else if (!strcmp(func, "ln"))
        strcpy(code, "l");
    else if (!strcmp(func, "sqrt"))
        strcpy(code, "q");
    return code;
}
