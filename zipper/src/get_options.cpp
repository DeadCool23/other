#include "get_options.hpp"

#include <iostream>
#include <getopt.h>
#include <unistd.h>

Options::Options(int argc, char* argv[], int *correct_opts) {
    *correct_opts = 1;
    zip = std::nullopt;
    name = std::nullopt;
    unzip = std::nullopt;
    const char options[] = "o:u:z:h";
    const struct option long_options[] = {
        {"name", required_argument, 0, 'o'},
        {"unzip", required_argument, 0, 'u'},
        {"zip", required_argument, 0, 'z'},
        {"help", no_argument, 0, 'h'},
        {nullptr, 0, nullptr, 0}
    };

    int c;
    int option_index = 0;

    while ((c = getopt_long(argc, argv, options, long_options, &option_index)) != -1) {
        switch (c) {
            case 'o':
                if (name) goto error;
                name = optarg;
                break;
            case 'u':
                if (unzip) goto error;
                unzip = optarg;
                break;
            case 'z':
                if (zip) goto error;
                zip = optarg;
                break;
            case 'h':
                help = true;
                return;
            case '?':
                goto error;
                return;
            default:
                std::cout << "ERROR: Incorrect options" << std::endl;
                goto error;
                return;
        }
    }

    // Проверка что нет архивации и разархивации одновременно
    // Проверка на так что есть что архивировать и разархивировать в случае если не требуется помощь
    if ((zip && unzip) || (!zip && !unzip && !help)) {
        std::cout << "ERROR: " << ((zip && unzip) ? "Can't zip and unzip together" : "Nothing given to (un)zip") << std::endl;
        error: *correct_opts = 0;
    } else if (zip) {
        this->get_zipped_name();
        if ((*name).substr((*name).find_last_of(".")) != ".nzip") {
            std::cout << "ERROR: Incorrect FILENAME for zip file(FILENAME=*.nzip)" << std::endl;
            *correct_opts = 0;
        }
    }

    // Проверка на то что файл не архивируется сам в себя
    if (zip.value_or("empty") == *name || unzip.value_or("empty") == *name) {
        std::cout << "ERROR: Can't zip file into itself" << std::endl;
        *correct_opts = 0;
    }
}

void Options::get_unzipped_name(const std::string extention) {
    if (this->name) return;
    this->name = (*this->unzip).substr(0, (*this->unzip).find_last_of('.')) + "." + extention;
}
void Options::get_zipped_name(void) {
    if (this->name) return;
    this->name = (*this->zip).substr(0, (*this->zip).find_last_of('.')) + ".nzip";
}

void Options::helper(char *app_name) {
    std::cout << "Usage: " << app_name << " [OPTION]... [FILE]..." << std::endl;
    std::cout << "Archivate text FILE" << std::endl << std::endl;
    std::cout << "With no FILE, utility don't work" << std::endl;
    std::cout << "FILENAME of zipped file <*.nzip>" << std::endl << std::endl;
    std::cout << "-z, --zip=FILE                       FILE to zipping" << std::endl;
    std::cout << "-u, --unzip=FILE                     FILE to unzipping" << std::endl;
    std::cout << "-o, --name=FILENAME                  FILENAME for (un)zipped FILE" << std::endl;
    std::cout << std::endl << "-h, --help                           display this help and exit" << std::endl;
}