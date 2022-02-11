#include <cassert>
#include <functional>
#include <limits>
#include <random>
#include <ranges>
#include <utility>

#include "fmt/core.h"
#include "testing.h"

/** Calculate a / b. **/
std::pair<int, int> division_simple(int a, int b) {
    // preconditions
    assert(b != 0);
    // assert(a >= b);

    int r{b};
    int q{0};
    while (r <= a) {
        r += b;
        ++q;
    }

    return {q, a - (r - b)};
}

std::pair<int, int> division_2(int a, int b) {
    // preconditions
    assert(b != 0);

    if (b > a) return {0, a};
    if (b == a) return {1, 0};

    int q{0};  // quotient
    int r{b};
    while (r <= a) {
        r += b;
        ++q;
    }

    r = a - (r - b);  // remainder

    return {q, r};
}

void test_that_stuff(std::function<std::pair<int, int>(int, int)> div);

int main() {
    test_that_stuff(division_simple);
    // test_that_stuff(division_2);
}

void test_that_stuff(std::function<std::pair<int, int>(int, int)> div) {
    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(42);
    // std::uniform_int_distribution<> distrib(0,
    // std::numeric_limits<int>::max());
    std::uniform_int_distribution<> distrib(0, 100);

    auto rand = [&]() { return distrib(gen); };

    for (int i : std::views::iota(1, 50)) {
        int a{rand()};
        int b(0);
        while (b == 0) b = rand();
        test_equal(fmt::format("{}: {} / {}", i, a, b), div(a, b),
                   std::make_pair(a / b, a % b));
    }
}