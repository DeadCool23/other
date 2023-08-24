#ifndef FUNCTION_H
#define FUNCTION_H

/// @def SYMB_LEN
/// размер строки состоящей из одного символа
#define SYMB_LEN 2

/**
 * @brief Функция поиска значений бинарных операций 
 * 
 * @param [in] oper - операция
 * @param [in] num1 - первое число
 * @param [in] num2 - второе число
 * @param [out] err - ошибка
 * @return получившееся значение 
 */
double count_binary(const char oper, const double num1, const double num2, int *err);

/**
 * @brief Функция поиска значений унарных операций 
 * 
 * @param [in] oper - операция
 * @param [in] num - число
 * @param [out] err - ошибка
 * @return получившееся значение 
 */
double count_unary(const char oper, const double num1, int *err);

/**
 * @brief Функция превращения функции в заданный код
 * 
 * @param [in] func - Функция
 * @param [out] code - код функции
 * @return Код функции 
 */
char *function_to_code(const char *func, char *code);

#endif  // FUNCTION_H