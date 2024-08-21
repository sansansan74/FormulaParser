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
    static double EvaluateAdd(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        double result = 0;
        for (const auto& item : items) {
            result += Evaluate(item);
        }
        return result;
    }

    static double EvaluateSubtract(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        double result = 0;
        for (const auto& item : items) {
            result -= Evaluate(item);
        }
        return result;
    }

    static double EvaluateMult(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        double result = 1;
        for (const auto& item : items) {
            result *= Evaluate(item);
        }
        return result;
    }

    static double EvaluateDivide(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        double result = Evaluate(items[0]);
        for (int i = 1; i < items.size(); i++) {
            auto res = Evaluate(items[i]);
            if (res == 0)
                throw std::domain_error("Division by zero");

            result /= res;
        }
        return result;
    }

    static double EvaluatePi(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        if (items.size() != 0)
        {
            throw std::domain_error("Fuction Pi() must no arguments");
        }
        return 3.14159;
    }

    static double EvaluateAvg(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        if (items.size() == 0)
        {
            throw std::domain_error("Fuction Avg() must have parameters");
        }

        double result = 0;
        for (const auto& item : items) {
            result += Evaluate(item);
        }
        return result / items.size();
    }

    static double EvaluatePow(const std::vector<std::unique_ptr<TreeItem>>& items)
    {
        if (items.size() != 2)
        {
            throw std::domain_error("Fuction Pow() must have 2 parameters");
        }

        return std::pow(Evaluate(items[0]), Evaluate(items[1]));
    }

    static double EvaluateOperation(TreeOperation* operation) {
        const std::string& op = operation->GetOperation();
        const auto& items = operation->GetItems();

        if (op == "Add") {
            return EvaluateAdd(items);
        }
        
        if (op == "Subtract") {
            return EvaluateSubtract(items);
        }

        if (op == "Mult") {
            return EvaluateMult(items);
        }

        if (op == "Divide") {
            return EvaluateDivide(items);
        }

        if (op == "pi") {
            return EvaluatePi(items);
        }
        
        if (op == "avg") {
            return EvaluateAvg(items);
        }

        if (op == "pow") {
            return EvaluatePow(items);
        }
        throw std::invalid_argument("Unknown operation: " + op);
    }
};

#endif // EXPRESSION_EVALUATOR_H
