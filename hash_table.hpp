#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

//constexpr uint16_t table_size = 18979;
//constexpr uint16_t table_size = 18979;

template <typename K, typename T>
class hash_table {
   public:
    hash_table();
    ~hash_table(){};
    virtual bool insert(const T& d) = 0;
    virtual int32_t search(const T& d) = 0;
    void print();
    float load_factor();
    uint32_t collisions();
    void set_size(uint32_t size);
    uint32_t size();
    virtual void enable_hash2(bool opt) = 0;

   protected:
    virtual K hash(const T& d) = 0;
    uint8_t fix_range(const char& c);
    std::vector<T> table;
    bool _is_full;
    uint16_t _insertions;
    uint32_t _collisions;
};

template <typename K, typename T>
hash_table<K, T>::hash_table()
    : table(0),
      _is_full(false),
      _insertions(0),
      _collisions(0) {
}

template <typename K, typename T>
void hash_table<K, T>::set_size(uint32_t size) {
    table.resize(size);
}

template <typename K, typename T>
uint32_t hash_table<K, T>::size() {
    return table.size();
}

template <typename K, typename T>
uint8_t hash_table<K, T>::fix_range(const char& c) {
    if (c == ' ') return 0;
    // fix range to [1, 52], A-Za-z
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 1 : c - 'a' + 27;
}

template <typename K, typename T>
void hash_table<K, T>::print() {
    for (uint16_t i = 0; i < table.size(); i++) {
        std::cout << (uint16_t)i << "\t\t" << table[i] << std::endl;
    }
}

template <typename K, typename T>
float hash_table<K, T>::load_factor() {
    return (100.0 * _insertions) / table.size();
}

template <typename K, typename T>
uint32_t hash_table<K, T>::collisions() {
    return _collisions;
}