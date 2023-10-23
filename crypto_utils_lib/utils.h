#pragma once
#include "fstream"

namespace utils {
    uint32_t checksum(std::ifstream& file);
}