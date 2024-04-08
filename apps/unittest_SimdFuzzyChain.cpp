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

TEST(SimdFuzzyChainTest, GoedelConjunctWith) {
    SimdFuzzyChain<GOEDEL> a;
    SimdFuzzyChain<GOEDEL> b;

    for (int j = 0; j < 100; j++) {
        for (double i = 0.0; i <= 1.0; i += 0.1)
            a.pushBack(i);

        for (double i = 1.0; i >= 0.0; i -= 0.1)
            if (i < 0.001)
                b.pushBack(0.0);
            else
                b.pushBack(i);
    }

    a.conjunctWith(b);

    for (int j = 0; j < 100; j++) {
        EXPECT_FLOAT_EQ(a.at(11*j + 0), 0.0);
        EXPECT_FLOAT_EQ(a.at(11*j + 1), 0.1);
        EXPECT_FLOAT_EQ(a.at(11*j + 2), 0.2);
        EXPECT_FLOAT_EQ(a.at(11*j + 3), 0.3);
        EXPECT_FLOAT_EQ(a.at(11*j + 4), 0.4);
        EXPECT_FLOAT_EQ(a.at(11*j + 5), 0.5);
        EXPECT_FLOAT_EQ(a.at(11*j + 6), 0.4);
        EXPECT_FLOAT_EQ(a.at(11*j + 7), 0.3);
        EXPECT_FLOAT_EQ(a.at(11*j + 8), 0.2);
        EXPECT_FLOAT_EQ(a.at(11*j + 9), 0.1);
        EXPECT_FLOAT_EQ(a.at(11*j + 10), 0.0);
    }
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

TEST(SimdFuzzyChainTest, GoguenConjunctWith) {
    SimdFuzzyChain<GOGUEN> a;
    SimdFuzzyChain<GOGUEN> b;

    for (int j = 0; j < 1; j++) {
        for (double i = 0.0; i <= 1.0; i += 0.2)
            a.pushBack(i);

        for (double i = 0.0; i < 1.0; i += 0.2)
            a.pushBack(0.9);

        for (double i = 1.0; i >= 0.0; i -= 0.1)
            if (i < 0.001)
                b.pushBack(0.0);
            else
                b.pushBack(i);
    }

    a.conjunctWith(b);

    for (int j = 0; j < 1; j++) {
        EXPECT_FLOAT_EQ(a.at(11*j + 0), 0.0 * 1.0); // 0.0 and 1.0
        EXPECT_FLOAT_EQ(a.at(11*j + 1), 0.2 * 0.9); // 0.2 and 0.9
        EXPECT_FLOAT_EQ(a.at(11*j + 2), 0.4 * 0.8); // 0.4 and 0.8
        EXPECT_FLOAT_EQ(a.at(11*j + 3), 0.6 * 0.7); // 0.6 and 0.7
        EXPECT_FLOAT_EQ(a.at(11*j + 4), 0.8 * 0.6); // 0.8 and 0.6
        EXPECT_FLOAT_EQ(a.at(11*j + 5), 1.0 * 0.5); // 1.0 and 0.5
        EXPECT_FLOAT_EQ(a.at(11*j + 6), 0.9 * 0.4); // 0.9 and 0.4
        EXPECT_FLOAT_EQ(a.at(11*j + 7), 0.9 * 0.3); // 0.9 and 0.3
        EXPECT_FLOAT_EQ(a.at(11*j + 8), 0.9 * 0.2); // 0.9 and 0.2
        EXPECT_FLOAT_EQ(a.at(11*j + 9), 0.9 * 0.1); // 0.9 and 0.1
        EXPECT_FLOAT_EQ(a.at(11*j + 10), 0.9 * 0.0); // 0.9 and 0.0
    }
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

TEST(SimdFuzzyChainTest, LukasiewiczConjunctWith) {
    SimdFuzzyChain<LUKASIEWICZ> a;
    SimdFuzzyChain<LUKASIEWICZ> b;

    for (int j = 0; j < 1; j++) {
        for (double i = 0.0; i <= 1.0; i += 0.2)
            a.pushBack(i);

        for (double i = 0.0; i < 1.0; i += 0.2)
            a.pushBack(0.9);

        for (double i = 1.0; i >= 0.0; i -= 0.1)
            if (i < 0.001)
                b.pushBack(0.0);
            else
                b.pushBack(i);
    }

    a.conjunctWith(b);

    for (int j = 0; j < 1; j++) {
        EXPECT_FLOAT_EQ(a.at(11*j + 0), 0.0); // 0.0 and 1.0
        EXPECT_FLOAT_EQ(a.at(11*j + 1), 0.1); // 0.2 and 0.9
        EXPECT_FLOAT_EQ(a.at(11*j + 2), 0.2); // 0.4 and 0.8
        EXPECT_FLOAT_EQ(a.at(11*j + 3), 0.3); // 0.6 and 0.7
        EXPECT_FLOAT_EQ(a.at(11*j + 4), 0.4); // 0.8 and 0.6
        EXPECT_FLOAT_EQ(a.at(11*j + 5), 0.5); // 1.0 and 0.5
        EXPECT_FLOAT_EQ(a.at(11*j + 6), 0.3); // 0.9 and 0.4
        EXPECT_FLOAT_EQ(a.at(11*j + 7), 0.2); // 0.9 and 0.3
        EXPECT_FLOAT_EQ(a.at(11*j + 8), 0.1); // 0.9 and 0.2
        EXPECT_FLOAT_EQ(a.at(11*j + 9), 0.0); // 0.9 and 0.1
        EXPECT_FLOAT_EQ(a.at(11*j + 10), 0.0); // 0.9 and 0.0
    }
}
