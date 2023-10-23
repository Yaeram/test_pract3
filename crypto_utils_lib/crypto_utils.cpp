#include "crypto_utils.h"
#include <fstream>
#include <sys/stat.h>



crypto_utils::CryptoEngine::CryptoEngine() {

}
crypto_utils::CryptoEngine::~CryptoEngine() {

}

void crypto_utils::CryptoEngine::choose_type(const TypeCryptographic & type) {
    m_type = type;
}

int exist(const char *name)
{
    struct stat buffer;
    return (stat (name, &buffer) == 0);
}

bool crypto_utils::CryptoEngine::push_to_queue(const std::string & filename){
    if (exist(filename.c_str())) {
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
                break;
        }
    }
    return true;
}

bool crypto_utils::CryptoEngine::process_xor(const std::string &filename, unsigned char base) {
    std::ifstream file_input(filename);
    std::string new_filename;
    switch (m_action) {
        case Encrypt:
            new_filename = filename + "_cr";
            break;
        case Decrypt:
            new_filename = filename + "_decr";
            break;
    }
    std::ofstream file_output(new_filename);
    char ch = 0x00;
    while(file_input.get(ch)){
        ch ^= base;
        file_output << ch;
    }
}

void crypto_utils::CryptoEngine::choose_action(const crypto_utils::TypeAction &type) {
    m_action = type;
}
