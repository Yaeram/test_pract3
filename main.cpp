#include <iostream>
#include "crypto_utils.h"

int main() {
    crypto_utils::CryptoEngine engine;
    engine.choose_type(crypto_utils::TypeCryptographic::XOR);
    engine.choose_action(crypto_utils::TypeAction::Decrypt);
    engine.push_to_queue("B:/CProjects/Env/test.txt_cr");
    engine.process_queue();
    return 0;
}
