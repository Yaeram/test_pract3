#include <iostream>
#include "utils.h"

int main(int argc, char** argv){
    if (argc < 4) {
        std::cerr << "Usage: e[d] <path>\n";
        return -1;
    }
    crypto_utils::CryptoEngine engine;
    std::string flag (argv[1]);
    std::string type (argv[2]);
    if (type == "xor") { engine.choose_type(crypto_utils::TypeCryptographic::XOR); };
    if (type == "shift") { engine.choose_type(crypto_utils::TypeCryptographic::shift); };
    if (flag == "e") {
        std::cout << "encrypting" << std::endl;
        engine.choose_action(crypto_utils::TypeAction::Encrypt);
    } else if (flag == "d") {
        std::cout << "decrypting" << std::endl;
        engine.choose_action(crypto_utils::TypeAction::Decrypt);
    } else {
        std::cerr << "flag is not valid [" << flag << "]"<< std::endl;
    }
    utils::process_in_directory(argv[3], engine);

    return 0;
}
