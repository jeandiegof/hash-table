#pragma once

#include <string>
#include <utility>
#include <vector>
#include "hash_table.hpp"

bool insert(const std::vector<std::string>& data, hash_table<uint32_t, std::string>& table);
std::vector<std::pair<int32_t, std::string>> search(const std::vector<std::string>& data, hash_table<uint32_t, std::string>& table);
void load_factor(hash_table<uint32_t, std::string>& table);
void collisions(hash_table<uint32_t, std::string>& table);
void best_and_worst(std::vector<std::pair<int32_t, std::string>> result);