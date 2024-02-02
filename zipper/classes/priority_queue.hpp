#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__

#include <memory>
#include <optional>

/* Очередь приоритетов */
// Очередь написана на основе односвязанного списка

template<typename T>
class PriorityQueue {
    // Структура узла
    struct Node {
        T val;                         // Значение
        int priority;                  // Приоритет
        std::shared_ptr<Node> next;    // Указатель на следующий элемент очереди

        explicit Node(T val, int priority); // Конструктор узла списка
    };
    std::shared_ptr<Node> head; // Указатель на голову списка(первый элемент очереди)
public:
    /* Конструкторы */
    // Пустая очередь
    explicit PriorityQueue(void);
    // Очередь на основе списка инициализации(Пара<Значение приоритет>)
    PriorityQueue(std::initializer_list<std::pair<T, int>> data);

    // Добавление элемента в очередь
    void add(T val, int priority);
    
    // Длина очереди
    std::size_t len(void) const;

    /**
     * @brief Получение минимального по приоритету элемента
     * @details Элемент из списка удаляется
     * 
     * @return Кортеж из значения и его приоритета
     */
    std::optional<std::tuple<T, int>> get_min(void);
    /**
     * @brief Получение максимального по приоритету элемента
     * @details Элемент из списка удаляется
     * 
     * @return Кортеж из значения и его приоритета
     */
    std::optional<std::tuple<T, int>> get_max(void);
};

template <typename T>
PriorityQueue<T>::Node::Node(T val, int priority) : val(val), priority(priority), next(nullptr) {}

template <typename T>
PriorityQueue<T>::PriorityQueue(void) : head(nullptr) {}
template <typename T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<std::pair<T, int>> data) {
    for (const auto &pair : data)
        this->add(pair.first, pair.second);
}

template <typename T>
void PriorityQueue<T>::add(T val, int priority) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(val, priority);
    if (!head || head->priority >= priority) {
        new_node->next = head;
        head = new_node;
    } else {
        std::shared_ptr<Node> next_node = head;
        std::shared_ptr<Node> inode = head->next;
        for (; inode && inode->priority < new_node->priority; next_node = inode, inode = inode->next);
        next_node->next = new_node;
        new_node->next = inode; 
    }
}

template <typename T>
std::size_t PriorityQueue<T>::len(void) const {
    std::size_t len = 0;
    for (std::shared_ptr<Node> inode = head; inode; inode = inode->next, len++);
    return len; 
}

template <typename T>
std::optional<std::tuple<T, int>> PriorityQueue<T>::get_min(void) {
    if (!head) return std::nullopt;
    std::shared_ptr<Node> tmp = head;
    head = head->next;
    return std::optional(std::tuple<T, int>(tmp->val, tmp->priority));
}
template <typename T>
std::optional<std::tuple<T, int>> PriorityQueue<T>::get_max(void) {
    if (!head) return std::nullopt;
    std::shared_ptr<Node> next_node = nullptr;
    std::shared_ptr<Node> inode = head->next;
    for (; inode->next; next_node = inode, inode = inode->next);
    if (next_node)
        next_node->next = nullptr;
    else
        head = nullptr;
    return std::optional(std::tuple<T, int>(inode->val, inode->priority));
}

#endif // __PRIORITY_QUEUE_HPP__
