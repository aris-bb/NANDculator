#pragma once

#include "bitvector.hpp"

#include "boolean.hpp"

using namespace nandculator::logic;

std::vector<bool> bitvector::bv_nand(const std::vector<bool>& a,
                                     const std::vector<bool>& b) {
  std::vector<bool> result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(boolean::b_nand(a[i], b[i]));
  }
  return result;
}

std::vector<bool> bitvector::bv_and(const std::vector<bool>& a,
                                    const std::vector<bool>& b) {
  return bv_nand(bv_nand(a, b), bv_nand(a, b));
}

std::vector<bool> bitvector::bv_or(const std::vector<bool>& a,
                                   const std::vector<bool>& b) {
  return bv_nand(bv_nand(a, a), bv_nand(b, b));
}

std::vector<bool> bitvector::bv_not(const std::vector<bool>& a) {
  return bv_nand(a, a);
}

std::vector<bool> bitvector::bv_xor(const std::vector<bool>& a,
                                    const std::vector<bool>& b) {
  return bv_nand(bv_nand(bv_nand(a, b), a), bv_nand(bv_nand(a, b), b));
}