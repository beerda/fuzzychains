#pragma once

#include <vector>
#include <cmath>
#include <iostream>

#include "common.h"


template <TNorm TNORM>
class VectorFuzzyChain {
public:
    VectorFuzzyChain()
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

    void conjunctWith(const VectorFuzzyChain& other);

    bool operator == (const VectorFuzzyChain& other) const
    { return data == other.data; }

    bool operator != (const VectorFuzzyChain& other) const
    { return !(*this == other); }

private:
    vector<float> data;
};
