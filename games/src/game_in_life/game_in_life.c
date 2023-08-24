#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// Размер поля
#define WIDTH 80
#define HEIGHT 25

// Состояние жизни на поле
#define ALIVE 0
#define DETH 1

// Коды продолжения игры
#define EXIT 0
#define CNT 1

// Коды ошибки
#define OKK 0
#define ERR_RANGE 2

// Задержки
#define DELAY 100000
#define DELAY_STEP (DELAY / 10)
#define DELAY_MAX 400000

#define INPUT_PROMT "Enter coordinates of living cells\n(if you want to stop input write \"end\")\n"

/* Работа с полем */
// Обновление поля
void updateGrid(int grid[][WIDTH]);
// Проверка поля на наличие жизни
_Bool checkGrid(int grid[][WIDTH], int *generation);
// Вывод поля
void printGrid(int grid[][WIDTH], long long speed, int generation);

/* Обработка кнопок */
int checkButton(char button, long long *speed);

/* Функция подсчета живых клеток */
int countAlive(int grid[][WIDTH]);

/* Игра */
int gameInLive(int grid[][WIDTH]);

/* Подсчет соседей */
int countNeighbours(int grid[][WIDTH], int row, int col);

/* Считывание вводимых координат */
int setInitialPattern(int grid[][WIDTH]);

/* Вывод сообщения об окончании */
void exitMessage(int ext);

int main(void) {
    int grid[HEIGHT][WIDTH] = {0};

    int err = setInitialPattern(grid);
    if (err != OKK) {
        if (err == ERR_RANGE) printf("ERROR: Incorrect coordinate\n");
        return err;
    }

    initscr();
    noecho();
    cbreak();
    halfdelay(0);
    nodelay(stdscr, TRUE);
    curs_set(0);

    int end = gameInLive(grid);

    clear();
    echo();
    endwin();

    exitMessage(end);

    return end;
}

int gameInLive(int grid[][WIDTH]) {
    int generation = 1;
    long long speed = DELAY;
    while (true) {
        clear();

        printGrid(grid, speed, generation);

        refresh();
        char button = '0';
        if (freopen("/dev/tty", "r", stdin)) button = getch();
        if (!checkButton(button, &speed)) return EXIT;
        if (checkGrid(grid, &generation)) return DETH;
        updateGrid(grid);

        usleep(speed);
    }
}

int checkButton(char button, long long *speed) {
    switch (button) {
        case 'x':
            *speed += *speed < DELAY_MAX ? DELAY_STEP : 0;
            break;
        case 'z':
            *speed -= *speed > DELAY_STEP ? DELAY_STEP : 0;
            break;
        case 'q':
            return EXIT;
    }
    return CNT;
}

void printGrid(int grid[][WIDTH], long long speed, int generation) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printw(grid[i][j] ? "@" : "`");
        }
        printw("\n");
    }
    printw("Delay: %-6lld ms \t Generation: %03d \t Alive: %d / %d\n", speed, generation, countAlive(grid),
           HEIGHT * WIDTH);
}

int countAlive(int grid[][WIDTH]) {
    int count = 0;
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) count += grid[i][j] ? 1 : 0;
    return count;
}

int countNeighbours(int grid[][WIDTH], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = (row + i + HEIGHT) % HEIGHT;
            int nj = (col + j + WIDTH) % WIDTH;
            count += grid[ni][nj];
        }
    }
    return count;
}

void updateGrid(int grid[][WIDTH]) {
    int newGrid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbours = countNeighbours(grid, i, j);
            if (grid[i][j]) {
                newGrid[i][j] = (neighbours < 2 || neighbours > 3) ? 0 : 1;
            } else {
                newGrid[i][j] = (neighbours == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int setInitialPattern(int grid[][WIDTH]) {
    int x, y;
    printf(INPUT_PROMT);
    while (fscanf(stdin, "%d %d", &x, &y) == 2) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            grid[y][x] = 1;
        } else {
            return ERR_RANGE;
        }
    }
    return OKK;
}

_Bool checkGrid(int grid[][WIDTH], int *generation) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (grid[i][j] == 1) {
                ++(*generation);
                return ALIVE;
            }
    return DETH;
}

void exitMessage(int ext) {
    if (ext == EXIT)
        printf(
            "\
 ____  _  _  ____  ____ \n\
( ___)( \\/ )(_  _)(_  _) \n\
 )__)  )  (  _)(_   )( \n\
(____)(_/\\_)(____) (__) \n");
    else if (ext == DETH)
        printf(
            "\
 __    ____  ____  ____    ____  ___    _____  _  _  ____  ____ \n\
(  )  (_  _)( ___)( ___)  (_  _)/ __)  (  _  )( \\/ )( ___)(  _ \\ \n\
 )(__  _)(_  )__)  )__)    _)(_ \\__ \\   )(_)(  \\  /  )__)  )   / \n\
(____)(____)(__)  (____)  (____)(___/  (_____)  \\/  (____)(_)\\_) \n");
}
