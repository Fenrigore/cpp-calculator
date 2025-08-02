#pragma once

#include "rational.h"
#include <cmath>

template<class Number>
inline Number IntegerPow(Number l_op, Number r_op) {
    Number res = 1;
    while (r_op > 0) {
        if (r_op & 1) {
            res *= l_op;
        }
        r_op >>= 1;
        l_op *= l_op;
    }
    return res;
}



template <typename T>
inline T Pow ( T count, T degree){
    T temp{};
    if constexpr (std::is_integral_v<T>){
        temp = IntegerPow(count, degree);
    }else if constexpr(std::is_floating_point_v<T>){
        temp = std::pow(count,degree);
    }
    return temp;
}

template <>
inline Rational Pow(Rational lhs, Rational rhs) {
    if (rhs.GetDenominator() != 1) {
        std::abort();
    }
    Rational rat{};
    auto pow = rhs.GetNumerator();
    if (pow >= 0) {
        rat = {IntegerPow(lhs.GetNumerator(), pow), IntegerPow(lhs.GetDenominator(), pow)};
    } else {
        rat = {IntegerPow(lhs.GetDenominator(), -pow), IntegerPow(lhs.GetNumerator(), -pow)};
    }
    return rat;
}
