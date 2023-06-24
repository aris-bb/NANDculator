#include <iostream>
#include <string>
#include <vector>

#include "arithmetic/arithmetic.hpp"
#include "helper.hpp"

#define RUN_TESTS 0

#if RUN_TESTS
#include "NANDculator.tests.hpp"
#endif

int main() {

#if RUN_TESTS
  nandculator::tests::run();
#endif

  std::cout << "Welcome to NANDculator, a calculator that is built using only "
               "NAND gates!"
            << std::endl;

  std::cout << "Enter two numbers and an operator to calculate. (ex. 2 + 2) "
            << std::endl;

  std::cout << "Supported operators: +, -, *, /" << std::endl;

  std::string input;
  while (true) {
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    // get rid of spaces
    input.erase(std::remove_if(input.begin(), input.end(), isspace),
                input.end());

    // parse the input
    int64_t a = 0, b = 0;
    std::string op;
    try {
      const auto& [a_str, op_str, b_str] =
          nandculator::helper::split_by_operator(input);

      op = op_str;

      try {
        a = std::stoll(a_str);
      } catch (std::out_of_range&) {
        std::cout << "The first input value is out of range. Please try again."
                  << std::endl;
        continue;
      }

      try {
        b = std::stoll(b_str);
      } catch (std::out_of_range&) {
        std::cout << "The second input value is out of range. Please try again."
                  << std::endl;
        continue;
      }
    } catch (const std::exception&) {
      std::cout << "Invalid input. Please try again." << std::endl;
      continue;
    }

    // convert to bitvector
    auto bv_a = nandculator::helper::to_bv(a);
    auto bv_b = nandculator::helper::to_bv(b);

    std::vector<bool> bv_result;
    if (op == "+") {
      bv_result = nandculator::arithmetic::bv_add(bv_a, bv_b);
    } else if (op == "-") {
      bv_result = nandculator::arithmetic::bv_sub(bv_a, bv_b);
    } else if (op == "*") {
      bv_result = nandculator::arithmetic::bv_mul(bv_a, bv_b);
    } else if (op == "/") {
      if (b == 0) {
        std::cout << "Cannot divide by zero. Please try again." << std::endl;
        continue;
      }
      bv_result = nandculator::arithmetic::bv_div(bv_a, bv_b);
    } else {
      std::cout << "Invalid operator. Please try again." << std::endl;
      continue;
    }

    std::cout << "Result: " << nandculator::helper::from_bv<int64_t>(bv_result)
              << std::endl;
  }

  return 0;
}