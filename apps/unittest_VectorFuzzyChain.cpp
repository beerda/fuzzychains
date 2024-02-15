#include <gtest/gtest.h>
#include "VectorFuzzyChain.h"


TEST(VectorFuzzyChainTest, Goedel) {
    VectorFuzzyChain<GOEDEL> b1;
    VectorFuzzyChain<GOEDEL> b2;

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

TEST(VectorFuzzyChainTest, Goguen) {
    VectorFuzzyChain<GOGUEN> b1;
    VectorFuzzyChain<GOGUEN> b2;

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

TEST(VectorFuzzyChainTest, Lukasiewicz) {
    VectorFuzzyChain<LUKASIEWICZ> b1;
    VectorFuzzyChain<LUKASIEWICZ> b2;

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
