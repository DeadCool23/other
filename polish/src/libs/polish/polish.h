#ifndef POLISH_H
#define POLISH_H

#include <stddef.h>

/// @def ALLOCATE_NEW_STR_DYN
/// Макрос выделения памяти в матице под динамический буфер
#define ALLOCATE_NEW_STR_DYN(matrix, str_len, ind_add, added_dyn)            \
    do {                                                                     \
        matrix = (char **)realloc((matrix), (ind_add + 1) * sizeof(char *)); \
        if (matrix == NULL) {                                                \
            free(added_dyn);                                                 \
            return ERR_MEM;                                                  \
        }                                                                    \
        (matrix)[ind_add] = (char *)calloc(str_len, sizeof(char));           \
        if ((matrix)[ind_add] == NULL) {                                     \
            free(added_dyn);                                                 \
            return ERR_MEM;                                                  \
        }                                                                    \
    } while (0)

/// @def ALLOCATE_NEW_STR
/// Макрос выделения памяти в матице под статический буфер
#define ALLOCATE_NEW_STR(matrix, str_len, ind_add)                           \
    do {                                                                     \
        matrix = (char **)realloc((matrix), (ind_add + 1) * sizeof(char *)); \
        if (matrix == NULL) {                                                \
            return ERR_MEM;                                                  \
        }                                                                    \
        (matrix)[ind_add] = (char *)calloc(str_len, sizeof(char));           \
        if ((matrix)[ind_add] == NULL) {                                     \
            return ERR_MEM;                                                  \
        }                                                                    \
    } while (0)

/**
 * @brief Функция разделения строки на токены
 * 
 * @param [in] str - строка выражения
 * @param [out] parser - матрица токенов выражения 
 * @return Код ошибки
 */
int str_parser(char *str, char ***parser);

/**
 * @brief Функция превращения выражения в польскую нотацию
 * 
 * @param [in] parse_str - матрица токенов выражения
 * @param [out] polish - Польская нотация
 * @return Код ошибки
 */
int to_polish_note(char **parse_str, char ***polish);

/**
 * @brief Функция подсчета значения польской нотации
 * 
 * @param [in] polish_note - польская нотация 
 * @param [out] err - ошибка
 * @param [in] to_x - значение x
 * @return полученное значения 
 */
double polish_calc(char **polish_note, int *err, double to_x);

/**
 * @brief Освобождение выделенной памяти
 * 
 * @param [in] data - очищаемые данные
 */
void free_data(char **data);

#endif  // POLISH_H