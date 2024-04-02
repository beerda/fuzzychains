#include <gtest/gtest.h>
#include "SimdFuzzyChain.h"


TEST(SimdFuzzyChainTest, LargeSum) {
    SimdFuzzyChain<GOEDEL> b1;

    EXPECT_TRUE(b1.empty());
    EXPECT_TRUE(b1.size() == 0);
    EXPECT_FLOAT_EQ(b1.sum(), 0.0);

    float expected = 0.0;
    for (size_t i = 0; i < 1024; ++i) {
        float val = (i % 256) / 256.0;
        expected += val;
        b1.pushBack(val);

        EXPECT_FLOAT_EQ(b1.sum(), expected);
    }
}

TEST(SimdFuzzyChainTest, Goedel) {
    SimdFuzzyChain<GOEDEL> b1;
    SimdFuzzyChain<GOEDEL> b2;

    EXPECT_TRUE(b1.empty());
    EXPECT_TRUE(b1.size() == 0);
    EXPECT_FLOAT_EQ(b1.sum(), 0.0);

    b1.pushBack(0.8);
    b1.pushBack(0.1);
    b1.pushBack(0);
    b1.pushBack(1);

    b2.pushBack(0.6);
    b2.pushBack(0.6);
    b2.pushBack(0.3);
    b2.pushBack(0.3);

    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.8);
    EXPECT_FLOAT_EQ(b1.at(1), 0.1);
    EXPECT_FLOAT_EQ(b1.at(2), 0);
    EXPECT_FLOAT_EQ(b1.at(3), 1);
    EXPECT_FLOAT_EQ(b1.sum(), 0.8 + 0.1 + 0 + 1);

    b1.conjunctWith(b2);
    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.6);
    EXPECT_FLOAT_EQ(b1.at(1), 0.1);
    EXPECT_FLOAT_EQ(b1.at(2), 0.0);
    EXPECT_FLOAT_EQ(b1.at(3), 0.3);
    EXPECT_FLOAT_EQ(b1.sum(), 0.6 + 0.1 + 0 + 0.3);
}

TEST(SimdFuzzyChainTest, Goguen) {
    SimdFuzzyChain<GOGUEN> b1;
    SimdFuzzyChain<GOGUEN> b2;

    EXPECT_TRUE(b1.empty());
    EXPECT_TRUE(b1.size() == 0);
    EXPECT_FLOAT_EQ(b1.sum(), 0.0);

    b1.pushBack(0.8);
    b1.pushBack(0.1);
    b1.pushBack(0);
    b1.pushBack(1);

    b2.pushBack(0.6);
    b2.pushBack(0.6);
    b2.pushBack(0.3);
    b2.pushBack(0.3);

    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.8);
    EXPECT_FLOAT_EQ(b1.at(1), 0.1);
    EXPECT_FLOAT_EQ(b1.at(2), 0);
    EXPECT_FLOAT_EQ(b1.at(3), 1);
    EXPECT_FLOAT_EQ(b1.sum(), 0.8 + 0.1 + 0 + 1);

    b1.conjunctWith(b2);
    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.8 * 0.6);
    EXPECT_FLOAT_EQ(b1.at(1), 0.1 * 0.6);
    EXPECT_FLOAT_EQ(b1.at(2), 0.0);
    EXPECT_FLOAT_EQ(b1.at(3), 0.3);
    EXPECT_FLOAT_EQ(b1.sum(), 0.8 * 0.6 + 0.1 * 0.6 + 0 + 0.3);
}

TEST(SimdFuzzyChainTest, Lukasiewicz) {
    SimdFuzzyChain<LUKASIEWICZ> b1;
    SimdFuzzyChain<LUKASIEWICZ> b2;

    EXPECT_TRUE(b1.empty());
    EXPECT_TRUE(b1.size() == 0);
    EXPECT_FLOAT_EQ(b1.sum(), 0.0);

    b1.pushBack(0.8);
    b1.pushBack(0.1);
    b1.pushBack(0);
    b1.pushBack(1);

    b2.pushBack(0.6);
    b2.pushBack(0.6);
    b2.pushBack(0.3);
    b2.pushBack(0.3);

    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.8);
    EXPECT_FLOAT_EQ(b1.at(1), 0.1);
    EXPECT_FLOAT_EQ(b1.at(2), 0);
    EXPECT_FLOAT_EQ(b1.at(3), 1);
    EXPECT_FLOAT_EQ(b1.sum(), 0.8 + 0.1 + 0 + 1);

    b1.conjunctWith(b2);
    EXPECT_TRUE(!b1.empty());
    EXPECT_TRUE(b1.size() == 4);
    EXPECT_FLOAT_EQ(b1.at(0), 0.4);
    EXPECT_FLOAT_EQ(b1.at(1), 0.0);
    EXPECT_FLOAT_EQ(b1.at(2), 0.0);
    EXPECT_FLOAT_EQ(b1.at(3), 0.3);
    EXPECT_FLOAT_EQ(b1.sum(), 0.4 + 0.0 + 0 + 0.3);
}
