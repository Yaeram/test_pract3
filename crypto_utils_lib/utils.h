#pragma once
#include "fstream"
#include <filesystem>
#include "crypto_utils.h"

namespace utils {
    uint32_t checksum(std::ifstream& file);
    bool process_in_directory(const std::filesystem::path & path, crypto_utils::CryptoEngine & engine);

}