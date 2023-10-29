#include "utils.h"

uint32_t utils::checksum(std::ifstream& file) {
    uint32_t sum = 0;
    uint32_t word = 0;
    while (file.read(reinterpret_cast<char*>(&word), sizeof(word))) {
    sum += word;
    word = 0;
    }
    sum += word;
    return sum;
}

bool utils::process_in_directory(const std::filesystem::path & path, crypto_utils::CryptoEngine & engine){
    for (auto &de : std::filesystem::recursive_directory_iterator(path)) {
        if (!de.is_regular_file()) {continue;}
        if (!engine.push_to_queue(de.path().string())){
            std::cout << "failed to push to queue " << de.path().string() << std::endl;
            return false;
        }
    }
    return engine.process_queue();
}