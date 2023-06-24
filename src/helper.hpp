#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace nandculator::helper {

// helpers for converting bitvectors to and from other types
// these are not implemented using nand gates, but everything else is

template <typename T>
std::vector<bool> to_bv(T value) {
  std::vector<bool> bv;
  // iterate over the bits of value
  const size_t bits = sizeof(T) * 8;
  for (int i = 0; i < bits; i++) {
    // check if the ith bit is set
    bv.push_back(value & (1i64 << i));
  }
  return bv;
}

template <typename T>
T from_bv(const std::vector<bool>& bv) {
  T result = 0;
  // iterate over either the size of bv, or the bit count of type T, whichever
  // is smaller
  const size_t bits = std::min(bv.size(), sizeof(T) * 8);
  for (int i = 0; i < bits; i++) {
    if (bv[i]) {
      result |= (1i64 << i);
    }
  }
  return result;
}

std::tuple<std::string, std::string, std::string> split_by_operator(
    const std::string& expression);

}  // namespace nandculator::helper