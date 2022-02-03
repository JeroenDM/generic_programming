#include <algorithm>
#include <cmath>
#include <concepts>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/format.h"
#include "timeit.h"

#define RandomAccessIterator std::random_access_iterator
#define Integer std::integral

inline int sqrt_floor(int x) {
    return static_cast<int>(std::floor(std::sqrt(x)));
}

template <Integer Int>
std::make_signed<Int>::type make_signed(Int i) {
    return static_cast<std::make_signed<Int>::type>(i);
}

/** Mark numbers that can be divided by the factor with false.
 *
 * # Preconditions
 *
 * First points to the index of the first value that needs to be checked.
 * This could be the index of  twice the factor:
 *     first = i + 2 * i + 3
 * but for efficiency it is the first occurrence of factor^2
 *     first = 2 * i^2 + 6 * i + 3.
 *
 * **/
// Assume first points the first value we need to check.
template <RandomAccessIterator Iter, Integer Int>
void mark_sieve_one(Iter first, Iter last, Int factor) {
    do {
        *first = false;
        first = first + factor;
    } while (last - first > make_signed<Int>(factor));
    // std::distance has linear time complexity for random access iterator!! ?
}

template <RandomAccessIterator Iter, Integer Int>
void mark_sieve(Iter first, Int n) {
    Iter last = first + n;
    std::fill(first, last, true);
    Int i{0};
    Int offset{3};
    Int factor{3};
    while (offset < n) {
        if (first[i]) {
            mark_sieve_one(first + offset, last, factor);
        }
        ++i;
        // factor(i + 1) = factor(i) + 2
        // offset(i + 1) = offset(i) + factor(i) + factor(i + 1)
        offset += factor;
        factor += Int(2);
        offset += factor;
    }
}

void print_primes(const std::vector<bool>& sieve) {
    for (size_t i = 0; i < sieve.size(); ++i) {
        int n = 3 + 2 * i;
        auto color = fmt::color::dark_red;
        if (sieve[i] == true) color = fmt::color::green;
        fmt::print(fg(color), "{}, ", n);
    }
    fmt::print("\n");
}

/** Exercise 3.2 **/
void benchmark() {
    fmt::print("\n--- Exercise 3.2 ---\n\n");
    static constexpr int NUM_RUNS{5000};
    std::vector<bool> sieve(60000);

    uint16_t n16{1000};
    uint32_t n32{1000};
    uint64_t n64{1000};

    double t1 = time_it([&]() { mark_sieve(sieve.begin(), n16); }, NUM_RUNS);
    fmt::print("time {:.6f} ms\n", t1 * 1000);

    double t2 = time_it([&]() { mark_sieve(sieve.begin(), n32); }, NUM_RUNS);
    fmt::print("time {:.6f} ms\n", t2 * 1000);

    double t3 = time_it([&]() { mark_sieve(sieve.begin(), n64); }, NUM_RUNS);
    fmt::print("time {:.6f} ms\n", t3 * 1000);
}

/** Exercise 3.3 **/
int count_primes(int n) {
    std::vector<bool> sieve(n);
    mark_sieve(sieve.begin(), sieve.size());
    return std::ranges::count(sieve, true);
}

void plot_line(const std::vector<int>& v) {
    static constexpr double TERMINAL_WIDTH = 80;
    int y_max = std::ranges::max(v);
    for (const auto& y : v) {
        int scaled = (int) ((double) y / (double) y_max) * TERMINAL_WIDTH;
        fmt::print("({}) |{}\n", y, std::string(y, '#'));
    }
}

void prime_function_plot() {
    fmt::print("\n--- Exercise 3.3 ---\n\n");
    auto generator = [n{0}]() mutable { return count_primes(++n); };

    std::vector<int> values(200);
    std::ranges::generate(values, generator);
    plot_line(values);
}

int main() {
    constexpr size_t N = 53;
    std::vector s((N - 3) / 2, true);

    int i = 0;
    auto i_offset = [](int i) { return 2 * i * i + 6 * i + 3; };
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

    mark_sieve(s.begin(), s.size());
    print_primes(s);

    // benchmark();
    // prime_function_plot();
}