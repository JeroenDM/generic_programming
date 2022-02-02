#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

template <typename T>
void test_equal(const std::string &name, const T &a, const T &b)
{
    if (a == b)
    {
        fmt::print(fg(fmt::color::green), "SUCCESS\t{}\n", name);
    }
    else
    {
        fmt::print(fg(fmt::color::red), "FAILURE\t in {}.\n", name);
        fmt::print(fg(fmt::color::red), "\t{} != {}\n", a, b);
    }
}