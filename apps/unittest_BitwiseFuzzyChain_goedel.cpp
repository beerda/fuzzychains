#include <gtest/gtest.h>
#include "BitwiseFuzzyChain.h"

#define EXPECTED_DATA_SIZE(x) ((x-1) * BitwiseFuzzyChain<8, GOEDEL>::BLOCK_SIZE / BitwiseFuzzyChain<8, GOEDEL>::INTEGER_SIZE + 1)
#define EQUAL(a, b) (fabs((a) - (b)) < 1e-6)


TEST(GoedelBitwiseFuzzyChainTest, PushBackAndSum) {
    BitwiseFuzzyChain<8, GOEDEL> b;

    EXPECT_TRUE(b.empty());
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.sum() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 0);

    b.pushBack(0.5);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 1);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.sum(), 0.496063));
    EXPECT_TRUE(b.getMutableData().size() == 1);

    b.pushBack(0.1);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 2);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.sum(), 0.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(0.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 3);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 0.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 4);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 1.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 5);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(4), 1.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 2.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 6);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(4), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(5), 1.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 3.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(0.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 7);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(4), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(5), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(6), 0.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 3.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 8);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(4), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(5), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(6), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(7), 1.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 4.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));

    b.pushBack(1.0);
    EXPECT_TRUE(!b.empty());
    EXPECT_TRUE(b.size() == 9);
    EXPECT_TRUE(EQUAL(b.at(0), 0.496063));
    EXPECT_TRUE(EQUAL(b.at(1), 0.094488));
    EXPECT_TRUE(EQUAL(b.at(2), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(3), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(4), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(5), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(6), 0.000000));
    EXPECT_TRUE(EQUAL(b.at(7), 1.000000));
    EXPECT_TRUE(EQUAL(b.at(8), 1.000000));
    EXPECT_TRUE(EQUAL(b.sum(), 5.5905512));
    EXPECT_TRUE(b.getMutableData().size() == EXPECTED_DATA_SIZE(b.size()));
}

TEST(GoedelBitwiseFuzzyChainTest, Reserve) {
    size_t inBlock = BitwiseFuzzyChain<8, GOEDEL>::INTEGER_SIZE / BitwiseFuzzyChain<8, GOEDEL>::BLOCK_SIZE;
    BitwiseFuzzyChain<8, GOEDEL> b;

    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 0);
    EXPECT_TRUE(b.getMutableData().capacity() == 0);

    b.reserve(inBlock * 2);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 0);
    EXPECT_TRUE(b.getMutableData().capacity() == 2);

    b.reserve(inBlock * 5);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 0);
    EXPECT_TRUE(b.getMutableData().capacity() == 5);

    b.reserve(inBlock * 5 + 1);
    EXPECT_TRUE(b.size() == 0);
    EXPECT_TRUE(b.getMutableData().size() == 0);
    EXPECT_TRUE(b.getMutableData().capacity() == 6);
}

TEST(GoedelBitwiseFuzzyChainTest, ConjunctWith) {
    BitwiseFuzzyChain<8, GOEDEL> a;
    BitwiseFuzzyChain<8, GOEDEL> b;

    for (int j = 0; j < 100; j++) {
        for (double i = 0.0; i <= 1.0; i += 0.1)
            a.pushBack(i);

        for (double i = 1.0; i >= 0.0; i -= 0.1)
            b.pushBack(i);
    }

    a.conjunctWith(b);

    for (int j = 0; j < 100; j++) {
        EXPECT_TRUE(EQUAL(a.at(11*j + 0), 0.000000));
        EXPECT_TRUE(EQUAL(a.at(11*j + 1), 0.094488));
        EXPECT_TRUE(EQUAL(a.at(11*j + 2), 0.1968504));
        EXPECT_TRUE(EQUAL(a.at(11*j + 3), 0.2992126));
        EXPECT_TRUE(EQUAL(a.at(11*j + 4), 0.3937008));
        EXPECT_TRUE(EQUAL(a.at(11*j + 5), 0.496063));
        EXPECT_TRUE(EQUAL(a.at(11*j + 6), 0.3937008));
        EXPECT_TRUE(EQUAL(a.at(11*j + 7), 0.2992126));
        EXPECT_TRUE(EQUAL(a.at(11*j + 8), 0.1968504));
        EXPECT_TRUE(EQUAL(a.at(11*j + 9), 0.094488));
        EXPECT_TRUE(EQUAL(a.at(11*j + 10), 0.000000));
    }
}

template <unsigned int N>
class MockFuzzyChain : public BitwiseFuzzyChain<N, GOEDEL>
{
public:
    void pushBack(uintmax_t v) {
        this->internalPushBack(v);
    }

    uintmax_t sum() const
    { return this->internalSum(); }
};

TEST(GoedelBitwiseFuzzyChainTest, SumALot) {
    MockFuzzyChain<4> b4;
    MockFuzzyChain<8> b8;

    size_t n = b8.STEP * b8.N_BLOCK * 2 + 1;
    for (size_t i = 0; i < n; ++i) {
        b4.pushBack(b4.MAX_VALUE);
        b8.pushBack(b8.MAX_VALUE);
    }

    /*
    cout << "step=" << b.STEP << " sum=" << b.sum() << " maxval=" << b.MAX_VALUE << " n=" << n
         << " dblblock=" << b.DBL_BLOCK_MASK << " nblock=" << b.N_BLOCK << endl;
         */

    EXPECT_TRUE(b4.sum() == n * b4.MAX_VALUE);
    EXPECT_TRUE(b8.sum() == n * b8.MAX_VALUE);
}
