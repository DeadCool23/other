#include "zipper.hpp"

#include "errs.h"
#include "haffman.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>

#if defined(DBG_PRINT)
#include <bitset>
static void print_codes(std::unordered_map<char, std::pair<Storage, std::uint8_t>> &codes) {
    for (auto& tmp : codes) {
        std::cout << "Symbol: " << tmp.first << " Code: ";
        std::bitset<CODE_BITS> __code(tmp.second.first);

        std::cout << __code;

        std::cout << " Size: " << static_cast<int>(tmp.second.second) << std::endl;
    }
}
#endif

static std::size_t symb_counter(std::ifstream &file) {
    std::size_t counter = 0;
    for (char c; file.get(c); counter++);
    file.clear();
    file.seekg(0, std::ios::beg);
    return counter;
}

static void write_meta_info(std::ofstream &file, const std::string filename, const std::size_t symb_cnt, const std::unordered_map<char, std::pair<Storage, std::uint8_t>> &codes) {
#if defined(DBG_PRINT)
    std::cout << std::endl << std::endl << "Writing meta data" << std::endl;
#endif
    std::string file_extention = (filename).substr((filename).find_last_of(".") + 1, (filename).length());
    std::uint8_t extention_size = file_extention.length();

    file.write(reinterpret_cast<char*>(&extention_size), sizeof(extention_size));
    file.write(file_extention.c_str(), sizeof(*(file_extention.c_str())) * extention_size);
    
    file.write(reinterpret_cast<const char*>(&symb_cnt), sizeof(symb_cnt));
    std::uint8_t codes_cnt = codes.size();
    file.write(reinterpret_cast<const char*>(&codes_cnt), sizeof(codes_cnt));
    std::uint8_t codes8b; std::uint16_t codes16b; 
    for (const auto& tmp : codes) {
        file.write(&tmp.first, sizeof(tmp.first));
        file.write(reinterpret_cast<const char*>(&tmp.second.second), sizeof(tmp.second.second));
        if (tmp.second.second <= 8) {
            codes8b = tmp.second.first;
            file.write(reinterpret_cast<const char*>(&codes8b), sizeof(codes8b));
#if defined(DBG_PRINT)
            std::bitset<CHAR_BIT> __code(codes8b);
            std::cout << "Small code: " << __code << " Size: " << (int)tmp.second.second << " Symb: " << tmp.first << std::endl;
#endif
        } else {
            codes16b = tmp.second.first;
            file.write(reinterpret_cast<const char*>(&codes16b), sizeof(codes16b));
#if defined(DBG_PRINT)
            std::bitset<CODE_BITS> __code(codes16b);
            std::cout << "Big code: " << __code << " Size: " << (int)tmp.second.second << " Symb: " << tmp.first << std::endl;
#endif
        }
    }
}

static void write_storage_bytes(std::ofstream &file, Storage wbytes) {
#if defined(DBG_PRINT)
    std::cout << std::endl;
#endif
    std::uint8_t wbyte;
    for (ssize_t i = CODE_BYTES - 1; i >= 0; i--) {
        wbyte = (wbytes >> (CHAR_BIT * i)) & ~(std::uint8_t(0));
        file.write(reinterpret_cast<const char*>(&wbyte), sizeof(wbyte));
#if defined(DBG_PRINT)
        std::bitset<CHAR_BIT> __code(wbyte);
        std::cout << "Writed byte: " << __code << std::endl;
#endif
    }
#if defined(DBG_PRINT)
    std::cout << std::endl;
#endif
}

