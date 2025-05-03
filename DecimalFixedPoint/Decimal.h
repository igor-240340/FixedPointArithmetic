#pragma once

#include <cstdint>
#include <string>

class Decimal {
public:
    Decimal() = default;

    // NOTE: For simplicity we suppose that the input string is always correct numeric string
    // with only two fractional digits (if presented).
    Decimal(std::string number_str) {
        int int_part = 0;
        int frac_part = 0;
        bool is_negative = false;
        for (int i = 0; i < number_str.size(); i++) {
            if (number_str[i] == '-') {
                is_negative = true;
                continue;
            }

            if (number_str[i] == '.') {
                frac_part += (number_str[i + 1] - '0') * 10; // First fractional digit.
                frac_part += (number_str[i + 2] - '0');      // Second fractional digit.
                break;
            }

            int_part *= 10;
            int_part += number_str[i] - '0';
        }

        rep = static_cast<int32_t>((int_part * scale + frac_part) * (is_negative ? -1 : 1));
    };

    std::string to_string() {
        const int32_t rep_abs = std::abs(rep);

        const int int_part = rep_abs / scale;
        const int frac_part = rep_abs % scale;

        const std::string sign = (rep < 0) ? "-" : "";
        const std::string frac_part_str = std::to_string(frac_part);
        return std::format("{}{}.{}", sign, int_part, (frac_part < 10) ? ("0" + frac_part_str) : frac_part_str);
    }

    Decimal operator+(Decimal rh) const {
        return Decimal{ rep + rh.rep };
    };

    Decimal operator-(Decimal rh) const {
        return Decimal{ rep - rh.rep };
    };

    // NOTE: We don't perform correct decimal rounding here
    // and just truncate everything but two decimal fractional digits.
    Decimal operator*(Decimal rh) const {
        const int64_t overscaled_product = static_cast<int64_t>(rep) * rh.rep;

        return Decimal{ static_cast<int32_t>(overscaled_product / scale) }; // (a * scale) * (b * scale) = (a * b) * scale * scale;
    };

    // NOTE: Overscale dividend so we get scaled quotient up to two decimal places.
    Decimal operator/(Decimal rh) const {
        const int64_t scaled_quotient = static_cast<int64_t>(rep) * scale / rh.rep;

        return Decimal{ static_cast<int32_t>(scaled_quotient) };
    };

private:
    int32_t rep;

    Decimal(int32_t value) : rep{ value } {};

    static constexpr int scale = 100; // 2 decimal places.
};
