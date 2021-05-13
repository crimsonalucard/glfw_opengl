//
// Created by briany on 5/12/21.
//

#include <utils.h>

std::string readFromFile(std::string fileName) {
    std::ifstream it(fileName);
    return std::string(std::istreambuf_iterator<char>(it), std::istreambuf_iterator<char>());
}

