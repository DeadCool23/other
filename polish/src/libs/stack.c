#include "stack.h"

#include "err_code.h"

void init(stack *stack, const char type) {
    stack->size = 0;
    if (type == 'd')
        stack->data = (double *)malloc(0 * sizeof(double));
    else if (type == 'c')
        stack->data = (char *)malloc(0 * sizeof(char));
}

int push(stack *stack, void *element, const char type) {
    if (type == 'd') {
        double *ptr_data = (double *)stack->data;
        ptr_data = realloc(ptr_data, (stack->size + 1) * sizeof(double));
        if (ptr_data == NULL) {
            return ERR_MEM;
        }
        ptr_data[stack->size] = *(double *)element;
        stack->data = ptr_data;
    } else if (type == 'c') {
        char *ptr_data = (char *)stack->data;
        ptr_data = realloc(ptr_data, (stack->size + 1) * sizeof(char));
        if (ptr_data == NULL) {
            return ERR_MEM;
        }
        ptr_data[stack->size] = *(char *)element;
        stack->data = ptr_data;
    }
    stack->size++;
    return OK;
}

void *pop(stack *stack, const char type) {
    if (stack->size <= 0) {
        return NULL;
    }

    void *element = NULL;
    if (type == 'd') {
        double *ptr_data = (double *)stack->data;
        element = malloc(sizeof(double));
        if (element != NULL) {
            *(double *)element = ptr_data[stack->size - 1];
        }
        stack->data = realloc(ptr_data, (stack->size - 1) * sizeof(double));
    } else if (type == 'c') {
        char *ptr_data = (char *)stack->data;
        element = malloc(sizeof(char));
        if (element != NULL) {
            *(char *)element = ptr_data[stack->size - 1];
        }
        stack->data = realloc(ptr_data, (stack->size - 1) * sizeof(char));
    }
    if (element == NULL) {
        return NULL;
    }
    stack->size--;
    return element;
}

void *peek(stack *stack, const char type) {
    void *result = NULL;

    if (stack->size > 0) {
        if (type == 'd') {
            double *ptr_data = (double *)stack->data;
            result = &ptr_data[stack->size - 1];
        } else if (type == 'c') {
            char *ptr_data = (char *)stack->data;
            result = &ptr_data[stack->size - 1];
        }
    }

    return result;
}

void destroy(stack *stack) {
    free(stack->data);
    stack->size = 0;
}