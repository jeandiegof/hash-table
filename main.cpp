#include <iostream>
#include "analysis.hpp"
#include "hash_table.hpp"
#include "input.hpp"
#include "linear_probing.hpp"
#include "quadratic_probing.hpp"

int main() {
    // 12511 18979
    constexpr uint32_t table_size = 18979;
    std::vector<hash_table<uint32_t, std::string>*> tables;
    tables.push_back(new linear_probing<uint32_t, std::string>);
    tables.push_back(new linear_probing<uint32_t, std::string>);
    tables.push_back(new quadratic_probing<uint32_t, std::string>);
    tables.push_back(new quadratic_probing<uint32_t, std::string>);

    tables[0]->enable_hash2(false);
    tables[1]->enable_hash2(true);
    tables[2]->enable_hash2(false);
    tables[3]->enable_hash2(true);

    std::vector<std::string> const& names = get_data("Doc/nomes_10000.txt");
    std::vector<std::string> const& targets = get_data("Doc/consultas.txt");
    std::vector<std::string> const& messages = {"\nLinear probing using accumulate method:\n",
                                                "\nLinear probing using djb2 algorithm:\n",
                                                "\nquadratic probing using accumulate method:\n",
                                                "\nquadratic probing using djb2 algorithm:\n"};

    uint8_t i = 0;
    for (auto table : tables) {
        table->set_size(table_size);
        insert(names, *table);
        std::cout << messages[i++] << std::flush;
        auto result = search(targets, *table);
        best_and_worst(result);
        load_factor(*table);
        collisions(*table);
        delete table;
    }

    return 0;
}