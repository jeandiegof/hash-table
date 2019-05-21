#pragma once
#include "hash_table.hpp"

template <typename K, typename T>
class quadractic_probing : public hash_table<K, T> {
   public:
    quadractic_probing();
    bool insert(const T& d);
    int32_t search(const T& d);
   private:
    K hash(const T& d);
};

template <typename K, typename T>
quadractic_probing<K, T>::quadractic_probing() {
    std::cout << "Hello there!!\n";
    std::cout << (int) hash_table<K,T>::collisions();
}

template <typename K, typename T>
K quadractic_probing<K, T>::hash(const T& d) {
    const uint8_t p = 79;
    K key = 0;
    for (std::uint8_t i = 0; i < d.size(); i++) {
        const uint8_t char_value = hash_table<K,T>::fix_range(d[i]);
        key = (p * key + char_value) % table_size;
    }
    return key;
}

template <typename K, typename T>
bool quadractic_probing<K, T>::insert(const T& d) {
    if (hash_table<K,T>::_is_full) {
        return false;
    }

    K k = hash(d);
    //std::cout << "[" << (uint32_t) k << "] " << d << std::endl;
    // if the k place is already being used
    for (uint16_t i = 0; i < table_size; i++) {
        const uint32_t target_index = static_cast<uint32_t>((k + std::pow(i, 2))) % table_size;
        // std::cout << "Collision for key " << (uint32_t) k << "\t[";
        // std::cout << d << "] trying slot " << (uint16_t)target_index;
        // std::cout << " = " << (uint32_t) k << " + (";
        // std::cout << (uint16_t) i << "*" << (uint16_t) i;
        // std::cout << ") % " << table_size << std::endl;
        if (hash_table<K,T>::table[target_index] == "") {
            hash_table<K,T>::table[target_index] = d;
            hash_table<K,T>::_insertions++;
            return true;
        }
        hash_table<K,T>::_collisions++;
    }
    std::cout << "Man, the table is full :/" << std::endl;
    std::cout << "Insertions: " << (uint16_t) hash_table<K,T>::_insertions;
    std::cout << std::endl;
    hash_table<K,T>::_is_full = true;
    return false;
}

template <typename K, typename T>
int32_t quadractic_probing<K, T>::search(const T& d) {
    //std::cout << "Searching for " << d << std::endl;
    uint16_t count = 0;
    K key = hash(d);

    for (uint16_t i = 0; i < hash_table<K,T>::table.size(); i++) {
        count++;
        const uint32_t target_index = static_cast<uint32_t>((key + std::pow(i, 2))) % table_size;
        if (hash_table<K,T>::table[target_index] == d) return count;
    }
    //std::cout << "Found with " << (uint16_t) count << " tests at " << (uint16_t) key << std::endl;
    return -1;
}

