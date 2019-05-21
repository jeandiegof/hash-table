#include <iostream>
#include "hash_table.hpp"
#include "input.hpp"

int main() {
    hash_table<uint32_t, std::string> hash_table;

    std::cout << "Inserting data..." << std::endl;
    std::vector<std::string> const& names = get_data("Doc/nomes_10000.txt");
    for (auto const& name : names) {
        hash_table.insert(name);
    }

    std::cout << "Searching..." << std::endl;
    std::vector<std::string> const& targets = get_data("Doc/consultas.txt");
    for (auto const& name : targets) {
        if (auto const& result = hash_table.search(name); result == 0) {
            std::cout << "[" << name << "] not found\n";
        }
    }
    //hash_table.print();
    std::cout << "Load factor: " << (float) hash_table.load_factor();
    std::cout << "%" << std::endl;
    std::cout << "Collisions: " << (uint32_t) hash_table.collisions();
    std::cout << std::endl;

    return 0;
}