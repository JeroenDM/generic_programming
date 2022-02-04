#include "fmt/core.h"
#include "testing.h"

template <typename T>
T remainder(T a, T b) {
    // precondition: a >= 0, b > 0
    while (b <= a) a = a - b;
    return a;
}

template <typename T>
T gdm_recurse(T a, T b) {
    if (a > b) return gdm_recurse(a - b, b);
    if (a < b) return gdm_recurse(a, b - a);
    return a;
}

template <typename T>
T gdm(T a, T b) {
    while (a != b) {
        while (a > b) a = a - b;
        std::swap(a, b);
    }
    return a;
}

template <typename T>
T gdm_with_zero(T a, T b) {
    while (b != T{0}) {
        a = remainder(a, b);
        std::swap(a, b);
    }
    return a;
}

// template <typename T>
// T gdm(T a, T b) {
//     while (b != 0) {
//         a = a % b;
//         std::swap(a, b);
//     }
//     return a;
// }

int main() {
    test_equal("220 / 10 ", remainder(220, 10), 0);
    test_equal("10 / 3 ", remainder(10, 3), 1);
    test_equal("233 / 20 ", remainder(233, 20), 13);

    test_equal("220, 10 ", gdm_recurse(220, 10), 10);
    test_equal("12, 3 ", gdm_recurse(12, 3), 3);
    test_equal("25, 75 ", gdm_recurse(25, 75), 25);

    test_equal("220, 10 ", gdm(220, 10), 10);
    test_equal("12, 3 ", gdm(12, 3), 3);
    test_equal("25, 75 ", gdm(25, 75), 25);

    test_equal("220, 10 ", gdm_with_zero(220, 10), 10);
    test_equal("12, 3 ", gdm_with_zero(12, 3), 3);
    test_equal("25, 75 ", gdm_with_zero(25, 75), 25);
}