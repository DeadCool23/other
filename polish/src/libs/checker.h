#ifndef CHECKER_H
#define CHECKER_H

/**
 * @brief Функция проверки символа на цифрру
 * 
 * @param [in] num - цифра
 * @return 1 если цифра, иначе 0
 */
int is_digit(const char num);

/**
 * @brief Функция проверки символа на букву
 * 
 * @param [in] letter - буква
 * @return 1 если буква, иначе 0
 */
int is_alpha(const char letter);

/**
 * @brief Функция проверки оператора
 * 
 * @param [in] oper - оператор
 * @return 1 если оператор, иначе 0  
 */
int is_operator(const char oper);

/**
 * @brief Функция проверки на валидность введенной функции
 * 
 * @param [in] func - функция
 * @return 1 если функции, иначе 0 
 */
int is_function(const char *func);

/**
 * @brief Функция проверки кода функции
 * 
 * @param func - код функции
 * @return 1 если код функции, иначе 0 
 */
int is_function_code(const char func);

/**
 * @brief Функция проверки оператора на бинарность
 * 
 * @param [in] operation - оператор
 * @return  1 если оператор бинарный, иначе 0 
 */
int is_binary(const char operation);

/**
 * @brief Функция проверки оператора на унарность
 * 
 * @param [in] operation - оператор
 * @return  1 если оператор унарный, иначе 0 
 */
int is_unary(const char operation);

/**
 * @brief Функция проверки числа
 * 
 * @param [in] num - число в строке
 * @return 1 если число, иначе 0 
 */
int check_num(const char *num);

/**
 * @brief Функция получения приоритета операции
 * 
 * @param [in] c - операция
 * @return Уровень приоритета 
 */
int get_priority(const char c);

#endif  // CHECKER_H