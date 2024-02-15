#include "BitwiseFuzzyChain.h"


// ----- GOEDEL ---------------------------------------------------------------
template <>
void BitwiseFuzzyChain<TNorm::GOEDEL>::pushBack(float value)
{ internalPushBack((uintmax_t) (value * MAX_VALUE)); }

template <>
float BitwiseFuzzyChain<TNorm::GOEDEL>::at(size_t pos) const
{ return 1.0 * internalAt(pos) / MAX_VALUE; }

template <>
float BitwiseFuzzyChain<TNorm::GOEDEL>::sum() const
{ return ((float) internalSum()) / ((float) MAX_VALUE); }

template <>
void BitwiseFuzzyChain<TNorm::GOEDEL>::conjunctWith(const BitwiseFuzzyChain<TNorm::GOEDEL>& other)
{
    if (n != other.n)
        throw std::invalid_argument("BitwiseFuzzyChain<GOEDEL>::conjunctWith: incompatible sizes");

    if (BitwiseFuzzyChain<GOEDEL>::BLOCK_SIZE != 8)
        throw std::runtime_error("BitwiseFuzzyChain<GOEDEL>::conjunctWith not implemented for BLOCK_SIZE != 8");

    const uintmax_t* a = data.data();
    const uintmax_t* b = other.data.data();
    vector<uintmax_t> res = data;

    for (size_t i = 0; i < data.size() - 1; i++) {
        uintmax_t s = internalCloneBits(a[i] - b[i]);
        res[i] = (a[i] & s) | (b[i] & ~s);
    }

    data = res;
}


// ----- LUKASIEWICZ ----------------------------------------------------------
template <>
void BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::pushBack(float value)
{ internalPushBack((uintmax_t) ((1.0 - value) * MAX_VALUE)); }

template <>
float BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::at(size_t pos) const
{ return 1.0 - 1.0 * internalAt(pos) / MAX_VALUE; }

template <>
float BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::sum() const
{ return size() - ((float) internalSum()) / ((float) MAX_VALUE); }

template <>
void BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::conjunctWith(const BitwiseFuzzyChain<TNorm::LUKASIEWICZ>& other)
{
    if (n != other.n)
        throw std::invalid_argument("BitwiseFuzzyChain<LUKASIEWICZ>::conjunctWith: incompatible sizes");

    if (BitwiseFuzzyChain<LUKASIEWICZ>::BLOCK_SIZE != 8)
        throw std::runtime_error("BitwiseFuzzyChain<LUKASIEWICZ>::conjunctWith not implemented for BLOCK_SIZE != 8");

    const uintmax_t* a = data.data();
    const uintmax_t* b = other.data.data();
    vector<uintmax_t> res = data;
    uintmax_t themask;
    for (size_t i = 0; i < data.size() - 1; i++) {
        uintmax_t sum = (a[i] + b[i]);
        uintmax_t s = internalCloneBits(sum);
        res[i] = (sum | s) & negOverflowMask;
    }

    data = res;
}


// ----- GOGUEN ---------------------------------------------------------------
template <>
const float BitwiseFuzzyChain<TNorm::GOGUEN>::LOG_BASE = pow(1.0 * MAX_VALUE, (-1.0) / (MAX_VALUE - 1));

template <>
void BitwiseFuzzyChain<TNorm::GOGUEN>::pushBack(float value)
{
    static float reciprocal = 1.0 / MAX_VALUE;
    static float logLogBase = log(LOG_BASE);

    internalPushBack((value <= reciprocal) ? MAX_VALUE : round(log(value) / logLogBase));
}

template <>
float BitwiseFuzzyChain<TNorm::GOGUEN>::at(size_t pos) const
{
    uintmax_t val = internalAt(pos);

    return (val >= MAX_VALUE) ? 0.0 : pow(LOG_BASE, val);
}

template <>
float BitwiseFuzzyChain<TNorm::GOGUEN>::sum() const
{
    float result = 0.0;
    for (size_t i = 0; i < size(); ++i)
        result += at(i);

    return result;
}

template <>
void BitwiseFuzzyChain<TNorm::GOGUEN>::conjunctWith(const BitwiseFuzzyChain<TNorm::GOGUEN>& other)
{
    if (n != other.n)
        throw std::invalid_argument("BitwiseFuzzyChain<GOGUEN>::conjunctWith: incompatible sizes");

    if (BitwiseFuzzyChain<GOGUEN>::BLOCK_SIZE != 8)
        throw std::runtime_error("BitwiseFuzzyChain<GOGUEN>::conjunctWith not implemented for BLOCK_SIZE != 8");

    const uintmax_t* a = data.data();
    const uintmax_t* b = other.data.data();
    vector<uintmax_t> res = data;
    uintmax_t themask;
    for (size_t i = 0; i < data.size() - 1; i++) {
        uintmax_t sum = (a[i] + b[i]);
        uintmax_t s = internalCloneBits(sum);
        res[i] = (sum | s) & negOverflowMask;
    }

    data = res;
}
