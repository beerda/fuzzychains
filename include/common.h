#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "AlignedAllocator.h"

using namespace std;

// fast ceiling of positive numbers
// see: http://stackoverflow.com/questions/2745074/fast-ceiling-of-an-integer-division-in-c-c
#define UNSIGNED_CEILING(a, b)  ((a) + (b) - 1) / (b)

enum TNorm {
    GOEDEL,
    GOGUEN,
    LUKASIEWICZ
};

template <typename TYPE>
using AlignedVector = vector<TYPE, AlignedAllocator<TYPE, 512>>;
