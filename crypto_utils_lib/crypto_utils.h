#pragma once
#include <string>
#include <iostream>
#include <queue>

namespace crypto_utils {
    enum TypeCryptographic {
      XOR,
      shuffle
    };
    enum TypeAction {
        Encrypt,
        Decrypt
    };
    class CryptoEngine {
    public:
        CryptoEngine();
        ~CryptoEngine();
        void choose_type(const TypeCryptographic & type);
        void choose_action(const TypeAction & type);
        bool push_to_queue(const std::string & filename);
        bool process_queue();
    private:
        TypeCryptographic m_type;
        TypeAction m_action;
        bool process_xor(const std::string & filename, unsigned char base = 0x56);
        std::queue<std::string> m_files_queue;
    };
}
