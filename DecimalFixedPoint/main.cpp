#include <iostream>
#include <iomanip>
#include <format>

#include "Decimal.h"

void test_construction() {
    Decimal a{ "0.10" };
    Decimal b{ "0.30" };
    Decimal c{ "0.01" };
    Decimal d{ "56.09" };
    Decimal e{ "-56.09" };
    Decimal f{ "-12345" };

    std::cout << "a: " << a.to_string() << '\n';
    std::cout << "b: " << b.to_string() << '\n';
    std::cout << "c: " << c.to_string() << '\n';
    std::cout << "d: " << d.to_string() << '\n';
    std::cout << "e: " << e.to_string() << '\n';
    std::cout << "f: " << f.to_string() << '\n';
}

void test_addition() {
    Decimal a{ "0.99" };
    Decimal b{ "0.02" };
    Decimal c = a + b; // 1.01

    std::cout << std::format("{} + {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void test_negative() {
    Decimal a{ "-0.60" };
    Decimal b{ "0.50" };
    Decimal c = a + b; // -0.1

    std::cout << std::format("{} + {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void test_subtraction() {
    Decimal a{ "67.29" };
    Decimal b{ "93.17" };
    Decimal c = a - b; // -25.88

    std::cout << std::format("{} - {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void test_multiplication() {
    Decimal a{ "-67.29" };
    Decimal b{ "93.17" };
    Decimal c = a * b; // -6269.4093 (but we truncate and get -6269.40)

    std::cout << std::format("{} * {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
}

void test_division() {
    Decimal a{ "-312.35" };
    Decimal b{ "117.23" };
    Decimal c = a / b; // -2.6644... (but we truncate and get -2.66)

    std::cout << std::format("{} / {} = {}", a.to_string(), b.to_string(), c.to_string()) << '\n';
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
    test_division();

    return 0;
}
