#pragma once

#include <cmath>

using namespace std;

// fast ceiling of positive numbers
// see: http://stackoverflow.com/questions/2745074/fast-ceiling-of-an-integer-division-in-c-c
#define UNSIGNED_CEILING(a, b)  ((a) + (b) - 1) / (b)

enum TNorm {
    GOEDEL,
    GOGUEN,
    LUKASIEWICZ
};
