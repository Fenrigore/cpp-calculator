#include <iostream>
#include <string>
#include <cmath>
#include "calculator.h"

bool ReadNumber(Number& result)
{
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
        return true;
}

bool RunCalculatorCycle()
{
    Number input_number = 0;
    Number summ = 0;
    bool is_no_error = true;
    std::string input_symbol;
    std::string saved_number;

    is_no_error = ReadNumber(input_number);

    summ = input_number;

    while (is_no_error) {
        std::cin >> input_symbol;
        if (input_symbol == "q") {
            break;
        }
        else if (input_symbol == "+") {
            is_no_error = ReadNumber(input_number);
            summ += input_number;
        }
        else if (input_symbol == "-") {
            is_no_error = ReadNumber(input_number);
            summ += input_number * -1;
        }
        else if (input_symbol == "*") {
            is_no_error = ReadNumber(input_number);
            summ *= input_number;
        }
        else if (input_symbol == "/") {
            is_no_error = ReadNumber(input_number);
            summ /= input_number;
        }
        else if (input_symbol == ":") {
            is_no_error = ReadNumber(input_number);
            summ = input_number;
        }
        else if (input_symbol == "=") {
            std::cout << summ << std::endl;
        }
        else if (input_symbol == "c") {
            summ = 0;
        }
        else if (input_symbol == "**") {
            is_no_error = ReadNumber(input_number);
            summ = std::pow(summ, input_number);
        }
        else if (input_symbol == "s") {
            saved_number = std::to_string(summ);
        }
        else if (input_symbol == "l") {
            if (saved_number.size() > 0) {
                summ = std::stod(saved_number);
            }
            else {
                std::cerr << "Error: Memory is empty" << std::endl;
                is_no_error = false;
            }
        }
        else {
            std::cerr << "Error: Unknown token " << input_symbol << std::endl;
            is_no_error = false;
        }
    }

    return is_no_error;
}