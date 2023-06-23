#include <cassert>
#include <iostream>
#include <vector>

#include "logic/nand.hpp"

template <typename T>
std::vector<bool> to_bv(T value) {
  std::vector<bool> bv;
  // iterate over the bits of value
  const size_t bits = sizeof(T) * 8;
  for (int i = 0; i < bits; i++) {
    // check if the ith bit is set
    bv.push_back(value & (1 << i));
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
      result |= (1 << i);
    }
  }
  return result;
}

int main() {
  int a = 0b1010;

  // convert the integer a to a bitvector of size 4
  auto bv = to_bv(a);

  auto out = nandculator::logic::bvadd(to_bv(5), to_bv(-5));

  auto b = from_bv<int>(out);

  // auto b = from_bv<int>(bv);

  // unit tests with asserts for bvadd
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(5), to_bv(0))) == 5);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(0), to_bv(5))) == 5);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(5), to_bv(5))) == 10);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(5), to_bv(-5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(-5), to_bv(5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(-5), to_bv(-5))) == -10);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(-5), to_bv(0))) == -5);
  assert(from_bv<int>(nandculator::logic::bvadd(to_bv(0), to_bv(-5))) == -5);

  // unit tests with asserts for bvsub
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(5), to_bv(0))) == 5);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(0), to_bv(5))) == -5);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(5), to_bv(5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(5), to_bv(-5))) == 10);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(-5), to_bv(5))) == -10);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(-5), to_bv(-5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(-5), to_bv(0))) == -5);
  assert(from_bv<int>(nandculator::logic::bvsub(to_bv(0), to_bv(-5))) == 5);

  // unit tests with asserts for bvmul
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(5), to_bv(0))) == 0);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(0), to_bv(5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(5), to_bv(5))) == 25);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(5), to_bv(-5))) == -25);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(-5), to_bv(5))) == -25);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(-5), to_bv(-5))) == 25);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(-5), to_bv(0))) == 0);
  assert(from_bv<int>(nandculator::logic::bvmul(to_bv(0), to_bv(-5))) == 0);

  // unit tests with asserts for bvdiv
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(5), to_bv(1))) == 5);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(5), to_bv(5))) == 1);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(5), to_bv(-5))) == -1);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(-5), to_bv(5))) == -1);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(-5), to_bv(-5))) == 1);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(-5), to_bv(1))) == -5);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(1), to_bv(-5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(0), to_bv(-5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(0), to_bv(5))) == 0);
  assert(from_bv<int>(nandculator::logic::bvdiv(to_bv(0), to_bv(1))) == 0);

  try {
    volatile auto result =
        from_bv<int>(nandculator::logic::bvdiv(to_bv(1), to_bv(0)));
    assert(false);
  } catch (const std::exception& e) {
    assert(true);
  }

  try {
    volatile auto result =
        from_bv<int>(nandculator::logic::bvdiv(to_bv(5), to_bv(0)));
    assert(false);
  } catch (const std::exception& e) {
    assert(true);
  }

  try {
    volatile auto result =
        from_bv<int>(nandculator::logic::bvdiv(to_bv(-5), to_bv(0)));
    assert(false);
  } catch (const std::exception& e) {
    assert(true);
  }

  return 0;
}