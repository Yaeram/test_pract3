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
    for( ;!m_files_queue.empty(); ) {
        switch (m_type) {
            case TypeCryptographic::XOR:
                if (!process_xor(m_files_queue.front())) {
                    return false;
                }
                m_files_queue.pop();
                break;
            case shuffle:
                break;
            default:
                return false;

        }
    }
    return true;
}

bool crypto_utils::CryptoEngine::process_xor(const std::string &filename, unsigned char base) {
    std::ifstream file_input(filename);
    std::string new_filename(filename + "_tmp");
    std::ofstream file_output(new_filename);
    char ch = 0x00;
    while(file_input.get(ch)){
        ch ^= base;
        file_output << ch;
    }
    file_input.close();
    file_output.close();
    if (!std::filesystem::remove(filename)) {
        return false;
    }
    std::filesystem::rename(new_filename, filename);
    return true;
}

void crypto_utils::CryptoEngine::choose_action(const crypto_utils::TypeAction &type) {
    m_action = type;
}
