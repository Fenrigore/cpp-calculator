
#pragma once

#include <string>
#include <optional>
#include "rational.h"
#include "pow.h"

using Error = std::string;

// Реализация шаблонного калькулятора.

template <typename T>
class Calculator{
    std::optional<T> mem_;
    T summ_ = 0;

public:
    void Set(T n){
        summ_=n;
    }

    T GetNumber() const{
        return summ_;
    }


    std::optional<Error> Add(T n){
        summ_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(T n){
        summ_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(T n){
        if constexpr (std::is_integral_v<T> || std::is_same_v<T, Rational>){
            if (n == 0){
                return "Division by zero";
            }
        }
        summ_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(T n){
        summ_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(T n){
        if constexpr(std::is_integral_v<T>){    //если целочисленный тип
            if (n == 0&& summ_ == 0){
                return "Zero power to zero";
            }else if(n < 0){
                return "Integer negative power";
            }
            summ_ = ::IntegerPow(summ_, n);
        }else if constexpr(std::is_same_v<T, Rational>){ //возведение в степень дроби
            if (n.GetDenominator() != 1){
                return "Fractional power is not supported";
            }else if (n == 0&& summ_ == 0){
                return "Zero power to zero";
            }
            summ_ = ::Pow(summ_, n);
        }else if constexpr(std::is_floating_point_v<T>){ //возведение в степень чисел с запятой
            if (n<0&& n<0){
                return "Zero power to zero";
            }
            summ_ = ::Pow(summ_, n);
        }
        return std::nullopt;
    }

    void Save(){
        mem_ = summ_;
    }

    void Load(){
        if (mem_.has_value()){
            summ_ = mem_.value();
        }
    }

    bool GetHasMem(){
        return (mem_.has_value());
    }

    std::string GetNumberRepr() const{
        return std::to_string(summ_);
    }
};
