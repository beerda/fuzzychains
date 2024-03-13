#include <benchmark/benchmark.h>
#include "BitwiseFuzzyChain.h"
#include "VectorFuzzyChain.h"

#define LENGTH 1 << 20

template<TNorm TNORM>
class BitwiseFuzzyChainFixture : public benchmark::Fixture {
public:
    BitwiseFuzzyChain<TNORM> ch1;
    BitwiseFuzzyChain<TNORM> ch2;
    float result = 0.0;

    void SetUp(::benchmark::State& state)
    {
        srand(1234);
        for (size_t i = 0; i < LENGTH; i++) {
            ch1.pushBack(1.0 * rand() / RAND_MAX);
            ch2.pushBack(1.0 * rand() / RAND_MAX);
        }
    }

    void TearDown(::benchmark::State& state)
    { }
};

template<TNorm TNORM>
class VectorFuzzyChainFixture : public benchmark::Fixture {
public:
    VectorFuzzyChain<TNORM> ch1;
    VectorFuzzyChain<TNORM> ch2;
    float result = 0.0;

    void SetUp(::benchmark::State& state)
    {
        srand(1234);
        for (size_t i = 0; i < LENGTH; i++) {
            ch1.pushBack(1.0 * rand() / RAND_MAX);
            ch2.pushBack(1.0 * rand() / RAND_MAX);
        }
    }

    void TearDown(::benchmark::State& state)
    { }
};


BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelConjunct, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoedelConjunct, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelSum, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoedelSum, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenConjunct, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoguenConjunct, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenSum, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoguenSum, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczConjunct, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, LukasiewiczConjunct, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczSum, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, LukasiewiczSum, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}



BENCHMARK_MAIN();
