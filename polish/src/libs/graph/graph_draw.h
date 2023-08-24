#ifndef GRAPH_DRAW_H
#define GRAPH_DRAW_H

/**
 * @def WIDTH
 * ширина поля 
 */
#define WIDTH 80
/**
 * @def HEIGHT
 * высота поля 
 */
#define HEIGHT 25

/**
 * @brief Процедура инициализации поля графика
 * 
 * @param [out] graph - поле графика
 */
void graph_init(char graph[][WIDTH]);

/**
 * @brief Функция отрисовки графика по выражению
 * 
 * @param [out] graph - поле графика
 * @param [in] polish - выражение в виде обратной польской нотации 
 * @return Код ошибки 
 */
int graph_draw(char graph[][WIDTH], char **polish);

/**
 * @brief Процедура вывода графика
 * 
 * @param [in] graph - поле графика
 */
void graph_print(char graph[][WIDTH]);

#endif  // GRAPH_DRAW_H