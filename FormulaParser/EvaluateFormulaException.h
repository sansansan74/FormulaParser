#pragma once


#include <exception>
#include <string>

using namespace std;

class EvaluateFormulaException : public std::exception {
    string message_;
public:
    explicit EvaluateFormulaException(const std::string& message)
        : message_(message) {
    }

    virtual char const* what() const noexcept { return message_.c_str(); }
};

