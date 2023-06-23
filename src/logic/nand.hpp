#pragma once

#include <algorithm>

namespace nandculator::logic {

// functions prefixed with b are for boolean operations
// functions prefixed with bv are for bitvector operations

// nand is the only primitive operation

// boolean nand
bool bnand(bool a, bool b) { return !(a && b); }

// bitvector nand
std::vector<bool> bvnand(const std::vector<bool>& a,
                         const std::vector<bool>& b) {
  std::vector<bool> result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(bnand(a[i], b[i]));
  }
  return result;
}

// all other operations are derived from nand

bool band(bool a, bool b) { return bnand(bnand(a, b), bnand(a, b)); }

bool bxor(bool a, bool b) {
  return bnand(bnand(a, bnand(a, b)), bnand(b, bnand(a, b)));
}

bool bor(bool a, bool b) { return bnand(bnand(a, a), bnand(b, b)); }

std::vector<bool> bvand(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  return bvnand(bvnand(a, b), bvnand(a, b));
}

std::vector<bool> bvor(const std::vector<bool>& a, const std::vector<bool>& b) {
  return bvnand(bvnand(a, a), bvnand(b, b));
}

std::vector<bool> bvnot(const std::vector<bool>& a) { return bvnand(a, a); }

std::vector<bool> bvxor(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  return bvnand(bvnand(bvnand(a, b), a), bvnand(bvnand(a, b), b));
}

std::pair<bool, bool> half_adder(bool a, bool b) {
  return {band(a, b), bxor(a, b)};
}

std::pair<bool, bool> full_adder(bool a, bool b, bool c) {
  auto [c1, s1] = half_adder(a, b);
  auto [c2, s2] = half_adder(s1, c);
  return {bor(c1, c2), s2};
}

std::vector<bool> bvadd(const std::vector<bool>& a,
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

std::vector<bool> bvsub(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  auto ones_complement = bvnot(b);

  // add 1 to ones complement
  auto one = std::vector<bool>(b.size(), false);
  one[0] = true;

  auto twos_complement = bvadd(ones_complement, one);
  return bvadd(a, twos_complement);
}

// maybe we could do karatsuba multiplication here
std::vector<bool> bvmul(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  std::vector<bool> result(a.size() + b.size(), false);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      if (band(a[i], b[j])) {
        std::vector<bool> temp(a.size() + b.size(), false);
        temp[i + j] = true;
        result = bvadd(result, temp);
        // ignore any overflow
        result.resize(a.size() + b.size());
      }
    }
  }
  return result;
}

// less than
bool bvlt(const std::vector<bool>& a, const std::vector<bool>& b) {
  for (int i = a.size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      return b[i];
    }
  }
  return false;
}

std::vector<bool> bvdiv(const std::vector<bool>& dividend,
                        const std::vector<bool>& divisor) {
  if (std::all_of(divisor.begin(), divisor.end(),
                  [](bool bit) { return !bit; })) {
    throw std::invalid_argument("Division by zero");
  }

  // determine if result is negative
  bool negative = bxor(dividend.back(), divisor.back());

  // convert to positive if negative
  std::vector<bool> abs_dividend =
      dividend.back()
          ? bvsub(std::vector<bool>(dividend.size(), false), dividend)
          : dividend;
  std::vector<bool> abs_divisor =
      divisor.back() ? bvsub(std::vector<bool>(divisor.size(), false), divisor)
                     : divisor;

  // ensure both are the same size
  abs_dividend.resize(dividend.size());
  abs_divisor.resize(dividend.size());

  std::vector<bool> quotient(dividend.size(), false);
  std::vector<bool> remainder = abs_dividend;

  for (int i = dividend.size() - 1; i >= 0; i--) {
    std::vector<bool> divisor_shifted(i, false);
    divisor_shifted.insert(divisor_shifted.end(), abs_divisor.begin(),
                           abs_divisor.end());
    divisor_shifted.resize(dividend.size());

    if (!bvlt(remainder, divisor_shifted)) {
      remainder = bvsub(remainder, divisor_shifted);
      // ignore any overflow
      remainder.resize(dividend.size());
      quotient[i] = true;
    }
  }

  // If result is negative, return the two's complement of the quotient
  return negative ? bvsub(std::vector<bool>(dividend.size(), false), quotient)
                  : quotient;
}

}  // namespace nandculator::logic
