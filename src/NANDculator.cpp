#include <iostream>
#include <string>
#include <vector>

#include "arithmetic/arithmetic.hpp"
#include "helper.hpp"

#define RUN_TESTS 1

#if RUN_TESTS
#include "NANDculator.tests.hpp"
#endif

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> result;
  std::string temp = "";
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == delimiter) {
      result.push_back(temp);
      temp = "";
    } else {
      temp += str[i];
    }
  }
  result.push_back(temp);
  return result;
}

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
  std::vector<std::string> input_array;
  while (true) {
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);
    input_array = split(input, ' ');
    if (input_array.size() != 3) {
      std::cout << "Invalid input. Please try again." << std::endl;
      continue;
    }

    int64_t a = 0;
    try {
      a = std::stoll(input_array[0]);
    } catch (std::out_of_range&) {
      std::cout << "The first input value is out of range. Please try again."
                << std::endl;
      continue;
    }

    int64_t b = 0;
    try {
      b = std::stoll(input_array[2]);
    } catch (std::out_of_range&) {
      std::cout << "The second input value is out of range. Please try again."
                << std::endl;
      continue;
    }

    // convert to bitvector
    auto bv_a = nandculator::helper::to_bv(a);
    auto bv_b = nandculator::helper::to_bv(b);

    std::string op = input_array[1];
    std::vector<bool> bv_result;
    if (op == "+") {
      bv_result = nandculator::arithmetic::bv_add(bv_a, bv_b);
    } else if (op == "-") {
      bv_result = nandculator::arithmetic::bv_sub(bv_a, bv_b);
    } else if (op == "*") {
      bv_result = nandculator::arithmetic::bv_mul(bv_a, bv_b);
    } else if (op == "/") {
      // check div by 0 here
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