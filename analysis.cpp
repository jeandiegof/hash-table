#include <string>
#include <vector>
#include "hash_table.hpp"

bool insert(const std::vector<std::string>& data, hash_table<uint32_t, std::string>& table) {
    for (const auto& d : data) {
        if (!table.insert(d)) return false;
    }
    return true;
}

std::vector<std::pair<int32_t, std::string>> search(const std::vector<std::string>& data, hash_table<uint32_t, std::string>& table) {
    int32_t minimum = 1;
    int32_t maximum = 0;
    std::string worst;
    std::string best;

    for (auto const& d : data) {
        auto found = table.search(d);
        if (found < 0) {
            std::cout << "\t" << d << " not found." << std::endl;
        }
        if (found > maximum) {
            maximum = found;
            worst = d;
        } else if (found > 0 && found <= minimum) {
            minimum = found;
            best = d;
        }
    }
    std::vector<std::pair<int32_t, std::string>> result;
    result.push_back(std::move(std::pair(minimum, best)));
    result.push_back(std::move(std::pair(maximum, worst)));
    return result;
}

void load_factor(hash_table<uint32_t, std::string>& table) {
    std::cout << "\tLoad factor: " << (float)table.load_factor();
    std::cout << "%" << std::endl;
}

void collisions(hash_table<uint32_t, std::string>& table) {
    std::cout << "\tCollisions: " << (uint32_t)table.collisions();
    std::cout << std::endl;
}

void best_and_worst(std::vector<std::pair<int32_t, std::string>> result) {
    std::cout << "\n\tBest case: " << result[0].second;
    std::cout << " with " << (int)result[0].first << " tests";
    std::cout << "\n\tWorst case: " << result[1].second;
    std::cout << " with " << (int)result[1].first << " tests\n";
}