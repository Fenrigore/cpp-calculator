#pragma once
#include <string>

using Number = double;

class Calculator{
    std::string saved_number_;
    Number summ_ = 0;

public:
    void Set(Number n);
    Number GetNumber() const;
    void Add(Number n);
    void Sub(Number n);
    void Div(Number n);
    void Mul(Number n);
    void Pow(Number n);
    void Save();
    void Load();
    bool HasMem() const;
    std::string GetNumberRepr() const;
};
