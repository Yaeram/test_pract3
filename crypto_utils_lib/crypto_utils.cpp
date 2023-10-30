#include "crypto_utils.h"
#include <fstream>
#include <filesystem>


crypto_utils::CryptoEngine::CryptoEngine() {

}
crypto_utils::CryptoEngine::~CryptoEngine() {

}

void crypto_utils::CryptoEngine::choose_type(const TypeCryptographic & type) {
    m_type = type;
}

bool crypto_utils::CryptoEngine::push_to_queue(const std::string & filename){
    if (std::filesystem::exists(filename)) {
        m_files_queue.push(filename);
        return true;
    }
    return false;
}
bool crypto_utils::CryptoEngine::process_queue(){
    uint32_t count = 0;
    for( ;!m_files_queue.empty(); ) {
        switch (m_type) {
            case XOR:
                if (!process_xor(m_files_queue.front())) {
                    return false;
                }
                break;
            case shuffle:
                break;
            case shift:
                if (!process_shift(m_files_queue.front())) {
                    return false;
                }
                break;
            default:
                return false;

        }
        m_files_queue.pop();
        count++;
    }
    std::cout << "Processed " << count << " files" << std::endl;
    return true;
}

bool crypto_utils::CryptoEngine::process_xor(const std::string &filename, unsigned char base) {
    std::ifstream file_input(filename, std::ios::binary);
    std::string new_filename(filename + "_tmp");
    std::ofstream file_output(new_filename, std::ios::binary);
    char buffer[1024];
    while (file_input.read(buffer, sizeof(buffer))) {
        for (char & i : buffer) {
            i ^= base;
        }
        file_output.write(buffer, sizeof(buffer));
    }
    for (int i = 0; i < file_input.gcount(); i++) {
        buffer[i] ^= base;
    }
    file_output.write(buffer, file_input.gcount());
    file_input.close();
    file_output.close();
    if (!std::filesystem::remove(filename)) {
        std::cout << " crypto_utils::CryptoEngine::process_xor \n failed to remove " << filename << std::endl;
        return false;
    }
    std::filesystem::rename(new_filename, filename);
    return true;
}

bool crypto_utils::CryptoEngine::process_shift(const std::string &filename, unsigned char base) {
    std::ifstream file_input(filename, std::ios::binary);
    std::string new_filename(filename + "_tmp");
    std::ofstream file_output(new_filename, std::ios::binary);
    char buffer[1024];
    if (m_action == Decrypt) {base = -base;};
    while (file_input.read(buffer, sizeof(buffer))) {
        for (char & i : buffer) {
            i += base;
        }
        file_output.write(buffer, sizeof(buffer));
    }
    for (int i = 0; i < file_input.gcount(); i++) {
        buffer[i] += base;
    }
    file_output.write(buffer, file_input.gcount());
    file_input.close();
    file_output.close();
    if (!std::filesystem::remove(filename)) {
        std::cout << " crypto_utils::CryptoEngine::process_shift \n failed to remove " << filename << std::endl;
        return false;
    }
    std::filesystem::rename(new_filename, filename);
    return true;
}

void crypto_utils::CryptoEngine::choose_action(const crypto_utils::TypeAction &type) {
    m_action = type;
}
