#include <array>
#include <cmath>

#include "testing.h"

template <class T>

concept Range = requires(T& t) {
    std::begin(t);
    std::end(t);
};

#define Semiring typename

template <Range I, Semiring R>
R polynomal_value(const I& range, R x) {
    auto first = std::cbegin(range);
    auto last = std::cend(range);

    if (first == last) return R(0);
    R sum(*first);
    while (++first != last) {
        sum *= x;
        sum += *first;
    }
    return sum;
}

/**
 * Requirements on R and the iterators value type T?
 * 
 * type(R) = type(T * R)
 *    (or with different return value type(T * R) = type(T))
 * type(T) = type(T + T)
 * type(R) = type(R ^ n)
 * 
 */

int main() {
    // std::array a = {3, 0, 4, -1};
    int a[] = {3, 0, 4, -1};
    test_equal("poly", polynomal_value(a, 5),
               static_cast<int>(3 * std::pow(5, 3) + 4 * 5 - 1));
}