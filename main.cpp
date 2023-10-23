#include <iostream>
#include "utils.h"

int main(int argc, char** argv){
    if (argc < 3) { return -1; }
    crypto_utils::CryptoEngine engine;
    if (argv[1] == "c") {

        engine.choose_type(crypto_utils::TypeCryptographic::XOR);
        engine.choose_action(crypto_utils::TypeAction::Encrypt);
        utils::process_in_directory(argv[2], engine);
    }
    if (argv[1] == "d") {
        engine.choose_type(crypto_utils::TypeCryptographic::XOR);
        engine.choose_action(crypto_utils::TypeAction::Decrypt);
        utils::process_in_directory(argv[2], engine);
    }

    return 0;
}
