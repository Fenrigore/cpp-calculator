#include "calculator.h"
#include <cmath>

void Calculator::Set(Number n){
    summ_ = n;
}

Number Calculator::GetNumber() const{
    return summ_;
}

void Calculator::Add(Number n){
    summ_ += n;
}

void Calculator::Sub(Number n){
    summ_ -= n;
}

void Calculator::Div(Number n){
    summ_ /= n;
}

void Calculator::Mul(Number n){
    summ_ *= n;
}

void Calculator::Pow(Number n){
    summ_ = pow(summ_, n);
}

void Calculator::Save(){
    saved_number_ = std::to_string(summ_);
}

void Calculator::Load(){
    summ_ = std::stod(saved_number_);
}

bool Calculator::HasMem() const{
    return saved_number_.size() > 0 ? true : false;
}

std::string Calculator::GetNumberRepr() const{
    return std::to_string(summ_);
}
