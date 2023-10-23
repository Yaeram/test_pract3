
#include "gtest/gtest.h"
#include "crypto_utils.h"
#include <fstream>
#include <filesystem>
#include "utils.h"

class CryptoUtilsFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        engine = new crypto_utils::CryptoEngine();
    }

    virtual void TearDown() {
        delete engine;
    }

    crypto_utils::CryptoEngine * engine;
};

TEST_F(CryptoUtilsFixture, process_xor){
    std::filesystem::create_directories("tmp");
    std::ofstream test_file("tmp/test");
    test_file << "123\n";
    test_file.close();
    std::ofstream test_file_second("tmp/test_second");
    test_file_second << "567\n";
    test_file_second.close();

    std::ifstream initial("tmp/test");
    std::ifstream initial_second("tmp/test_second");
    auto first_sum_initial = utils::checksum(initial);
    auto second_sum_initial = utils::checksum(initial_second);
    initial.close();
    initial_second.close();
    engine->choose_type(crypto_utils::TypeCryptographic::XOR);
    engine->choose_action(crypto_utils::TypeAction::Encrypt);
    ASSERT_EQ(engine->push_to_queue("tmp/test"), true);
    ASSERT_EQ(engine->push_to_queue("tmp/test_second"), true);
    ASSERT_EQ(engine->process_queue(), true);
    engine->choose_type(crypto_utils::TypeCryptographic::XOR);
    engine->choose_action(crypto_utils::TypeAction::Decrypt);
    ASSERT_EQ(engine->push_to_queue("tmp/test"), true);
    ASSERT_EQ(engine->push_to_queue("tmp/test_second"), true);
    ASSERT_EQ(engine->process_queue(), true);
    std::ifstream control("tmp/test");
    std::ifstream control_second("tmp/test_second");
    auto first_sum_final = utils::checksum(control);
    auto second_sum_final = utils::checksum(control_second);
    ASSERT_EQ(first_sum_final, first_sum_initial);
    ASSERT_EQ(second_sum_final, second_sum_initial);
    std::filesystem::remove_all("tmp/*");

}



