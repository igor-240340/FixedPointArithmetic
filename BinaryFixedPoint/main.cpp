#include <iostream>
#include <iomanip>
#include <format>

#include "Fixed16.h"

void print_float_as_hex(float* a) {
    uint32_t int_rep = *(uint32_t*)a;

    // NOTE: std::dec restores output to decimal mode.
    std::cout << std::hex << std::setfill('0') << std::setw(8) << int_rep << std::dec << std::endl;
}

void float_test_construction() {
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

void float_test_addition() {
    Fixed16 a{ 17.375f };
    Fixed16 b{ 1.125f };
    Fixed16 c = a + b;

    std::cout << std::format("{} + {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_negative() {
    Fixed16 a{ 0.9375f };
    Fixed16 b{ -22.9375f };
    Fixed16 c = a + b;

    std::cout << std::format("{} + {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_subtraction() {
    Fixed16 a{ 5.65625f };
    Fixed16 b{ 3.5f };
    Fixed16 c = a - b;

    std::cout << std::format("{} - {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_multiplication() {
    Fixed16 a{ 1.5f };
    Fixed16 b{ 1.5f };
    Fixed16 c = a * b;

    std::cout << std::format("{} * {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_multiplication_overflow() {
    Fixed16 a{ 2147483647 }; // 32767.9999847412109375 (can't be represented in float axactly - rounds to 32768).
    Fixed16 b{ 2147483647 };
    Fixed16 c = a * b;

    std::cout << std::format("{} * {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_division() {
    Fixed16 a{ 2147483647 }; // 32767.9999847412109375 (can't be represented in float axactly - rounds to 32768).
    Fixed16 b{ 3.5f };
    Fixed16 c = a / b;

    std::cout << std::format("{} / {} = {}", a.to_float(), b.to_float(), c.to_float()) << '\n';
}

void float_test_division_min() {
    Fixed16 min{ 1 }; // 2^-16.
    Fixed16 max{ 2147483647 }; // 32767.9999847412109375.
    Fixed16 c = min / max; // Underflow.

    std::cout << std::format("{} / {} = {}", min.to_float(), max.to_float(), c.to_float()) << '\n';
}

void float_test_division_max() {
    Fixed16 max{ 2147483647 }; // 32767.9999847412109375.
    Fixed16 min{ 1 }; // 2^-16.
    Fixed16 c = max / min; // Overflow.

    std::cout << std::format("{} / {} = {}", max.to_float(), min.to_float(), c.to_float()) << '\n';
}

void float_test() {
    float_test_construction();

    std::cout << '\n';
    float_test_addition();

    std::cout << '\n';
    float_test_negative();

    std::cout << '\n';
    float_test_subtraction();

    std::cout << '\n';
    float_test_multiplication();

    std::cout << '\n';
    float_test_multiplication_overflow();

    std::cout << '\n';
    float_test_division();

    std::cout << '\n';
    float_test_division_min();

    std::cout << '\n';
    float_test_division_max();
}

void no_float_test_construction() {
    Fixed16 a{ "1223" };
    std::cout << "a: " << a.to_string() << '\n';

    Fixed16 b{ "23234.5" };
    std::cout << "b: " << b.to_string() << '\n';

    Fixed16 c{ "-10234.000354" };
    std::cout << "c: " << c.to_string() << '\n';

    Fixed16 d{ "-0.000345" };
    std::cout << "d: " << d.to_string() << '\n';

    Fixed16 max_incorrect{ "32767.9999847412109375" };
    std::cout << "max_incorrect: " << max_incorrect.to_string() << '\n';

    Fixed16 long_frac_incorrect{ "0.9999847412109375" };
    std::cout << "long_frac_incorrect: " << long_frac_incorrect.to_string() << '\n';

    Fixed16 frac_with_loss{ "0.00984741188" };
    std::cout << "frac_with_loss: " << frac_with_loss.to_string() << '\n';

    Fixed16 near_max_short_frac{ "32767.9984741" };
    std::cout << "near_max_short_frac: " << near_max_short_frac.to_string() << '\n';
}

void no_float_test_addition() {
    Fixed16 a{ "17.375" };
    Fixed16 b{ "1.125" };
    Fixed16 c = a + b; // Expected: 18.5.

    std::cout << std::format("{} + {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void no_float_test_negative() {
    Fixed16 a{ "0.9375" };
    Fixed16 b{ "-22.9375" };
    Fixed16 c = a + b; // Expected: -22.

    std::cout << std::format("{} + {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void no_float_test_subtraction() {
    Fixed16 a{ "5.65625" };
    Fixed16 b{ "3.5" };
    Fixed16 c = a - b; // Expected: 2.15625.

    std::cout << std::format("{} - {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void no_float_test_multiplication() {
    Fixed16 a{ "1.5" };
    Fixed16 b{ "1.5" };
    Fixed16 c = a * b; // Expected: 2.25.

    std::cout << std::format("{} * {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void no_float_test_multiplication_overflow() {
    Fixed16 a{ "32767.9984741" }; // Though 32767.9999847412109375 can be represented axactly in 16.16 format,
    Fixed16 b{ "32767.9984741" }; // we can't correctly convert it into binary with current method.
    Fixed16 c = a * b;

    std::cout << std::format("{} * {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void no_float_test_division() {
    Fixed16 a{ "32767.9984741" };
    Fixed16 b{ "3.5" };
    Fixed16 c = a / b; // Expected: 9362.2852783142857142857142857143.

    std::cout << std::format("{} / {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

// Not really min as we can't handle maximum representable value.
void no_float_test_division_min() {
    Fixed16 min{ "0.0000152587890625" }; // 2^-16.
    Fixed16 max{ "32767.9984741" };
    Fixed16 c = min / max; // Underflow.

    std::cout << std::format("{} / {} = {}", min.to_string(), max.to_string(), c.to_string()) << '\n';
}

// Not really max as we can't handle maximum representable value.
void no_float_test_division_max() {
    Fixed16 max{ "32767.9984741" };
    Fixed16 min{ "0.0000152587890625" }; // 2^-16.
    Fixed16 c = max / min; // Overflow.

    std::cout << std::format("{} / {} = {}", max.to_string(), min.to_string(), c.to_string()) << '\n';
}

void no_float_test() {
    no_float_test_construction();

    std::cout << '\n';
    no_float_test_addition();

    std::cout << '\n';
    no_float_test_negative();

    std::cout << '\n';
    no_float_test_subtraction();

    std::cout << '\n';
    no_float_test_multiplication();

    std::cout << '\n';
    no_float_test_multiplication_overflow();

    std::cout << '\n';
    no_float_test_division();

    std::cout << '\n';
    no_float_test_division_min();

    std::cout << '\n';
    no_float_test_division_max();
}

int main() {
    std::cout << "Using float\n";
    float_test();

    std::cout << "\nNot using float\n";
    no_float_test();

    return 0;
}
