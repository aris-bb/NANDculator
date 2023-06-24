#include "helper.hpp"

#include <stdexcept>

std::tuple<std::string, std::string, std::string>
nandculator::helper::split_by_operator(const std::string& expression) {
  // list of operators
  const std::vector<std::string> operators = {"+", "-", "*", "/"};

  // count the number of operators in the expression
  int operator_count = 0;
  for (const auto& c : expression) {
    if (std::find(operators.begin(), operators.end(), std::string(1, c)) !=
        operators.end()) {
      operator_count++;
    }
  }

  if (operator_count == 1) {
    // one operator:
    // "a+b"

    // find the operator
    auto operator_position =
        std::find_if(expression.begin(), expression.end(), [&](const char& c) {
          return std::find(operators.begin(), operators.end(),
                           std::string(1, c)) != operators.end();
        });

    // split the expression into two parts
    std::string first_part =
        expression.substr(0, operator_position - expression.begin());
    std::string second_part =
        expression.substr(operator_position - expression.begin() + 1);

    // return the tuple
    return std::make_tuple(first_part, std::string(1, *operator_position),
                           second_part);
  } else if (operator_count == 2) {
    // two operators:
    // "+a+b"
    // "a++b"

    std::string first_part;
    std::string operator_1;
    std::string second_part;
    std::string operator_2;
    std::string third_part;

    auto it = expression.begin();
    if (std::find(operators.begin(), operators.end(), std::string(1, *it)) !=
        operators.end()) {
      // first character is an operator
      operator_1 = std::string(1, *it);
      it++;
    }

    auto operator_position =
        std::find_if(it, expression.end(), [&](const char& c) {
          return std::find(operators.begin(), operators.end(),
                           std::string(1, c)) != operators.end();
        });

    first_part =
        expression.substr(it - expression.begin(), operator_position - it);
    operator_2 = std::string(1, *operator_position);
    third_part = expression.substr(operator_position - expression.begin() + 1);

    // return the tuple
    return std::make_tuple(operator_1 + first_part, operator_2, third_part);
  } else if (operator_count == 3) {
    // three operators:
    // "+a++b"

    std::string first_part;
    std::string operator_1;
    std::string second_part;
    std::string operator_2;
    std::string operator_3;
    std::string third_part;

    auto it = expression.begin();
    if (std::find(operators.begin(), operators.end(), std::string(1, *it)) !=
        operators.end()) {
      // first character is an operator
      operator_1 = std::string(1, *it);
      it++;
    }

    auto operator_position =
        std::find_if(it, expression.end(), [&](const char& c) {
          return std::find(operators.begin(), operators.end(),
                           std::string(1, c)) != operators.end();
        });

    first_part =
        expression.substr(it - expression.begin(), operator_position - it);
    operator_2 = std::string(1, *operator_position);
    it = operator_position + 1;

    operator_position = std::find_if(it, expression.end(), [&](const char& c) {
      return std::find(operators.begin(), operators.end(), std::string(1, c)) !=
             operators.end();
    });

    second_part =
        expression.substr(it - expression.begin(), operator_position - it);
    operator_3 = std::string(1, *operator_position);
    third_part = expression.substr(operator_position - expression.begin() + 1);

    // return the tuple
    return std::make_tuple(operator_1 + first_part, operator_2 + second_part,
                           operator_3 + third_part);
  }

  // invalid expression
  throw std::invalid_argument("invalid expression");
}