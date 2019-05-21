#include "input.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> get_data(std::string filename) {
    std::vector<std::string> data;
    std::ifstream file;
    file.open(filename);
    for (std::string line; std::getline(file, line);) {
        data.push_back(line);
    }
    file.close();
    return data;
}