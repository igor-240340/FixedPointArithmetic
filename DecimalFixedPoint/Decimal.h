#pragma once

#include <cstdint>
#include <string>

class Decimal {
public:
    Decimal() = default;

    // NOTE: For negative value specify minus for both int_part and frac_part except when one of it is zero.
    Decimal(int int_part, int frac_part) : rep{ int_part * scale + frac_part } {};

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
