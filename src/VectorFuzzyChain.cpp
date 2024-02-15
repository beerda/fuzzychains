#include "VectorFuzzyChain.h"


// ----- GOEDEL ---------------------------------------------------------------
template <>
void VectorFuzzyChain<TNorm::GOEDEL>::conjunctWith(const VectorFuzzyChain<TNorm::GOEDEL>& other)
{
    if (size() != other.size())
        throw std::invalid_argument("VectorFuzzyChain<GOEDEL>::conjunctWith: incompatible sizes");

    for (size_t i = 0; i < data.size(); i++) {
        data[i] = min(data[i], other.data[i]);
    }
}


// ----- LUKASIEWICZ ----------------------------------------------------------
template <>
void VectorFuzzyChain<TNorm::LUKASIEWICZ>::conjunctWith(const VectorFuzzyChain<TNorm::LUKASIEWICZ>& other)
{
    if (size() != other.size())
        throw std::invalid_argument("VectorFuzzyChain<LUKASIEWICZ>::conjunctWith: incompatible sizes");

    for (size_t i = 0; i < data.size(); i++) {
        data[i] += other.data[i] - 1.0;
        if (data[i] < 0.0)
            data[i] = 0;
    }
}


// ----- GOGUEN ---------------------------------------------------------------
template <>
void VectorFuzzyChain<TNorm::GOGUEN>::conjunctWith(const VectorFuzzyChain<TNorm::GOGUEN>& other)
{
    if (size() != other.size())
        throw std::invalid_argument("VectorFuzzyChain<GOGUEN>::conjunctWith: incompatible sizes");

    for (size_t i = 0; i < data.size(); i++) {
        data[i] = data[i] * other.data[i];
    }
}
