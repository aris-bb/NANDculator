#pragma once

#include "arithmetic.hpp"

#include <algorithm>
#include <stdexcept>

#include "../logic/bitvector.hpp"
#include "../logic/boolean.hpp"

using namespace nandculator;
using namespace logic;

std::pair<bool, bool> half_adder(bool a, bool b) {
  return {boolean::b_and(a, b), boolean::b_xor(a, b)};
}

std::pair<bool, bool> full_adder(bool a, bool b, bool c) {
  auto [c1, s1] = half_adder(a, b);
  auto [c2, s2] = half_adder(s1, c);
  return {boolean::b_or(c1, c2), s2};
}

bool bv_lt(const std::vector<bool>& a, const std::vector<bool>& b) {
  for (int i = static_cast<int>(a.size()) - 1; i >= 0; i--) {
    if (boolean::b_xor(a[i], b[i])) {
      return b[i];
    }
  }
  return false;
}

std::vector<bool> bv_neg(const std::vector<bool>& a) {
  return arithmetic::bv_sub(std::vector<bool>(a.size(), false), a);
}

std::vector<bool> bv_abs(const std::vector<bool>& a) {
  if (a.back()) {
    return bv_neg(a);
  } else {
    return a;
  }
}

std::vector<bool> arithmetic::bv_add(const std::vector<bool>& a,
                                     const std::vector<bool>& b) {
  std::vector<bool> result;
  bool c = false;
  for (int i = 0; i < a.size(); i++) {
    auto [c1, s1] = full_adder(a[i], b[i], c);
    result.push_back(s1);
    c = c1;
  }
  result.push_back(c);
  return result;
}

std::vector<bool> arithmetic::bv_sub(const std::vector<bool>& minuend,
                                     const std::vector<bool>& subtrahend) {
  auto ones_complement = bitvector::bv_not(subtrahend);

  // add 1 to ones complement
  auto one = std::vector<bool>(subtrahend.size(), false);
  one[0] = true;

  auto twos_complement = bv_add(ones_complement, one);
  return bv_add(minuend, twos_complement);
}

std::vector<bool> arithmetic::bv_mul(const std::vector<bool>& a,
                                     const std::vector<bool>& b) {
  std::vector<bool> result(a.size() + b.size(), false);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      if (boolean::b_and(a[i], b[j])) {
        std::vector<bool> temp(a.size() + b.size(), false);
        temp[i + j] = true;
        result = bv_add(result, temp);
        // ignore any overflow
        result.resize(a.size() + b.size());
      }
    }
  }
  return result;
}

std::vector<bool> arithmetic::bv_div(const std::vector<bool>& dividend,
                                     const std::vector<bool>& divisor) {
  if (std::all_of(divisor.begin(), divisor.end(),
                  [](bool bit) { return boolean::b_not(bit); })) {
    throw std::invalid_argument("Division by zero");
  }

  // determine if result is negative
  const bool negative = boolean::b_xor(dividend.back(), divisor.back());

  // convert to positive if negative
  std::vector<bool> abs_dividend = bv_abs(dividend);
  std::vector<bool> abs_divisor = bv_abs(divisor);

  // initialize quotient and remainder to 0
  std::vector<bool> quotient(abs_dividend.size(), false);
  std::vector<bool> remainder(abs_dividend.size(), false);

  for (int i = static_cast<int>(abs_dividend.size()) - 1; i >= 0; i--) {
    remainder.insert(remainder.begin(), abs_dividend[i]);

    // bv_lt needs both vectors to be the same size
    remainder.resize(abs_divisor.size());

    if (!bv_lt(remainder, abs_divisor)) {
      remainder = bv_sub(remainder, abs_divisor);
      quotient[i] = true;
    }
  }

  // if result should be negative, return the negative of the positive result
  if (negative) {
    return bv_neg(quotient);
  } else {
    return quotient;
  }
}