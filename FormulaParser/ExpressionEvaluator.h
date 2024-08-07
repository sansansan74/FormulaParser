#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include "TreeItem.h"
#include "TreeLeaf.h"
#include "TreeOperation.h"
#include <stdexcept>
#include <string>
#include <memory>
#include <cmath>

class ExpressionEvaluator {
public:
    static double Evaluate(const std::unique_ptr<TreeItem>& item) {
        if (const TreeLeaf* leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
            return leaf->GetValue();
        }
        
        if (TreeOperation* operation = dynamic_cast<TreeOperation*>(item.get())) {
            return EvaluateOperation(operation);
        }
        throw std::invalid_argument("Unknown TreeItem type");
    }

private:
    static double EvaluateOperation(TreeOperation* operation) {
        const std::string& op = operation->GetOperation();
        const auto& items = operation->GetItems();

        if (op == "Add") {
            double result = 0;
            for (const auto& item : items) {
                result += Evaluate(item);
            }
            return result;
        }
        
        if (op == "Subtract") {
            double result = 0;
            for (const auto& item : items) {
                result -= Evaluate(item);
            }
            return result;
        }

        if (op == "Mult") {
            double result = 1;
            for (const auto& item : items) {
                result *= Evaluate(item);
            }
            return result;
        }

        if (op == "Divide") {
            double result = Evaluate(items[0]);
            for (int i = 1; i < items.size(); i++) {
                auto res = Evaluate(items[i]);
                if (res == 0)
                    throw std::domain_error("Division by zero");

                result /= res;
            }
            return result;
        }

        if (op == "pi") {
            if (items.size() != 0)
            {
                throw std::domain_error("Fuction Pi() must no arguments");
            }
            return 3.14159;
        }
        
        if (op == "avg") {
            if (items.size() == 0)
            {
                throw std::domain_error("Fuction Avg() must have parameters");
            }

            double result = 0;
            for (const auto& item : items) {
                result += Evaluate(item);
            }
            return result/items.size();
        }

        if (op == "pow") {
            if (items.size() != 2)
            {
                throw std::domain_error("Fuction Pow() must have 2 parameters");
            }

            return std::pow(Evaluate(items[0]), Evaluate(items[1]));

        }
        throw std::invalid_argument("Unknown operation: " + op);
    }
};

#endif // EXPRESSION_EVALUATOR_H
