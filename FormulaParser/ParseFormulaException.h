#pragma once

#include <exception>
#include <string>

class ParseFormulaException : public std::exception {
public:
    explicit ParseFormulaException(const std::string& message, int position)
        : msg_(message), position_(position) {}

    const char* what() const noexcept override {
        return msg_.c_str();
    }

    int GetPosition() const noexcept { return position_; }

private:
    std::string msg_;
    int position_;
};

