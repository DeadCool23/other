#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

/// @typedef stack - стэк
/// @brief Стек может хранить в себе типы char и double
typedef struct {
    void *data;
    size_t size;
} stack;

/**
 * @brief Процедура инициализации стэка
 * 
 * @param [out] stack - стэк
 * @param [in] type - тип хранящийся в стэке 
 */
void init(stack *stack, const char type);

/**
 * @brief Функция кладет элемент на вершину стэка
 * 
 * @param [in, out] stack - стэк
 * @param [in] element - элемент
 * @param [in] type - тип хранящийся в стэке 
 * @return Код ошибки 
 */
int push(stack *stack, void *element, const char type);

/**
 * @brief Функция просмотра вершины стэка
 * 
 * @param [in, out] stack - стэк
 * @param [in] type - тип хранящийся в стэке 
 * @return вершина стэка
 */
void *peek(stack *stack, const char type);

/**
 * @brief Функция удаляет и возвращает вершину стэка
 * 
 * @param [in, out] stack - стэк
 * @param [in] type - тип хранящийся в стэке 
 * @return вершина стэка
 */
void *pop(stack *stack, const char type);

/**
 * @brief Процедура очиски памяти стэка
 * 
 * @param [in] stack - стэк
 */
void destroy(stack *stack);

#endif  // STACK_H