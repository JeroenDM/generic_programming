#include <fmt/core.h>
#include <fmt/format.h>

#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

struct Vector {
    float x;
    float y;

    Vector operator+(const Vector& other) { return {x + other.x, y + other.y}; }

    Vector operator-(const Vector& other) { return {x - other.x, y - other.y}; }
};

float dot(const Vector& a, const Vector& b) { return a.x * b.x + a.y * b.y; }

Vector normalize(const Vector& v) {
    float n = dot(v, v);
    if (n == 0) return {0, 0};
    return {v.x / n, v.y / n};
}

using Shape = std::vector<Vector>;

Vector support_fun(const Shape& shape, const Vector& dir) {
    // preconditions: dir is normalized.
    // Shape has at least one vertex;
    float max_dot = dot(shape.front(), dir);
    Vector result = shape.front();
    for (const Vector& v : shape) {
        float d = dot(v, dir);
        fmt::print("v ({}, {}) d {}\n", v.x, v.y, d);
        if (d > max_dot) {
            max_dot = d;
            result = v;
        }
    }
    return result;
}

int main() {
    Shape square = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

    Vector right_down = normalize({-1, -1});
    fmt::print("({}, {})\n", right_down.x, right_down.y);

    Vector s = support_fun(square, right_down);

    fmt::print("({}, {})\n", s.x, s.y);

}