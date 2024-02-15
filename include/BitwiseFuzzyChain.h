#pragma once

#include <vector>
#include <cmath>
#include <iostream>

#include "common.h"


template <TNorm TNORM>
class BitwiseFuzzyChain {
public:
    // number of bits in a single block
    constexpr static size_t BLOCK_SIZE = 8;

    // number of bits in the whole integer
    constexpr static size_t INTEGER_SIZE = 8 * sizeof(uintmax_t);

    // maximum unsigned number to be stored in a value bits of a block
    // (the overflow bit (i.e. the hightest bit) must remain empty
    constexpr static uintmax_t MAX_VALUE = (((uintmax_t) 1) << (BLOCK_SIZE - 1)) - 1;

    // bit mask of the first block of bits within the integer
    constexpr static uintmax_t BLOCK_MASK = (((uintmax_t) 1) << BLOCK_SIZE) - 1;

    // bit mask of first two blocks of bits within the integer
    constexpr static uintmax_t DBL_BLOCK_MASK = (BLOCK_MASK << BLOCK_SIZE) + BLOCK_MASK;

    constexpr static uintmax_t STEP = ((1UL << (2 * BLOCK_SIZE)) - 1) / ((1UL << (BLOCK_SIZE - 1)) - 1) - 1;

    static const float LOG_BASE;


    BitwiseFuzzyChain()
        : data(), n(0)
    {
        data.push_back(0); // +1 to make room for shifts in sum()

        overflowMask = 1 << (BLOCK_SIZE - 1);
        for (size_t j = 1; j * BLOCK_SIZE < INTEGER_SIZE; j <<= 1) {
            overflowMask = overflowMask + (overflowMask << (j * BLOCK_SIZE));
        }
        negOverflowMask = ~overflowMask;
    }

    void clear()
    {
        data.clear();
        data.push_back(0); // +1 to make room for shifts in sum()
        n = 0;
    }

    void reserve(size_t capacity)
    {
        data.reserve(1 + UNSIGNED_CEILING(capacity * BLOCK_SIZE, INTEGER_SIZE)); // +1 to make room for shifts in sum()
    }

    size_t size() const
    { return n; }

    bool empty() const
    { return n == 0; }

    void pushBack(float value);

    float at(size_t pos) const;

    float sum() const;

    void conjunctWith(const BitwiseFuzzyChain& other);

    vector<uintmax_t>& getMutableData()
    { return data; }

    bool operator == (const BitwiseFuzzyChain& other) const
    {
        if (n != other.n)
            return false;

        return data == other.data;
    }

    bool operator != (const BitwiseFuzzyChain& other) const
    { return !(*this == other); }

private:
    vector<uintmax_t> data;
    size_t n;
    uintmax_t overflowMask;
    uintmax_t negOverflowMask;

    void internalPushBack(uintmax_t value)
    {
        size_t index = n * BLOCK_SIZE / INTEGER_SIZE;
        size_t shift = n * BLOCK_SIZE % INTEGER_SIZE;

        if (index == data.size() - 1) {
            // always need to have reserved +1 integer for shifts in sum()
            data.push_back(0);
        }

        data[index] |= value << shift;
        n++;
    }

    uintmax_t internalAt(size_t pos) const
    {
        if (pos >= n) {
            throw std::out_of_range("BitwiseFuzzyChain::at");
        }

        size_t index = pos * BLOCK_SIZE / INTEGER_SIZE;
        size_t shift = pos * BLOCK_SIZE % INTEGER_SIZE;

        //cout << endl << "index: " << index << ", shift: " << shift << ", data: " << data[index] << endl;
        //cout << "chunkmask: " << BLOCK_MASK << ", result: " << ((data[index] >> shift) & BLOCK_MASK) << endl;
        return 1.0 * ((data[index] >> shift) & BLOCK_MASK);
    }

    uintmax_t internalCloneBits(uintmax_t value) const
    {
        uintmax_t res = value & overflowMask;
        res = res | (res >> 1);
        res = res | (res >> 2);
        res = res | (res >> 4);

        return res;
    }

    uintmax_t internalSum() const
    {
        // TODO: as constant
        uintmax_t mask = BLOCK_MASK;
        for (size_t shift = 1; shift < INTEGER_SIZE / 2; shift += BLOCK_SIZE) {
            mask = (mask << (2 * BLOCK_SIZE)) + BLOCK_MASK;
        }

        uintmax_t result = 0;
        uintmax_t tempOdd = 0;
        uintmax_t tempEven = 0;
        const uintmax_t* oddChain = data.data();
        const uintmax_t* evenChain = (uintmax_t*) (((uint8_t*) data.data()) + (BLOCK_SIZE / 8));

        size_t index = 0;
        while (index < data.size() - 1) {
            tempOdd = 0;
            tempEven = 0;

            size_t border;
            if (data.size() - 1 > index + STEP) {
                border = index + STEP;
            } else {
                border = data.size() - 1;
            }

            //TODO: mozna se to zrychli, kdyz ten for cyklus rozdelim na dva (intrinsics optimalizace)
            for (; index < border; index++) {
                tempOdd += oddChain[index] & mask;
                tempEven += evenChain[index] & mask;
            }
            for (size_t shift = 0; shift < INTEGER_SIZE; shift += 2 * BLOCK_SIZE) {
                result += (tempOdd >> shift) & DBL_BLOCK_MASK;
                result += (tempEven >> shift) & DBL_BLOCK_MASK;
            }
        }

        return result;
    }
};
