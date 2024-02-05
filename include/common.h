#pragma once

#include <cmath>

using namespace std;


// fast ceiling of positive numbers
// see: http://stackoverflow.com/questions/2745074/fast-ceiling-of-an-integer-division-in-c-c
#define CEILING(a, b)  ((a) + (b) - 1) / (b)

#define EQUAL(a, b)    (fabs((a) - (b)) < 1e-6)

enum TNorm {
    GOEDEL,
    GOGUEN,
    LUKASIEWICZ
};
