#ifndef __HAFFMAN_HPP__
#define __HAFFMAN_HPP__

#include <array>
#include <memory>
#include <cstdint>
#include <fstream>
#include <optional>
#include <charconv>
#include <unordered_map>

#include "priority_queue.hpp"

#if defined(DBG_PRINT)
#include <bitset>
#include <iostream>
#endif

#define BYTE 1
#define CODE_BYTES 2
#define CODE_BITS CODE_BYTES * CHAR_BIT

#if 0 > CODE_BITS || CODE_BITS > 64
#error "Too big storage"
#endif

#define STORAGE_TYPE(code_bits) \
    std::conditional_t<(code_bits <= 8), std::uint8_t, \
    std::conditional_t<(code_bits <= 16), std::uint16_t, \
    std::conditional_t<(code_bits <= 32), std::uint32_t, \
    std::conditional_t<(code_bits <= 64), std::uint64_t, void>>>>

// Создание синонима хранилищу кодов
#define BITS_STORAGE(code_bits) using Storage = STORAGE_TYPE(code_bits);

BITS_STORAGE(CODE_BITS)

/* Дерево Хаффмана */

template <typename T=char>
class HaffmanTree {
    // Структура узла бинарного дерева
    struct Tree {
        std::optional<T> data;
        std::shared_ptr<Tree> left;
        std::shared_ptr<Tree> right;

        explicit Tree(void) : data(std::nullopt), left(nullptr), right(nullptr) {}
        explicit Tree(T el) : data(std::optional(el)), left(nullptr), right(nullptr) {}
    };
    std::shared_ptr<Tree> root; // Указатель на корень дерева

public:
    /* Конструкторы */
    explicit HaffmanTree(std::ifstream &file); // Конструктор на основе файла
    HaffmanTree(const std::unordered_map<T, std::size_t>& data); // Конструктор на основе словаря

    // Получение кодов
    void get_codes(std::unordered_map<T, std::pair<Storage, std::uint8_t>> &codes) const;
private:
    // Получение приоритетов сиволов на основе очереди приоритетов
    std::unordered_map<T, std::size_t> get_prioreties(std::ifstream &file) const;
    // Обход дерева Хаффмана с целью получения кодов символов
    void codes_traversal(std::shared_ptr<Tree> node, std::uint8_t size, Storage code, std::unordered_map<T, std::pair<Storage, std::uint8_t>> &codes) const;
};


template <typename T>
HaffmanTree<T>::HaffmanTree(const std::unordered_map<T, std::size_t>& data) {
    PriorityQueue<Tree> queue;
    for (const auto &pair : data) {
        Tree new_node = Tree(pair.first);
        queue.add(new_node, pair.second);
    }
#define Picked_cnt 2
    Tree tmp_tree;
    std::array<std::tuple<Tree, int>, Picked_cnt> childrens; 
    while (queue.len() != 1) {
        for (std::size_t i = 0; i < Picked_cnt; childrens[i++] = *queue.get_min());
        int new_priority = std::get<1>(childrens[0]) + std::get<1>(childrens[1]);
        tmp_tree.left = std::make_shared<Tree>(std::get<Tree>(childrens[0]));
        tmp_tree.right = std::make_shared<Tree>(std::get<Tree>(childrens[1]));
        queue.add(tmp_tree, new_priority);
        tmp_tree = Tree();
    }
#undef Picked_cnt
    this->root = std::make_shared<Tree>(std::get<Tree>(*queue.get_min()));
}
template <typename T>
HaffmanTree<T>::HaffmanTree(std::ifstream &file) : HaffmanTree<T>(get_prioreties(file)) {}

template <typename T>
std::unordered_map<T, std::size_t> HaffmanTree<T>::get_prioreties(std::ifstream &file) const {
    std::unordered_map<T, std::size_t> char_frequency;
    for (T c; file.get(c); char_frequency[c]++);
    file.clear();
    file.seekg(0, std::ios::beg);
    return char_frequency;
}

template <typename T>
void HaffmanTree<T>::get_codes(std::unordered_map<T, std::pair<Storage, std::uint8_t>> &codes) const {
    codes_traversal(this->root, 0, Storage(0), codes);
}

template <typename T>
void HaffmanTree<T>::codes_traversal(std::shared_ptr<Tree> node, std::uint8_t size, Storage code, std::unordered_map<T, std::pair<Storage, std::uint8_t>> &codes) const {
    if (!node) return;
    if (node->data.has_value())
        codes[*node->data] = { code, size };
    codes_traversal(node->left, size + 1, code << 1 | 0, codes);
    codes_traversal(node->right, size + 1, code << 1 | 1, codes);
}

#endif // __HAFFMAN_HPP__