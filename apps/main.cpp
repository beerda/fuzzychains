#include <benchmark/benchmark.h>
#include "BitwiseFuzzyChain.h"
#include "VectorFuzzyChain.h"

#define LENGTH 1 << 24
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
        /*
        std::cout << "real size: " << ch1.getMutableData().size()
            << " data size: " << ch1.size()
            << " block size: " << ch1.BLOCK_SIZE << ":" << BLSIZE << std::endl;
            */
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


BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenConjunct4, 4, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczConjunct4, 4, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelConjunct4, 4, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenConjunct8, 8, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczConjunct8, 8, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelConjunct8, 8, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoguenConjunct, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, LukasiewiczConjunct, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoedelConjunct, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        ch1.conjunctWith(ch2);
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenSum4, 4, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczSum4, 4, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelSum4, 4, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoguenSum8, 8, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, LukasiewiczSum8, 8, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(BitwiseFuzzyChainFixture, GoedelSum8, 8, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoguenSum, TNorm::GOGUEN)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, LukasiewiczSum, TNorm::LUKASIEWICZ)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}

BENCHMARK_TEMPLATE_F(VectorFuzzyChainFixture, GoedelSum, TNorm::GOEDEL)(benchmark::State& st) {
    for (auto _ : st) {
        result += ch1.sum();
    }
}



BENCHMARK_MAIN();
