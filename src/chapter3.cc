#include <cmath>
#include <concepts>
#include <iterator>
#include <vector>

#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/format.h"
#include "testing.h"

inline int sqrt_floor(int x) {
    return static_cast<int>(std::floor(std::sqrt(x)));
}

// void mark_sieve_one(std::vector<bool>& s, int idx) {
//     int factor = 2 * idx + 3;
//     size_t i = (factor * factor - 3) / 2;
//     while (i < s.size()) {
//         s[i] = false;
//         i = i + factor;
//     }
// }

#define RandomAccessIterator std::random_access_iterator
#define Integer std::integral

// Assume first points the first value we need to check.
template <RandomAccessIterator I, Integer N>
void mark_sieve_one(I first, I last, N factor) {
    fmt::print("factor: {}\n", factor);
    do {
        *first = false;
        first = first + factor;
    } while (std::distance(first, last) > factor);
}

template <RandomAccessIterator I, Integer N>
void mark_sieve(I first, N n) {
    std::fill_n(first, n, true);
    int i_max = (sqrt_floor(n) - 3) / 2;
    for (int i = 0; i <= i_max; ++i) {
        int two_i = i + i;
        int factor = two_i + 3;
        int offset = two_i * (i + 3) + 3;
        mark_sieve_one(first + offset, first + n, factor);
    }
}

// void mark_sieve(std::vector<bool>& s, int n) {
//     int d_max = sqrt_floor(n);
//     int d = 0;
//     int i = 0;
//     while (true) {
//         d = 3 + 2 * i;
//         if (d > d_max) break;

//         int d2 = 0;
//         int i2 = i + d;
//         while (true) {
//             d2 = 3 + 2 * i2;
//             fmt::print("d, d2: {}, {} {}\n", d, d2, d2 % d == 0);
//             if (d2 > n) break;
//             if (d2 % d == 0) s[i2] = false;
//             i2 = i2 + 1;
//         }

//         i = i + 1;
//     }
// }

void print_primes(const std::vector<bool>& sieve) {
    for (size_t i = 0; i < sieve.size(); ++i) {
        int n = 3 + 2 * i;
        auto color = fmt::color::red;
        if (sieve[i] == true) color = fmt::color::green;
        fmt::print(fg(color), "{}, ", n);
    }
    fmt::print("\n");
}

int main() {
    constexpr size_t N = 53;
    std::vector s((N - 3) / 2, true);

    int i = 0;
    auto i_offset = [](int i) {return 2 * i * i + 6 * i + 3;};
    mark_sieve_one(s.begin() + i_offset(i), s.end(), 3);
    print_primes(s);

    i = 1;
    std::fill(s.begin(), s.end(), true);
    mark_sieve_one(s.begin() + i_offset(i), s.end(), 5);
    print_primes(s);

    i = 2;
    std::fill(s.begin(), s.end(), true);
    mark_sieve_one(s.begin() + i_offset(i), s.end(), 7);
    print_primes(s);

    mark_sieve(s.begin(), N);
    print_primes(s);
}