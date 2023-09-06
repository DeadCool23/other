#include <stdio.h>

// Возвраты из игры
#define WIN 0
#define EXIT 1

// Ошибки ввлда
#define OK 0
#define ERR_CHAR 1
#define BUF_OVERFLOW 2

// Поля
#define WEIGHT 80
#define HEIGHT 25

// Максимальное кол-во очков
#define SCORE 21

// Начальные координаты мяча
#define BALL_START_X (WEIGHT / 2)
#define BALL_START_Y (HEIGHT / 2)

// Началаьная позиция ракеток
#define START_PLAYER (HEIGHT / 2)

#define ROCKET_LIMIT_Y_UP (HEIGHT - 3)
#define ROCKET_LIMIT_Y_DOWN 2

#define LEFT_PLAYER_X 1
#define RIGHT_PLAYER_X (WEIGHT - 2)

// Отрисовка счета
void score(int left, int right);
// Отрисовка всего поля
void GraphDraw(int, int, int, int, int, int, int);

// Проверка победы
_Bool is_win(int right_score, int left_player);
// Вывод победителя
void winner_print(int right_score, int left_score);
// Проверка отбития
_Bool is_rep(int player_pos, int ball_pos);

/// @brief Функция работы игры
/// @return Признак возврата
int game(int, int, int, int, int, int, int, int);

// Проверка буфера ввода
int check_buf(void);
// Очистка буфера
void clean_buf(void);

int main(void) {
    int ball_y = BALL_START_Y;
    int ball_x = BALL_START_X;

    int left_player = START_PLAYER;
    int right_player = START_PLAYER;

    int left_score = 0;
    int right_score = 0;

    int vec_x = 1;
    int vec_y = 1;

    int end = game(ball_x, ball_y, left_score, right_score, left_player, right_player, vec_x, vec_y);
    return end;
}

int game(int ball_x, int ball_y, int left_score, int right_score, int left_player, int right_player,
         int vec_x, int vec_y) {
    int err = OK;
    for (;;) {
        if (is_win(right_score, left_score)) {
            winner_print(right_score, left_score);
            return WIN;
        }
        printf("\033[2J"); // очистка терминала
        GraphDraw(ball_x, ball_y, left_score, right_score, left_player, right_player, err);  // Отрисовка
        // Проверка введенной команды
        char button = getchar();
        if (button == '\n') {
            continue;
        }
        err = check_buf();
        if (err != OK) {
            continue;
        }
        if (button == 'z')
            left_player += left_player == ROCKET_LIMIT_Y_UP ? 0 : 1;
        else if (button == 'a')
            left_player -= left_player == ROCKET_LIMIT_Y_DOWN ? 0 : 1;
        else if (button == 'k')
            right_player -= right_player == ROCKET_LIMIT_Y_DOWN ? 0 : 1;
        else if (button == 'm')
            right_player += right_player == ROCKET_LIMIT_Y_UP ? 0 : 1;
        else if (button == ' ')
            ;
        else if (button == 'q')
            return EXIT;
        else {
            err = ERR_CHAR;
            continue;
        }

        vec_y = (ball_y == HEIGHT - 2 || ball_y == 1) ? -vec_y : vec_y;
        vec_x = ((ball_x == WEIGHT - 3 || ball_x == 2) &&
                 (is_rep(left_player, ball_y) || is_rep(right_player, ball_y)))
                    ? -vec_x
                    : vec_x;
        ball_x += vec_x;
        ball_y += vec_y;
        if (ball_x == WEIGHT - 2 || ball_x == 1) {
            ball_x == 1 ? ++right_score : ++left_score;
            ball_y = BALL_START_Y;
            ball_x = BALL_START_X;

            left_player = START_PLAYER;
            right_player = START_PLAYER;
        }
    }
}

void GraphDraw(int ball_x, int ball_y, int left_score, int right_score, int left_player, int right_player,
               int err) {
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WEIGHT; x++) {
            if ((x == 0 || x == WEIGHT - 1) && (y == 0 || y == HEIGHT - 1))
                printf("+");
            else if (y == 0 || y == HEIGHT - 1)
                printf("-");
            else if (ball_y == y && ball_x == x)
                printf("o");
            else if (y == 1 && x == WEIGHT / 2 - 3) {
                score(left_score, right_score);
                x += 6;
            } else if (x == LEFT_PLAYER_X &&
                       (y == left_player - 1 || y == left_player + 1 || y == left_player))
                printf("|");
            else if (x == RIGHT_PLAYER_X &&
                     (y == right_player - 1 || y == right_player + 1 || y == right_player))
                printf("|");
            else if (x == 0 || x == WEIGHT - 1 || x == WEIGHT / 2)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
    if (err == OK)
        printf(":");
    else if (err == ERR_CHAR)
        printf("ERROR: incorrect buttom. Try again: ");
    else if (err == BUF_OVERFLOW)
        printf("ERROR: too much acts. Try again: ");
}

void score(int left, int right) { printf("%02d | %02d", left, right); }

_Bool is_rep(int player_pos, int ball_pos) {
    return (ball_pos == player_pos - 1 || ball_pos == player_pos + 1 || ball_pos == player_pos);
}

_Bool is_win(int score1, int score2) { return (score1 == SCORE || score2 == SCORE) ? 1 : 0; }

int check_buf(void) {
    if (getchar() == '\n') return OK;
    clean_buf();
    return BUF_OVERFLOW;
}

void clean_buf(void) {
    while (getchar() != '\n')
        ;
}

void winner_print(int right_score, int left_score) {
    left_score > right_score ? printf(
                                   "\
 ____  _                         _            _ \n\
|  _ \\| | __ _ _   _  ___ _ __  / | __      _(_)_ __ \n\
| |_) | |/ _` | | | |/ _ \\ '__| | | \\ \\ /\\ / / | '_ \\ \n\
|  __/| | (_| | |_| |  __/ |    | |  \\ V  V /| | | | | \n\
|_|   |_|\\__,_|\\__, |\\___|_|    |_|   \\_/\\_/ |_|_| |_| \n\
               |___/                                  \n")
                             : printf(
                                   "\
 ____  _                         ____             _ \n\
|  _ \\| | __ _ _   _  ___ _ __  |___ \\  __      _(_)_ __ \n\
| |_) | |/ _` | | | |/ _ \\ '__|   __) | \\ \\ /\\ / / | '_ \\ \n\
|  __/| | (_| | |_| |  __/ |     / __/   \\ V  V /| | | | | \n\
|_|   |_|\\__,_|\\__, |\\___|_|    |_____|   \\_/\\_/ |_|_| |_| \n\
               |___/                                      \n");
}
