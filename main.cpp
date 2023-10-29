#include <iostream>
#include "utils.h"

int main(int argc, char** argv){
    if (argc < 3) {
        std::cerr << "Usage: e[d] <path>\n";
        return -1;
    }
    crypto_utils::CryptoEngine engine;
    std::string flag (argv[1]);
    if (flag == "e") {
        std::cout << "encrypting" << std::endl;
        engine.choose_type(crypto_utils::TypeCryptographic::XOR);
        engine.choose_action(crypto_utils::TypeAction::Encrypt);
        utils::process_in_directory(argv[2], engine);
    } else if (flag == "d") {
        std::cout << "decrypting" << std::endl;
        engine.choose_type(crypto_utils::TypeCryptographic::XOR);
        engine.choose_action(crypto_utils::TypeAction::Decrypt);
        utils::process_in_directory(argv[2], engine);
    } else {
        std::cerr << "flag is not valid [" << flag << "]"<< std::endl;
    }

    return 0;
}
