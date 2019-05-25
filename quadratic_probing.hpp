#pragma once
#include <numeric>
#include "hash_table.hpp"

template <typename K, typename T>
class quadratic_probing : public hash_table<K, T> {
   public:
    quadratic_probing() : _use_hash2{false} {}
    ~quadratic_probing() {}
    bool insert(const T& d) override;
    int32_t search(const T& d) override;
    void enable_hash2(bool opt);

   private:
    virtual K hash(const T& d);
    K hash2(const T& d);
    bool _use_hash2;
};

template <typename K, typename T>
void quadratic_probing<K, T>::enable_hash2(bool opt) {
    _use_hash2 = opt;
}

// This function uses Horner's method to calculate the hash
//  p(x) = a0 + a1*x + a2*x² + a3*x³ ... anx^n
//       = a0 + x(a1 + x(a2 + x(a3 + ... + x(an-1 + x(*an)))))
// Otherwise we would be having integer overflows all the time
template <typename K, typename T>
K quadratic_probing<K, T>::hash(const T& d) {
    return std::accumulate(d.begin(), d.end(), 0) % hash_table<K, T>::table.size();
}

// djb2 algorithm, by dan bernstein
template <typename K, typename T>
K quadratic_probing<K, T>::hash2(const T& d) {
    uint64_t hash = 5381;
    for (const auto& c : d) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % hash_table<K, T>::table.size();
}

template <typename K, typename T>
bool quadratic_probing<K, T>::insert(const T& d) {
    if (hash_table<K, T>::_is_full) {
        return false;
    }

    K k = (_use_hash2) ? hash2(d) : hash(d);
    for (uint16_t i = 0; i < hash_table<K, T>::table.size(); i++) {
        const uint32_t target_index = static_cast<uint32_t>((k + std::pow(i, 2))) % hash_table<K, T>::table.size();
        if (hash_table<K, T>::table[target_index] == "") {
            hash_table<K, T>::table[target_index] = d;
            hash_table<K, T>::_insertions++;
            return true;
        }
        if (k == target_index) {
            hash_table<K, T>::_collisions++;
        }
    }
    std::cout << "The table is full :/" << std::endl;
    std::cout << "Insertions: " << (uint16_t)hash_table<K, T>::_insertions;
    std::cout << std::endl;
    hash_table<K, T>::_is_full = true;
    return false;
}

template <typename K, typename T>
int32_t quadratic_probing<K, T>::search(const T& d) {
    uint16_t count = 0;
    K key = (_use_hash2) ? hash2(d) : hash(d);

    for (uint16_t i = 0; i < hash_table<K, T>::table.size(); i++) {
        count++;
        const uint32_t target_index = static_cast<uint32_t>((key + std::pow(i, 2))) % hash_table<K, T>::table.size();
        if (hash_table<K, T>::table[target_index] == d) return count;
    }
    return -1;
}
