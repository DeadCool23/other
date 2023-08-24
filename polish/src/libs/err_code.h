#ifndef ERR_CODE
#define ERR_CODE

/// @typedef err_t
/// @brief коды ошибок
typedef enum {
    OK, /// Все хорошо
    ERR_IO, /// Ошибка ввода
    ERR_MEM, /// Ошибка выделения памяти
    ERR_SYNTAX, /// Ошибка выражения
} err_t;

/// @typedef math_err_t
/// @brief коды ошибок поиска значений выражений
typedef enum {
    IMAG_NUM = 3, /// Комплексное число
    UNCALCED = 4, /// Несчитаемое выражение
    UNKNOWN_OP = 5, /// Неизвестный оператор
    DIVIZIO_BY_ZERO = 6, /// Деление на ноль
} math_err_t;

#endif  // ERR_CODE