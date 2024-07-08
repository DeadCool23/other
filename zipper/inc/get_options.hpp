#ifndef __GET_OPTIONS_HPP__
#define __GET_OPTIONS_HPP__

#include <string>
#include <optional>

/* Аргументы приложения */

struct Options {
    bool help = false;                 // Помощь в использовании
    std::optional<std::string> zip;    // Имя архивируемого файла
    std::optional<std::string> name;   // Имя для файла (раз)архивации
    std::optional<std::string> unzip;  // Имя файла разархивации

    // Получение и обработка переданных аргументов
    explicit Options(int argc, char* argv[], int *correct_opts);
    // Вывод сообщения помощи
    void helper(char *app_name);
    // Получение имени файла разархивации (Если оно не передано)
    void get_unzipped_name(const std::string extention);
private:
    void get_zipped_name(void);   // Получение имени файла архивации (Если оно не передано)
};

#endif // __GET_OPTIONS_HPP__
