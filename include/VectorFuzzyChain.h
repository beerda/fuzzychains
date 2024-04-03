#pragma once

#include <algorithm>

#include "common.h"


template <TNorm TNORM>
class VectorFuzzyChainBase {
public:
    VectorFuzzyChainBase()
        : data()
    { }

    void clear()
    { data.clear(); }

    void reserve(size_t capacity)
    { data.reserve(capacity); }

    size_t size() const
    { return data.size(); }

    bool empty() const
    { return data.empty(); }

    void pushBack(float value)
    { data.push_back(value); }

    float at(size_t pos) const
    { return data.at(pos); }

    float sum() const
    {
        float res = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            res += data.at(i);
        }

        return res;
    }

    void conjunctWith(const VectorFuzzyChainBase& other);

    bool operator == (const VectorFuzzyChainBase& other) const
    { return data == other.data; }

    bool operator != (const VectorFuzzyChainBase& other) const
    { return !(*this == other); }

protected:
    AlignedVector<float> data;
};


template <TNorm TNORM>
class VectorFuzzyChain : public VectorFuzzyChainBase<TNORM> {
};


template <>
class VectorFuzzyChain<TNorm::GOEDEL> : public VectorFuzzyChainBase<TNorm::GOEDEL> {
public:
    void conjunctWith(const VectorFuzzyChain<TNorm::GOEDEL>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("VectorFuzzyChain<GOEDEL>::conjunctWith: incompatible sizes");

        for (size_t i = 0; i < this->data.size(); i++) {
            this->data[i] = std::min(this->data[i], other.data[i]);
        }
    }
};


template <>
class VectorFuzzyChain<TNorm::LUKASIEWICZ> : public VectorFuzzyChainBase<TNorm::LUKASIEWICZ> {
public:
    void conjunctWith(const VectorFuzzyChain<TNorm::LUKASIEWICZ>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("VectorFuzzyChain<LUKASIEWICZ>::conjunctWith: incompatible sizes");

        for (size_t i = 0; i < this->data.size(); i++) {
            this->data[i] += other.data[i] - 1.0;
            if (this->data[i] < 0.0)
                this->data[i] = 0;
        }
    }
};


template <>
class VectorFuzzyChain<TNorm::GOGUEN> : public VectorFuzzyChainBase<TNorm::GOGUEN> {
public:
    void conjunctWith(const VectorFuzzyChain<TNorm::GOGUEN>& other)
    {
        if (this->size() != other.size())
            throw std::invalid_argument("VectorFuzzyChain<GOGUEN>::conjunctWith: incompatible sizes");

        for (size_t i = 0; i < this->data.size(); i++) {
            this->data[i] = this->data[i] * other.data[i];
        }
    }
};
