#include <gtest/gtest.h>
#include "BitwiseFuzzyChain.h"

#define EXPECTED_DATA_SIZE(x) ((x-1) * BitwiseFuzzyChain<LUKASIEWICZ>::BLOCK_SIZE / BitwiseFuzzyChain<LUKASIEWICZ>::INTEGER_SIZE + 2)
#define EQUAL(a, b) (fabs((a) - (b)) < 1e-6)


TEST(LukasiewiczBitwiseFuzzyChainTest, PushBackAndSum) {
    BitwiseFuzzyChain<LUKASIEWICZ> b;

    EXPECT_TRUE(b.empty());
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.sum() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 1);
    EXPECT_TRUE(b.getMutableData().back() == 0UL);

    b.pushBack(0.5);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 1);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.sum(), 0.503937));
    EXPECT_TRUE(b.getMutableData().size() == 2);

    b.pushBack(0.1);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 2);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.sum(), 0.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(0.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 3);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.sum(), 0.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 4);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.sum(), 1.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 5);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.at(4), 1.0));
    EXPECT_TRUE(EQUAL(b.sum(), 2.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 6);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.at(4), 1.0));
    EXPECT_TRUE(EQUAL(b.at(5), 1.0));
    EXPECT_TRUE(EQUAL(b.sum(), 3.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(0.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 7);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.at(4), 1.0));
    EXPECT_TRUE(EQUAL(b.at(5), 1.0));
    EXPECT_TRUE(EQUAL(b.at(6), 0.0));
    EXPECT_TRUE(EQUAL(b.sum(), 3.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 8);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.at(4), 1.0));
    EXPECT_TRUE(EQUAL(b.at(5), 1.0));
    EXPECT_TRUE(EQUAL(b.at(6), 0.0));
    EXPECT_TRUE(EQUAL(b.at(7), 1.0));
    EXPECT_TRUE(EQUAL(b.sum(), 4.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 9);
    EXPECT_TRUE(EQUAL(b.at(0), 0.503937));
    EXPECT_TRUE(EQUAL(b.at(1), 0.102362));
    EXPECT_TRUE(EQUAL(b.at(2), 0.0));
    EXPECT_TRUE(EQUAL(b.at(3), 1.0));
    EXPECT_TRUE(EQUAL(b.at(4), 1.0));
    EXPECT_TRUE(EQUAL(b.at(5), 1.0));
    EXPECT_TRUE(EQUAL(b.at(6), 0.0));
    EXPECT_TRUE(EQUAL(b.at(7), 1.0));
    EXPECT_TRUE(EQUAL(b.at(8), 1.0));
    EXPECT_TRUE(EQUAL(b.sum(), 5.606299));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));
}

TEST(LukasiewiczBitwiseFuzzyChainTest, Reserve) {
    size_t inBlock = BitwiseFuzzyChain<LUKASIEWICZ>::INTEGER_SIZE / BitwiseFuzzyChain<LUKASIEWICZ>::BLOCK_SIZE;
    BitwiseFuzzyChain<LUKASIEWICZ> b;

    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 1);
    EXPECT_TRUE(b.getMutableData().capacity() == 1);

    b.reserve(inBlock * 2);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 1);
    EXPECT_TRUE(b.getMutableData().capacity() == 3);

    b.reserve(inBlock * 5);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 1);
    EXPECT_TRUE(b.getMutableData().capacity() == 6);

    b.reserve(inBlock * 5 + 1);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 1);
    EXPECT_TRUE(b.getMutableData().capacity() == 7);
}

TEST(LukasiewiczBitwiseFuzzyChainTest, ConjunctWith) {
    BitwiseFuzzyChain<LUKASIEWICZ> a;
    BitwiseFuzzyChain<LUKASIEWICZ> b;

    for (int j = 0; j < 1; j++) {
        for (double i = 0.0; i <= 1.0; i += 0.2)
            a.pushBack(i);

        for (double i = 0.0; i < 1.0; i += 0.2)
            a.pushBack(0.9);

        for (double i = 1.0; i >= 0.0; i -= 0.1)
            b.pushBack(i);
    }

    a.conjunctWith(b);

    for (int j = 0; j < 1; j++) {
        EXPECT_TRUE(EQUAL(a.at(11*j + 0), 0.000000)); // 0.0 and 1.0
        EXPECT_TRUE(EQUAL(a.at(11*j + 1), 0.110236)); // 0.2 and 0.9
        EXPECT_TRUE(EQUAL(a.at(11*j + 2), 0.204724)); // 0.4 and 0.8
        EXPECT_TRUE(EQUAL(a.at(11*j + 3), 0.307087)); // 0.6 and 0.7
        EXPECT_TRUE(EQUAL(a.at(11*j + 4), 0.409449)); // 0.8 and 0.6
        EXPECT_TRUE(EQUAL(a.at(11*j + 5), 0.503937)); // 1.0 and 0.5
        EXPECT_TRUE(EQUAL(a.at(11*j + 6), 0.307087)); // 0.9 and 0.4
        EXPECT_TRUE(EQUAL(a.at(11*j + 7), 0.212598)); // 0.9 and 0.3
        EXPECT_TRUE(EQUAL(a.at(11*j + 8), 0.110236)); // 0.9 and 0.2
        EXPECT_TRUE(EQUAL(a.at(11*j + 9), 0.007874)); // 0.9 and 0.1
        EXPECT_TRUE(EQUAL(a.at(11*j + 10), 0.00000)); // 0.9 and 0.0
    }
}
