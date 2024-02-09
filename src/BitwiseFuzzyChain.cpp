#include "BitwiseFuzzyChain.h"

// ----- GOEDEL ---------------------------------------------------------------
template <>
void BitwiseFuzzyChain<TNorm::GOEDEL>::pushBack(float value)
{ internalPushBack(value); }

template <>
float BitwiseFuzzyChain<TNorm::GOEDEL>::at(size_t pos) const
{ return internalAt(pos); }

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
        res[i] = (a[i] - b[i]) & overflowMask;
        res[i] = res[i] | (res[i] >> 1);
        res[i] = res[i] | (res[i] >> 2);
        res[i] = res[i] | (res[i] >> 4);
        res[i] = (a[i] & res[i]) | (b[i] & ~(res[i]));
    }

    data = res;
}


// ----- LUKASIEWICZ ----------------------------------------------------------
template <>
void BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::pushBack(float value)
{ internalPushBack(1.0 - value); }

template <>
float BitwiseFuzzyChain<TNorm::LUKASIEWICZ>::at(size_t pos) const
{ return 1.0 - internalAt(pos); }

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
        res[i] = (a[i] + b[i]);
        themask = res[i] & overflowMask;
        themask = themask | (themask >> 1);
        themask = themask | (themask >> 2);
        themask = themask | (themask >> 4);
        res[i] = (res[i] | themask) & negOverflowMask;
    }

    data = res;
}


// ----- GOGUEN ---------------------------------------------------------------
template <>
void BitwiseFuzzyChain<TNorm::GOGUEN>::conjunctWith(const BitwiseFuzzyChain<TNorm::GOGUEN>& other)
{
    throw std::invalid_argument("unimplemented");
    if (n != other.n)
        throw std::invalid_argument("BitwiseFuzzyChain<GOGUEN>::conjunctWith: incompatible sizes");

    if (BitwiseFuzzyChain<GOGUEN>::BLOCK_SIZE != 8)
        throw std::runtime_error("BitwiseFuzzyChain<GOGUEN>::conjunctWith not implemented for BLOCK_SIZE != 8");
}
