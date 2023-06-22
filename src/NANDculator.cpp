#include <iostream>
#include <vector>

#include "logic/nand.hpp"
#include <cassert>

template <typename T>
std::vector<bool> to_bv(T a) {
  std::vector<bool> bv;
  // iterate over the bits of "a"
  size_t bits = sizeof(T) * 8;
  for (int i = 0; i < bits; i++) {
    // check if the ith bit is set
    bv.push_back(a & (1 << i));
  }
  return bv;
}

template <typename T>
T from_bv(const std::vector<bool>& bv) {
  T a = 0;
  for (int i = 0; i < bv.size(); i++) {
    if (bv[i]) {
      a |= (1 << i);
    }
  }
  return a;
}

int main() {
  int a = 0b1010;

  // convert the integer a to a bitvector of size 4
  auto bv = to_bv(a);

  auto out = nandculator::logic::bvadd(to_bv(5), to_bv(-5));

  auto b = from_bv<int>(out);

  // auto b = from_bv<int>(bv);

  // unit tests with asserts for bvadd
  assert(nandculator::logic::bvadd(to_bv(5), to_bv(0)) == to_bv(5));
  assert(nandculator::logic::bvadd(to_bv(0), to_bv(5)) == to_bv(5));
  assert(nandculator::logic::bvadd(to_bv(5), to_bv(5)) == to_bv(10));
  assert(nandculator::logic::bvadd(to_bv(5), to_bv(-5)) == to_bv(0));
  assert(nandculator::logic::bvadd(to_bv(-5), to_bv(5)) == to_bv(0));
  assert(nandculator::logic::bvadd(to_bv(-5), to_bv(-5)) == to_bv(-10));

  return 0;
}