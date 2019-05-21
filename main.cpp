#include <iostream>
#include "hash_table.hpp"
#include "input.hpp"
#include "quadractic_probing.hpp"

int main() {
    //hash_table<uint32_t, std::string> hash_table;
    quadractic_probing<uint32_t, std::string> hash_table;

    //std::vector<std::string> const& names = {"jean diego silva fontenaA", "kakkak", "abobs"};

    std::cout << "Inserting data..." << std::endl;
    std::vector<std::string> const& names = get_data("Doc/nomes_10000.txt");
    for (auto const& name : names) {
        hash_table.insert(name);
    }

    std::cout << "Searching..." << std::endl;
    std::vector<std::string> const& targets = get_data("Doc/consultas.txt");
    for (auto const& name : targets) {
        if (auto const& result = hash_table.search(name); result == -1) {
            std::cout << "[" << name << "] not found\n";
        } else {
            std::cout << "[" << name << "] found with " << (uint32_t) result << " tests";
            std::cout << std::endl;
        }
    }
    //hash_table.print();
    std::cout << "Load factor: " << (float) hash_table.load_factor();
    std::cout << "%" << std::endl;
    std::cout << "Collisions: " << (uint32_t) hash_table.collisions();
    std::cout << std::endl;

    return 0;
}