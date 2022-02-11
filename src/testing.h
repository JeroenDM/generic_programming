#pragma once

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include <utility>
#include <vector>

struct point {
    double x, y;
};

template <>
struct fmt::formatter<std::pair<int, int>> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin(), end = ctx.end();
        // Return an iterator past the end of the parsed range:
        return it;
    }
    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    template <typename FormatContext>
    auto format(const std::pair<int, int>& p, FormatContext& ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "({}, {})", p.first, p.second);
    }
};

template <typename T>
void test_equal(const std::string& name, const T& a, const T& b) {
    if (a == b) {
        fmt::print(fg(fmt::color::green), "SUCCESS\t{}\t{} == {}\n", name, a,
                   b);
    } else {
        fmt::print(fg(fmt::color::red), "FAILURE\t in {}", name);
        fmt::print(fg(fmt::color::red), "\t{} != {}\n", a, b);
    }
}