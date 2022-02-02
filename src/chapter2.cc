#include "testing.h"

int multiply(int n, int a) {
    if (n == 1)
        return a;
    else
        return multiply(n - 1, a) + a;
}

// bool odd(int n) { return (n % 2) != 0; }
// Check least significant bit of x.
// Can't the compiler generate this kind of stuff?
inline bool odd(int n) { return n & 0x1; }
inline int half(int n) { return n >> 1; }

int ahmes(int n, int a) {
    // if (n == 1)
    //     return a;
    // if (odd(n))
    //     return ahmes(n - 1, a) + a;
    // else
    //     return ahmes(n / 2, a + a);
    if (n == 1) return a;

    // Kind of weird but rely on half(n) == half(n-1)
    int result = ahmes(half(n), a + a);
    if (odd(n)) result = result + a;

    return result;
}

int mult_acc(int r, int n, int a) {
    if (n == 1) return r + a;
    if (odd(n)) r = r + a;
    return mult_acc(r, half(n), a + a);
}

int mult_loop(int n, int a) {
    int r = 0;
    while (n > 1) {
        if (odd(n)) r = r + a;
        a = a + a;
        n = half(n);
    }
    return r + a;
}

// Crazy optimized implementation at the end of section 2.2.
// Also, where is the line when optimizing function calls.
// odd() and half() are still functions, could also be inlined,
// but this is easily done by the compiler.
// (Same can be said for tail recursion, or not?)
int mult_acc_final(int r, int n, int a) {
    while (true) {
        if (odd(n)) {
            r = r + a;
            if (n == 1) return r;
        }
        n = half(n);
        a = a + a;
    }
}

int mult_final(int a, int n) {
    while (!odd(n)) {
        a = a + a;
        n = half(n);
    }
    if (n == a) return a;
    // odd(n) == true
    // even(n - 1) => n - 1 != 1
    return mult_acc_final(a, half(n - 1), a + a);
}

int main() {
    test_equal("odd true", odd(3), true);
    test_equal("odd false", odd(442), false);
    test_equal("half", half(42), 21);
    test_equal("half", half(43), 21);

    test_equal("multiply", multiply(3, 5), 3 * 5);
    test_equal("ahmes", ahmes(41, 59), 41 * 59);

    test_equal("mult_acc", mult_acc(0, 41, 59), 41 * 59);
    test_equal("mult_loop", mult_loop(41, 59), 41 * 59);

    test_equal("mult_final", mult_final(41, 59), 41 * 59);
}