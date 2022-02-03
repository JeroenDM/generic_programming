#pragma once

#include <chrono>
#include <functional>
#include <ranges>

/** Return the time it takes to execute a function n times, in seconds. **/
double time_it(std::function<void()> f, int n) {
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();
    for ([[maybe_unused]] int i : std::views::iota(0, n)) f();
    auto end = clock::now();
    std::chrono::duration<double> dt = end - start;
    return dt.count();
}