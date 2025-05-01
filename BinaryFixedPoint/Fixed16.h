#pragma once

#include <cstdint>

class Fixed16 {
public:
    Fixed16() = default;
    Fixed16(int32_t num) : rep{ num } {};

    // NOTE: We always construct from floating-point values.
    // It's ok,because almost all possible integer values from which we could build Fixed16 are representable in float exactly.
    // Moreover, as int32_t is defined in MSVC as typedef int int32_t, we can't overload constructor anyway.
    //Fixed16(int num) : value{ static_cast<int32_t>(num << frac_bit_len) } {};

    // NOTE:
    // When fractional num converts to int it's first internally denormalized to the left by it's exponent
    // then trucation of fractional part occurs. So, to preserve whole part as well as fractional part,
    // when it happens we have to have the num already be shifted left by 16 bits.
    // Obviously enough we can't just shift floating-point representation as it will just corrupt stored value.
    // So we scale floating-point value by multiplication.
    //
    // Another important moment is that float has 23 fractional bits but our fixed-point type has only 16 fractional bits
    // so, aside from the fact that you can lose some bits, if needed, you have to perform correct rounding,
    // but here we don't care and just truncate.
    Fixed16(float num) : rep{ static_cast<int32_t>(num * (1 << frac_bit_len)) } {};

    // NOTE: For conversion into numeric string without losing precision we should extract decimal digits of
    // whole part and fractional part separately. For example, by calculating mod 10 for whole part and multiplying
    // fractional part by 10. But for now we don't care, we just playing around fixed-point arithmetic for fun.
    float to_float() const {
        return static_cast<float>(rep) / (1 << frac_bit_len);
    }

    Fixed16 operator+(Fixed16 rh) const {
        return Fixed16{ rep + rh.rep };
    };

    Fixed16 operator-(Fixed16 rh) const {
        return Fixed16{ rep - rh.rep };
    };

    // NOTE: True product has additional 16 low-order bits and 16 high-order bits
    // so, after correction of the scale we can lose 16 low-order fractional bits
    // and get overflow losing 16 high-order bits after packing back into int32_t.
    Fixed16 operator*(Fixed16 rh) const {
        const int64_t overscaled_product = static_cast<int64_t>(rep) * rh.rep;

        // (a * scale) * (b * scale) =
        // (a * b) * scale * scale =>
        // (a * b) * scale = true_product / scale.
        return Fixed16{ static_cast<int32_t>(overscaled_product >> frac_bit_len) };
    };

    Fixed16 operator/(Fixed16 rh) const {
        // NOTE: If we don't scale we get true partial quotient (whole part only)
        // but we want have 16 bit of the fractional part as well.
        // 
        // Also, don't confuse scaling with temporary binary grid expansion during division
        // which occurs implicitly in the CPU and in general depends on realization of integer division.
        const int64_t scaled_divident = static_cast<int64_t>(rep) << frac_bit_len;

        return Fixed16{ static_cast<int32_t>(scaled_divident / rh.rep) }; // (a * k * k) / (b * k) = (a / b) * k.
    }

private:
    int32_t rep;

    static constexpr int frac_bit_len = 16;
};
