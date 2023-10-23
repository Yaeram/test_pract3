#include <iostream>
#include "utils.h"

int main() {
    crypto_utils::CryptoEngine engine;
    engine.choose_type(crypto_utils::TypeCryptographic::XOR);
    engine.choose_action(crypto_utils::TypeAction::Encrypt);
    utils::process_in_directory("B:/CProjects/Env", engine);
    engine.choose_action(crypto_utils::TypeAction::Decrypt);
    utils::process_in_directory("B:/CProjects/Env", engine);
    return 0;
}
