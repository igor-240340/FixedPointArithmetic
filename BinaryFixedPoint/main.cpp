#include <iostream>
#include <iomanip>
#include <format>

#include "Fixed16.h"

void print_float_as_hex(float* a) {
    uint32_t int_rep = *(uint32_t*)a;

    // NOTE: std::dec restores output to decimal mode.
    std::cout << std::hex << std::setfill('0') << std::setw(8) << int_rep << std::dec << std::endl;
}

void test_construction() {
    Fixed16 a{ 10.0f };
    std::cout << "a: " << a.to_float() << '\n';

    Fixed16 b{ 8.5f };
    std::cout << "b: " << b.to_float() << '\n';

    std::cout << '\n';

    float orig_value = 0.1f;
    print_float_as_hex(&orig_value); // orig_value = 3dcccccd.

    Fixed16 c{ orig_value }; // Now we've lost precision.
    float back_converted = c.to_float();
    std::cout << "c: " << c.to_float() << '\n';
    print_float_as_hex(&back_converted); // back_converted = 3dccc800.
}

void test_addition() {
    Fixed16 a{ 17.375f };
    Fixed16 b{ 1.125f };
    Fixed16 c = a + b;

    std::cout << std::format("{} + {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_negative() {
    Fixed16 a{ 0.9375f };
    Fixed16 b{ -22.9375f };
    Fixed16 c = a + b;

    std::cout << std::format("{} + {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_subtraction() {
    Fixed16 a{ 5.65625f };
    Fixed16 b{ 3.5f };
    Fixed16 c = a - b;

    std::cout << std::format("{} - {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_multiplication() {
    Fixed16 a{ 1.5f };
    Fixed16 b{ 1.5f };
    Fixed16 c = a * b;

    std::cout << std::format("{} * {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_multiplication_overflow() {
    Fixed16 a{ 2147483647 }; // 32767.9999847412109375 (can't be represented in float axactly - rounds to 32768).
    Fixed16 b{ 2147483647 };
    Fixed16 c = a * b;

    std::cout << std::format("{} * {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_division() {
    Fixed16 a{ 2147483647 }; // 32767.9999847412109375 (can't be represented in float axactly - rounds to 32768).
    Fixed16 b{ 3.5f };
    Fixed16 c = a / b;

    std::cout << std::format("{} / {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void test_division_min() {
    Fixed16 min{ 1 }; // 2^-16.
    Fixed16 max{ 2147483647 }; // 32767.9999847412109375.
    Fixed16 c = min / max; // Underflow.

    std::cout << std::format("{} / {} = {}", min.to_float(), max.to_float(), c.to_float()) << '\n';
}

void test_division_max() {
    Fixed16 max{ 2147483647 }; // 32767.9999847412109375.
    Fixed16 min{ 1 }; // 2^-16.
    Fixed16 c = max / min; // Overflow.

    std::cout << std::format("{} / {} = {}", max.to_float(), min.to_float(), c.to_float()) << '\n';
}

int main() {
    test_construction();

    std::cout << '\n';
    test_addition();

    std::cout << '\n';
    test_negative();

    std::cout << '\n';
    test_subtraction();

    std::cout << '\n';
    test_multiplication();

    std::cout << '\n';
    test_multiplication_overflow();

    std::cout << '\n';
    test_division();

    std::cout << '\n';
    test_division_min();

    std::cout << '\n';
    test_division_max();

    return 0;
}
