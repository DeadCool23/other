#include "unzipper.hpp"

#include <vector>
#include <climits>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "errs.h"
#include "haffman.hpp"

#if defined(DBG_PRINT)
#include <bitset>
#endif

static std::pair<std::vector<char>, std::vector<std::pair<Storage, std::uint8_t>>> get_meta_data(std::ifstream &zip_file, std::size_t *file_size, Options &opts) {
    std::uint8_t ex_size;
    zip_file.read(reinterpret_cast<char *>(&ex_size), sizeof(ex_size));
    char *ex_filename = new char[ex_size + 1]; ex_filename[ex_size] = '\0';
    zip_file.read(ex_filename, sizeof(*ex_filename) * ex_size);
#if defined(DBG_PRINT)
    std::cout << "Extention: " << ex_filename << " Extention size: " << (int)ex_size << std::endl;
#endif
    std::string extention = ex_filename;
    opts.get_unzipped_name(extention);
    delete[] ex_filename;
    
    std::uint8_t symbs_cnt;
    zip_file.read(reinterpret_cast<char *>(file_size), sizeof(*file_size));
    zip_file.read(reinterpret_cast<char *>(&symbs_cnt), sizeof(symbs_cnt));

    std::vector<char> symbols(symbs_cnt);
    std::vector<std::pair<Storage, std::uint8_t>> symbols_codes(symbs_cnt);

#if defined(DBG_PRINT)
    std::cout << "File size: " << *file_size << " Symbols cnt: " << (std::size_t)symbs_cnt << std::endl ;
#endif
    for (std::size_t i = 0; i < symbs_cnt; i++) {
        zip_file.read(reinterpret_cast<char *>(&symbols[i]), sizeof(symbols[i]));
        zip_file.read(reinterpret_cast<char *>(&symbols_codes[i].second), sizeof(symbols_codes[i].second));
        zip_file.read(reinterpret_cast<char *>(&symbols_codes[i].first), symbols_codes[i].second <= 8 ? BYTE : CODE_BYTES);
#if defined(DBG_PRINT)
        std::bitset<CODE_BITS> __code((char)symbols_codes[i].first);
        std::cout << (symbols_codes[i].second <= 8 ? "Small " : "Big ") << "Code: " << __code << " Size: " << (int)symbols_codes[i].second << " Symb: " << symbols[i] << std::endl;
#endif
    }
    return std::pair(symbols, symbols_codes);
}

void unzip_data(std::ofstream &unzip_file, std::ifstream &zip_file, std::size_t file_size, std::pair<std::vector<char>, std::vector<std::pair<Storage, std::uint8_t>>> &codes) {
    auto symbols = codes.first;
    auto symbols_codes = codes.second;

    std::size_t symbols_cnt = symbols.size();
    auto symb_code = std::pair(Storage(0), std::uint8_t(0));
    for (std::size_t i = 0; i < file_size; i += symbols_cnt == 1 ? 1 : 0) {
        if (symbols_cnt == 1) {
            unzip_file.put(symbols[0]);
        } else {
            std::byte readed_byte = std::byte(0);
            zip_file.read(reinterpret_cast<char *>(&readed_byte), BYTE);
#if defined(DBG_PRINT)
            std::bitset<CHAR_BIT> __code((char)readed_byte);
            std::cout << "Readed byte: " << __code << std::endl << std::endl;
#endif
            for (ssize_t j = CHAR_BIT - 1; j >= 0 && i < file_size; j--) {
                std::byte bit = std::byte((char)readed_byte >> j & 1);
                symb_code.first = (symb_code.first << 1) | (char)bit; symb_code.second++;
#if defined(DBG_PRINT)
                __code = (char)bit;
                std::cout << "Readed bit: " << __code << std::endl;
                __code = (char)symb_code.first;
                std::cout << "Tmp code: " << __code << " Tmp size: " << (int)symb_code.second << std::endl;
#endif
                auto is_symbol_exist = std::find(symbols_codes.begin(), symbols_codes.end(), symb_code);
                if (is_symbol_exist != symbols_codes.end()) {
                    unzip_file.put(symbols[std::distance(symbols_codes.begin(), is_symbol_exist)]);
#if defined(DBG_PRINT)
                    std::cout << std::endl << "Finded symbol: " << symbols[std::distance(symbols_codes.begin(), is_symbol_exist)] << std::endl << std::endl;
#endif
                    symb_code = std::pair(Storage(0), 0);
                    i++;
                }
            }
        }
    }
}

int unzipper(Options &opts) {
#if defined(DBG_PRINT)
    std::cout << opts.unzip.value_or("empty") << std::endl;
    std::cout << opts.name.value_or("empty") << std::endl;
#endif
    errs_t err = OK;
    std::size_t file_size;
    std::ifstream zip_file(*opts.unzip, std::ios::binary);
    if (!zip_file.is_open()) return err = ERR_FILE;

    auto codes = get_meta_data(zip_file, &file_size, opts);

    std::ofstream unzip_file(*opts.name);
    if (!unzip_file.is_open()) {
        err = ERR_FILE;
        goto error;
    };

    unzip_data(unzip_file, zip_file, file_size, codes);

    unzip_file.close();
    error:
    zip_file.close();

    if (!err)
        std::cout << "File " << *opts.unzip << " unzipped in " << *opts.name << " successfully" << std::endl;
    return err;
}
