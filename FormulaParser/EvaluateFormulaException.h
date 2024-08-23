#pragma once

#ifndef EVALUATE_FORMULA_EXCEPTION_H
#define EVALUATE_FORMULA_EXCEPTION_H

#include <exception>
#include <string>

class EvaluateFormulaException : public std::exception {
public:
    explicit EvaluateFormulaException(const std::string& message)
        : std::exception(message.c_str()) {}
    
private:
};

#endif // EVALUATE_FORMULA_EXCEPTION_H
