#pragma once

#include <immintrin.h>
#include "common.h"


template <TNorm TNORM>
class SimdFuzzyChainBase {
public:
    // number of floats that fit into the SIMD register
    constexpr static size_t N_PACKED = 8;

    SimdFuzzyChainBase()
        : data()
    { }

    void clear()
    {  data.clear(); }

    void reserve(size_t capacity)
    { data.reserve(capacity); }

    size_t size() const
    { return data.size(); }

    bool empty() const
    { return data.empty(); }

    void pushBack(float value)
    {  data.push_back(value); }

    float at(size_t pos) const
    { return data.at(pos); }

    float sum() const
    {
        __m256 sumv = _mm256_set1_ps(0.0f);

        for (size_t i = 0; i < (data.size() / N_PACKED) * N_PACKED; i += N_PACKED) {
            __m256 d = _mm256_load_ps(data.data() + i);
            sumv = _mm256_add_ps(sumv, d);
        }

        const __m128 hiQuad = _mm256_extractf128_ps(sumv, 1);
        // loQuad = ( x3, x2, x1, x0 )
        const __m128 loQuad = _mm256_castps256_ps128(sumv);
        // sumQuad = ( x3 + x7, x2 + x6, x1 + x5, x0 + x4 )
        const __m128 sumQuad = _mm_add_ps(loQuad, hiQuad);
        // loDual = ( -, -, x1 + x5, x0 + x4 )
        const __m128 loDual = sumQuad;
        // hiDual = ( -, -, x3 + x7, x2 + x6 )
        const __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
        // sumDual = ( -, -, x1 + x3 + x5 + x7, x0 + x2 + x4 + x6 )
        const __m128 sumDual = _mm_add_ps(loDual, hiDual);
        // lo = ( -, -, -, x0 + x2 + x4 + x6 )
        const __m128 lo = sumDual;
        // hi = ( -, -, -, x1 + x3 + x5 + x7 )
        const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
        // sum = ( -, -, -, x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 )
        const __m128 summ = _mm_add_ss(lo, hi);

        float res = _mm_cvtss_f32(summ);

        for (size_t i = (data.size() / N_PACKED) * N_PACKED; i < data.size(); ++i) {
            res += data.at(i);
        }

        return res;
    }

    void conjunctWith(const SimdFuzzyChainBase& other);

    bool operator == (const SimdFuzzyChainBase& other) const
    { return data == other.data; }

    bool operator != (const SimdFuzzyChainBase& other) const
    { return !(*this == other); }

protected:
    AlignedVector<float> data;
};


template <TNorm TNORM>
class SimdFuzzyChain : public SimdFuzzyChainBase<TNORM> {
};


template <>
class SimdFuzzyChain<TNorm::GOEDEL> : public SimdFuzzyChainBase<TNorm::GOEDEL> {
public:
    void conjunctWith(const SimdFuzzyChain<TNorm::GOEDEL>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("SimdFuzzyChain<GOEDEL>::conjunctWith: incompatible sizes");

        for (size_t i = 0; i < (this->size() / N_PACKED) * N_PACKED; i += N_PACKED) {
            __m256 a = _mm256_load_ps(this->data.data() + i);
            __m256 b = _mm256_load_ps(other.data.data() + i);
            __m256 res = _mm256_min_ps(a, b);
            _mm256_store_ps(this->data.data() + i, res);
        }

        for (size_t i = (data.size() / N_PACKED) * N_PACKED; i < data.size(); ++i) {
            this->data[i] = min(this->data[i], other.data[i]);
        }
    }
};


template <>
class SimdFuzzyChain<TNorm::LUKASIEWICZ> : public SimdFuzzyChainBase<TNorm::LUKASIEWICZ> {
public:
    void conjunctWith(const SimdFuzzyChain<TNorm::LUKASIEWICZ>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("SimdFuzzyChain<LUKASIEWICZ>::conjunctWith: incompatible sizes");

        __m256 zero = _mm256_set1_ps(0.0);
        __m256 one = _mm256_set1_ps(1.0);

        for (size_t i = 0; i < (this->size() / N_PACKED) * N_PACKED; i += N_PACKED) {
            __m256 a = _mm256_load_ps(this->data.data() + i);
            __m256 b = _mm256_load_ps(other.data.data() + i);
            __m256 res = _mm256_add_ps(a, b);
            res = _mm256_sub_ps(res, one);
            res = _mm256_max_ps(res, zero);
            _mm256_store_ps(this->data.data() + i, res);
        }

        for (size_t i = (data.size() / N_PACKED) * N_PACKED; i < data.size(); ++i) {
            this->data[i] += other.data[i] - 1.0;
            if (this->data[i] < 0.0)
                this->data[i] = 0;
        }
    }
};


template <>
class SimdFuzzyChain<TNorm::GOGUEN> : public SimdFuzzyChainBase<TNorm::GOGUEN> {
public:
    void conjunctWith(const SimdFuzzyChain<TNorm::GOGUEN>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("SimdFuzzyChain<GOGUEN>::conjunctWith: incompatible sizes");

        for (size_t i = 0; i < (this->size() / N_PACKED) * N_PACKED; i += N_PACKED) {
            __m256 a = _mm256_load_ps(this->data.data() + i);
            __m256 b = _mm256_load_ps(other.data.data() + i);
            __m256 res = _mm256_mul_ps(a, b);
            _mm256_store_ps(this->data.data() + i, res);
        }

        for (size_t i = (data.size() / N_PACKED) * N_PACKED; i < data.size(); ++i) {
            this->data[i] = this->data[i] * other.data[i];
        }
    }
};
