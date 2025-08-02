#pragma once
#include <numeric>
#include <iostream>

class Rational{
public:
    Rational() = default;
    Rational(int num):numerator_{num}{}
    Rational(int num, int denom): numerator_{num}, denominator_{denom}{
        Reduction();
    }
    Rational(const Rational& other) : numerator_{other.numerator_}, denominator_{other.denominator_}{
        Reduction();
    }

    //инвертирование дроби
    Rational Inv(){
        return Rational {denominator_,numerator_};
    }

    //получение числителя
    int GetNumerator()const{
        return numerator_;
    }

    //получение знаменателя
    int GetDenominator()const{
        return denominator_;
    }

    //сокращение дроби
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    //Математические операции
    Rational& operator*=(const Rational& rat2){
        numerator_ *= rat2.numerator_;
        denominator_ *= rat2.denominator_;
        //Reduction();
        return *this;
    }

    Rational operator *(const Rational& rat2){
        Rational output = *this;
        return output *= rat2;
    }

    Rational & operator /=(const Rational & rat2){
        numerator_ *= rat2.denominator_;
        denominator_ *= rat2.numerator_;
        //Reduction();
        return *this;
    }

    Rational operator /(const Rational & rat2){
        Rational output = *this;
        return output /= rat2;
    }

    Rational & operator +=(const Rational & rat2){
        numerator_ = numerator_*rat2.denominator_ + denominator_ * rat2.numerator_;
        denominator_ *= rat2.denominator_;
        //Reduction();
        return *this;
    }

    Rational operator +(const Rational & rat2){
        Rational output = *this;
        return output += rat2;
    }

    Rational & operator -=(const Rational&rat2){
        numerator_ = numerator_*rat2.denominator_ - denominator_ * rat2.numerator_;
        denominator_ *= rat2.denominator_;
        //Reduction();
        return *this;
    }

    Rational operator - (const Rational & rat2){
        Rational output = *this;
        return output -= rat2;
    }

    Rational  operator+()const{
        return *this;
    }

    Rational  operator -()const{
        return Rational{-numerator_, -denominator_};
    }

    //перегрузка присваивания

    Rational& operator =(const int val){
        numerator_ = val;
        denominator_ = 1;
        return *this;
    }
    Rational& operator = (const Rational& rat2){
        numerator_ = rat2.numerator_;
        denominator_ = rat2.denominator_;
        return *this;
    }

    friend bool operator ==(const Rational & l_ratio, const Rational & r_ratio);
    friend bool operator ==(const Rational & l_ratio, int number);
    friend auto  operator <=>(const Rational & l_ratio, const Rational & r_ratio);
    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

    private:
    int numerator_{0};
    int denominator_{1};
};

inline bool operator ==(const Rational & l_ratio, const Rational & r_ratio){
    int c1 = l_ratio.numerator_ * r_ratio.denominator_;
    int c2 = r_ratio.numerator_ * l_ratio.denominator_;
    return c1 == c2;
}

inline bool operator ==(const Rational & l_ratio, int number){
    int c1 = l_ratio.numerator_;
    int c2 = number;
    return c1 == c2;
}

inline auto  operator <=>(const Rational & l_ratio, const Rational & r_ratio){
    int c1 = l_ratio.numerator_ * r_ratio.denominator_;
    int c2 = r_ratio.numerator_ * l_ratio.denominator_;
    return c1 <=> c2;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    using namespace std::literals;
    if (r.GetDenominator() == 1){
        os << r.numerator_;
    }else{
        os << r.numerator_ << " / "s << r.denominator_;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char div;

    if (!(is >> n)) {
        return is;
    }

    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }

    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }

    if (!(is >> d) || (d == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    r = Rational(n, d);

    return is;
}
