#pragma once
#include <cmath>
#include <string>
#include <vector>

constexpr uint16_t table_size = 18979;

template <typename K, typename T>
class hash_table {
   public:
    hash_table();
    bool insert(const T& d);
    int32_t search(const T& d);
    void print();
    float load_factor();
    uint32_t collisions();

   private:
    K hash(const T& d);
    uint8_t fix_range(const char& c);
    std::vector<T> table;
    bool _is_full;
    uint16_t _insertions;
    uint32_t _collisions;
};

template <typename K, typename T>
hash_table<K, T>::hash_table()
    : table(table_size),
      _is_full(false),
      _insertions(0),
      _collisions(0) {
}

template <typename K, typename T>
bool hash_table<K, T>::insert(const T& d) {
    if (_is_full) {
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
        if (table[target_index] == "") {
            table[target_index] = d;
            _insertions++;
            return true;
        }
        _collisions++;
    }
    std::cout << "Man, the table is full :/" << std::endl;
    std::cout << "Insertions: " << (uint16_t) _insertions;
    std::cout << std::endl;
    _is_full = true;
    return false;
}

template <typename K, typename T>
int32_t hash_table<K, T>::search(const T& d) {
    //std::cout << "Searching for " << d << std::endl;
    uint16_t count = 0;
    K key = hash(d);

    for (uint16_t i = 0; i < table.size(); i++) {
        count++;
        const uint32_t target_index = static_cast<uint32_t>((key + std::pow(i, 2))) % table_size;
        if (table[target_index] == d) return count;
    }
    //std::cout << "Found with " << (uint16_t) count << " tests at " << (uint16_t) key << std::endl;
    return -1;
}

// This function uses Horner's method to calculate the hash
//  p(x) = a0 + a1*x + a2*x² + a3*x³ ... anx^n
//       = a0 + x(a1 + x(a2 + x(a3 + ... + x(an-1 + x(*an)))))
// Otherwise we would be having integer overflows all the time
template <typename K, typename T>
K hash_table<K, T>::hash(const T& d) {
    const uint8_t p = 79;
    K key = 0;
    for (std::uint8_t i = 0; i < d.size(); i++) {
        const uint8_t char_value = fix_range(d[i]);
        key = (p * key + char_value) % table_size;
    }
    return key;
}

template <typename K, typename T>
uint8_t hash_table<K, T>::fix_range(const char& c) {
    if (c == ' ') return 53;
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
    return (100.0 * _insertions) / table_size;
}

template <typename K, typename T>
uint32_t hash_table<K, T>::collisions() {
    return _collisions;
}