static void zip_data(std::ofstream &zip_file, std::ifstream &file, std::unordered_map<char, std::pair<Storage, std::uint8_t>> &codes) {
#if defined(DBG_PRINT)
    std::cout << std::endl << "Zipping data" << std::endl;
#endif
    std::uint8_t bits_cnt = 0;
    Storage write_data = 0;
    for (char c; file.get(c); ) {
        auto char_code = codes[c];
#if defined(DBG_PRINT)
        std::bitset<CODE_BITS> __code(write_data);
        std::cout << "Write data: " << __code << " real_bits: " << (int)bits_cnt << std::endl;
        __code = std::bitset<CODE_BITS>(char_code.first);
        std::cout << "New symb: " << c << " Code: " << __code << " Size: " << (int)char_code.second << std::endl;
#endif
        int stepping = CODE_BITS - (bits_cnt + char_code.second);
        Storage new_bits = (stepping < 0 ? char_code.first >> -stepping : char_code.first << stepping);
        write_data = write_data | new_bits;
        std::uint8_t unwrited_bits_cnt = (stepping < 0 ? -stepping : 0);
        bits_cnt = (stepping < 0 ? CODE_BITS : bits_cnt + char_code.second);
#if defined(DBG_PRINT)
        std::cout << "Stepping: " << stepping << " unwritten bits cnt: " << (int)unwrited_bits_cnt << std::endl << std::endl;
#endif        
        if (bits_cnt == CODE_BITS) {
#if defined(DBG_PRINT)
            std::cout << "Opa zapis" << std::endl;
            __code = std::bitset<CODE_BITS>(write_data);
            std::cout << "Writed data: " << __code << " writen bits: " << (int)bits_cnt << std::endl;
#endif        
            write_storage_bytes(zip_file, write_data);
            write_data = bits_cnt = 0;
            if (unwrited_bits_cnt) {
                write_data = write_data | char_code.first << (CODE_BITS - unwrited_bits_cnt);
                bits_cnt += unwrited_bits_cnt;
#if defined(DBG_PRINT)
                std::cout << "Opa unwritted bytes" << std::endl;
                __code = std::bitset<CODE_BITS>(write_data);
                std::cout << "Unwrite data: " << __code << " unwrite_bits: " << (int)bits_cnt << std::endl;
#endif        
            }
        }
    }

    // Дозапись недостающих битов
    if (bits_cnt > 8) {
#if defined(DBG_PRINT)
        std::cout << "Writing last big storage" << std::endl;
        std::bitset<CODE_BITS> __code(write_data);
        std::cout << "Write data: " << __code << " real_bits: " << (int)bits_cnt << std::endl;
#endif
        write_storage_bytes(zip_file, write_data);
    } else if (bits_cnt) {
        std::uint8_t byte = write_data >> CHAR_BIT;
#if defined(DBG_PRINT)
        std::cout << "Writing last small storage" << std::endl;
        std::bitset<CHAR_BIT> __code((char)byte);
        std::cout << "Write data: " << __code << " real_bits: " << (int)bits_cnt << std::endl;
#endif
        zip_file.write(reinterpret_cast<const char*>(&byte), BYTE);
    };
}

int zipper(Options &opts) {
#if defined(DBG_PRINT)
    std::cout << opts.zip.value_or("empty") << std::endl;
    std::cout << opts.name.value_or("empty") << std::endl;
#endif
    errs_t err = OK;
    std::ifstream file(*opts.zip);
    if (!file.is_open()) return err = ERR_FILE;

    HaffmanTree tree = HaffmanTree(file);
    std::size_t symb_cnt = symb_counter(file);
    std::unordered_map<char, std::pair<Storage, std::uint8_t>> codes;

    std::ofstream binfile(*opts.name, std::ios::binary);
    if (!binfile.is_open()) {
        err = ERR_FILE;
        goto error;
    }

    tree.get_codes(codes);

#if defined(DBG_PRINT)
    print_codes(codes);
    std::cout << "File symb cnt: " << symb_cnt << std::endl;
    std::cout << "File uniq symb cnt: " << codes.size() << std::endl;
#endif
    write_meta_info(binfile, *opts.zip, symb_cnt, codes);
    zip_data(binfile, file, codes);

    binfile.close();
    error: file.close();
    if (!err)
        std::cout << "File " << *opts.zip << " zipped in " << *opts.name << " successfully" << std::endl;
    return err;
}
