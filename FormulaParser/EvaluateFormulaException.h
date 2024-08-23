#pragma once


#include <exception>
#include <string>

class EvaluateFormulaException : public std::exception {
public:
    explicit EvaluateFormulaException(const std::string& message)
        : std::exception(message.c_str()) {}
};

