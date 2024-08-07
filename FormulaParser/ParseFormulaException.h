#ifndef PARSE_FORMULA_EXCEPTION_H
#define PARSE_FORMULA_EXCEPTION_H

#include <exception>
#include <string>

class ParseFormulaException : public std::exception {
public:
    explicit ParseFormulaException(const std::string& message, int position)
        : msg_(message), position_(position) {}

    const char* what() const noexcept override {
        return msg_.c_str();
    }

    int GetPosition() const { return position_; }

private:
    std::string msg_;
    int position_;
};

#endif // PARSE_FORMULA_EXCEPTION_H
