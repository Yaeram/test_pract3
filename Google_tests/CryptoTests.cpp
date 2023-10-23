#pragma once
#include "gtest/gtest.h"
#include "crypto_utils.h"
#include <fstream>

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

//TEST_F(CalcUtilsFixture, Max){
//
//EXPECT_EQ(utils->max(2,2), 2);
//EXPECT_EQ(utils->max(1,2), 2);
//EXPECT_EQ(utils->max(3,6), 6);
//EXPECT_EQ(utils->max(-4,2), 2);
//}



