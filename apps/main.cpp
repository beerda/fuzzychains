#include <benchmark/benchmark.h>
#include "BitwiseFuzzyChain.h"
#include "SimdFuzzyChain.h"
#include "VectorFuzzyChain.h"

#define LENGTH 16777216  // 2^24
//#define LENGTH 65536

template<unsigned int BLSIZE, TNorm TNORM>
class BitwiseFuzzyChainFixture : public benchmark::Fixture {
public:
    BitwiseFuzzyChain<BLSIZE, TNORM> ch1;
    BitwiseFuzzyChain<BLSIZE, TNORM> ch2;
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
    {
        ch1.clear();
        ch2.clear();
    }
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

template<TNorm TNORM>
class SimdFuzzyChainFixture : public benchmark::Fixture {
public:
    SimdFuzzyChain<TNORM> ch1;
    SimdFuzzyChain<TNORM> ch2;
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

#define BENCHMARK_BITWISE_CONJUNCTION(name, blsize, tnorm) BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, name, blsize, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            ch1.conjunctWith(ch2);    \
        }                             \
    }

#define BENCHMARK_VECTOR_CONJUNCTION(name, tnorm) BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, name, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            ch1.conjunctWith(ch2);    \
        }                             \
    }

#define BENCHMARK_SIMD_CONJUNCTION(name, tnorm) BENCHMARK_TEMPLATE_F(SimdFuzzyChainFixture, name, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            ch1.conjunctWith(ch2);    \
        }                             \
    }

#define BENCHMARK_BITWISE_SUM(name, blsize, tnorm) BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, name, blsize, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            result += ch1.sum();      \
        }                             \
    }

#define BENCHMARK_VECTOR_SUM(name, tnorm) BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, name, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            result += ch1.sum();      \
        }                             \
    }

#define BENCHMARK_SIMD_SUM(name, tnorm) BENCHMARK_TEMPLATE_F(SimdFuzzyChainFixture, name, tnorm)(benchmark::State& st) \
    {                                 \
        for (auto _ : st) {           \
            result += ch1.sum();      \
        }                             \
    }

BENCHMARK_BITWISE_CONJUNCTION(GoguenConjunct4, 4, TNorm::GOGUEN)
BENCHMARK_BITWISE_CONJUNCTION(LukasiewiczConjunct4, 4, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_CONJUNCTION(GoedelConjunct4, 4, TNorm::GOEDEL)

BENCHMARK_BITWISE_CONJUNCTION(GoguenConjunct8, 8, TNorm::GOGUEN)
BENCHMARK_BITWISE_CONJUNCTION(LukasiewiczConjunct8, 8, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_CONJUNCTION(GoedelConjunct8, 8, TNorm::GOEDEL)

BENCHMARK_BITWISE_CONJUNCTION(GoguenConjunct16, 16, TNorm::GOGUEN)
BENCHMARK_BITWISE_CONJUNCTION(LukasiewiczConjunct16, 16, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_CONJUNCTION(GoedelConjunct16, 16, TNorm::GOEDEL)

BENCHMARK_VECTOR_CONJUNCTION(GoguenConjunct, TNorm::GOGUEN)
BENCHMARK_VECTOR_CONJUNCTION(LukasiewiczConjunct, TNorm::LUKASIEWICZ)
BENCHMARK_VECTOR_CONJUNCTION(GoedelConjunct, TNorm::GOEDEL)

BENCHMARK_SIMD_CONJUNCTION(GoguenConjunct, TNorm::GOGUEN)
BENCHMARK_SIMD_CONJUNCTION(LukasiewiczConjunct, TNorm::LUKASIEWICZ)
BENCHMARK_SIMD_CONJUNCTION(GoedelConjunct, TNorm::GOEDEL)

BENCHMARK_BITWISE_SUM(GoguenSum4, 4, TNorm::GOGUEN)
BENCHMARK_BITWISE_SUM(LukasiewiczSum4, 4, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_SUM(GoedelSum4, 4, TNorm::GOEDEL)

BENCHMARK_BITWISE_SUM(GoguenSum8, 8, TNorm::GOGUEN)
BENCHMARK_BITWISE_SUM(LukasiewiczSum8, 8, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_SUM(GoedelSum8, 8, TNorm::GOEDEL)

BENCHMARK_BITWISE_SUM(GoguenSum16, 16, TNorm::GOGUEN)
BENCHMARK_BITWISE_SUM(LukasiewiczSum16, 16, TNorm::LUKASIEWICZ)
BENCHMARK_BITWISE_SUM(GoedelSum16, 16, TNorm::GOEDEL)

BENCHMARK_VECTOR_SUM(GoguenSum, TNorm::GOGUEN)
BENCHMARK_VECTOR_SUM(LukasiewiczSum, TNorm::LUKASIEWICZ)
BENCHMARK_VECTOR_SUM(GoedelSum, TNorm::GOEDEL)

BENCHMARK_SIMD_SUM(GoguenSum, TNorm::GOGUEN)
BENCHMARK_SIMD_SUM(LukasiewiczSum, TNorm::LUKASIEWICZ)
BENCHMARK_SIMD_SUM(GoedelSum, TNorm::GOEDEL)

BENCHMARK_MAIN();
