#include "NANDculator.tests.hpp"

#include <cassert>

#include "arithmetic/arithmetic.hpp"
#include "helper.hpp"

using namespace nandculator::helper;
using namespace nandculator::arithmetic;

// TODO: use a unit testing framework
void nandculator::tests::run() {
  // unit tests with asserts for bv_add
  assert(from_bv<int64_t>(bv_add(to_bv(5i64), to_bv(0i64))) == 5);
  assert(from_bv<int64_t>(bv_add(to_bv(0i64), to_bv(5i64))) == 5);
  assert(from_bv<int64_t>(bv_add(to_bv(5i64), to_bv(5i64))) == 10);
  assert(from_bv<int64_t>(bv_add(to_bv(5i64), to_bv(-5i64))) == 0);
  assert(from_bv<int64_t>(bv_add(to_bv(-5i64), to_bv(5i64))) == 0);
  assert(from_bv<int64_t>(bv_add(to_bv(-5i64), to_bv(-5i64))) == -10);
  assert(from_bv<int64_t>(bv_add(to_bv(-5i64), to_bv(0i64))) == -5);
  assert(from_bv<int64_t>(bv_add(to_bv(0i64), to_bv(-5i64))) == -5);
  assert(from_bv<int64_t>(bv_add(to_bv(9999i64), to_bv(1i64))) == 10000);
  assert(from_bv<int64_t>(bv_add(to_bv(1i64), to_bv(9999i64))) == 10000);
  assert(from_bv<int64_t>(bv_add(to_bv(9999i64), to_bv(9999i64))) == 19998);
  assert(from_bv<int64_t>(bv_add(to_bv(9999i64), to_bv(-9999i64))) == 0);
  assert(from_bv<int64_t>(bv_add(to_bv(-9999i64), to_bv(9999i64))) == 0);
  assert(from_bv<int64_t>(bv_add(to_bv(-9999i64), to_bv(-9999i64))) == -19998);
  assert(from_bv<int64_t>(bv_add(to_bv(-9999i64), to_bv(0i64))) == -9999);
  assert(from_bv<int64_t>(bv_add(to_bv(0i64), to_bv(-9999i64))) == -9999);

  // unit tests with asserts for bv_sub
  assert(from_bv<int64_t>(bv_sub(to_bv(5i64), to_bv(0i64))) == 5);
  assert(from_bv<int64_t>(bv_sub(to_bv(0i64), to_bv(5i64))) == -5);
  assert(from_bv<int64_t>(bv_sub(to_bv(5i64), to_bv(5i64))) == 0);
  assert(from_bv<int64_t>(bv_sub(to_bv(5i64), to_bv(-5i64))) == 10);
  assert(from_bv<int64_t>(bv_sub(to_bv(-5i64), to_bv(5i64))) == -10);
  assert(from_bv<int64_t>(bv_sub(to_bv(-5i64), to_bv(-5i64))) == 0);
  assert(from_bv<int64_t>(bv_sub(to_bv(-5i64), to_bv(0i64))) == -5);
  assert(from_bv<int64_t>(bv_sub(to_bv(0i64), to_bv(-5i64))) == 5);
  assert(from_bv<int64_t>(bv_sub(to_bv(1i64), to_bv(9999i64))) == -9998);
  assert(from_bv<int64_t>(bv_sub(to_bv(9999i64), to_bv(1i64))) == 9998);
  assert(from_bv<int64_t>(bv_sub(to_bv(9999i64), to_bv(9999i64))) == 0);
  assert(from_bv<int64_t>(bv_sub(to_bv(9999i64), to_bv(-9999i64))) == 19998);
  assert(from_bv<int64_t>(bv_sub(to_bv(-9999i64), to_bv(9999i64))) == -19998);
  assert(from_bv<int64_t>(bv_sub(to_bv(-9999i64), to_bv(-9999i64))) == 0);
  assert(from_bv<int64_t>(bv_sub(to_bv(-9999i64), to_bv(0i64))) == -9999);
  assert(from_bv<int64_t>(bv_sub(to_bv(0i64), to_bv(-9999i64))) == 9999);

  // unit tests with asserts for bv_mul
  assert(from_bv<int64_t>(bv_mul(to_bv(5i64), to_bv(0i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(0i64), to_bv(5i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(5i64), to_bv(5i64))) == 25);
  assert(from_bv<int64_t>(bv_mul(to_bv(5i64), to_bv(-5i64))) == -25);
  assert(from_bv<int64_t>(bv_mul(to_bv(-5i64), to_bv(5i64))) == -25);
  assert(from_bv<int64_t>(bv_mul(to_bv(-5i64), to_bv(-5i64))) == 25);
  assert(from_bv<int64_t>(bv_mul(to_bv(-5i64), to_bv(0i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(0i64), to_bv(-5i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(9999i64), to_bv(1i64))) == 9999);
  assert(from_bv<int64_t>(bv_mul(to_bv(1i64), to_bv(9999i64))) == 9999);
  assert(from_bv<int64_t>(bv_mul(to_bv(9999i64), to_bv(9999i64))) == 99980001);
  assert(from_bv<int64_t>(bv_mul(to_bv(9999i64), to_bv(-9999i64))) == -99980001);
  assert(from_bv<int64_t>(bv_mul(to_bv(-9999i64), to_bv(9999i64))) == -99980001);
  assert(from_bv<int64_t>(bv_mul(to_bv(-9999i64), to_bv(-9999i64))) == 99980001);
  assert(from_bv<int64_t>(bv_mul(to_bv(-9999i64), to_bv(0i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(0i64), to_bv(-9999i64))) == 0);
  assert(from_bv<int64_t>(bv_mul(to_bv(123456i64), to_bv(654321i64))) == 80779853376);

  // unit tests with asserts for bv_div
  assert(from_bv<int64_t>(bv_div(to_bv(5i64), to_bv(1i64))) == 5);
  assert(from_bv<int64_t>(bv_div(to_bv(5i64), to_bv(5i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(5i64), to_bv(-5i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-5i64), to_bv(5i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-5i64), to_bv(-5i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(-5i64), to_bv(1i64))) == -5);
  assert(from_bv<int64_t>(bv_div(to_bv(1i64), to_bv(-5i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0i64), to_bv(-5i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0i64), to_bv(5i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0i64), to_bv(1i64))) == 0);

  try {
    volatile auto result =
        from_bv<int64_t>(bv_div(to_bv(1i64), to_bv(0)));
    assert(false);
  } catch (const std::exception&) {
    assert(true);
  }

  try {
    volatile auto result =
        from_bv<int64_t>(bv_div(to_bv(5i64), to_bv(0)));
    assert(false);
  } catch (const std::exception&) {
    assert(true);
  }

  try {
    volatile auto result =
        from_bv<int64_t>(bv_div(to_bv(-5i64), to_bv(0)));
    assert(false);
  } catch (const std::exception&) {
    assert(true);
  }

  assert(from_bv<int64_t>(bv_div(to_bv(9999i64), to_bv(1i64))) == 9999);
  assert(from_bv<int64_t>(bv_div(to_bv(1i64), to_bv(9999i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(9999i64), to_bv(9999i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(9999i64), to_bv(-9999i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-9999i64), to_bv(9999i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-9999i64), to_bv(-9999i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(-9999i64), to_bv(1i64))) == -9999);
  assert(from_bv<int64_t>(bv_div(to_bv(1i64), to_bv(-9999i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0i64), to_bv(-9999i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0i64), to_bv(9999i64))) == 0);
  assert(from_bv<int64_t>(bv_div(to_bv(0x7FFFFFFFi64), to_bv(0x7FFFFFFFi64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(0x80000000i64), to_bv(0x80000000i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(0x80000001i64), to_bv(0x80000001i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(8000i64), to_bv(50i64))) == 160);
  assert(from_bv<int64_t>(bv_div(to_bv(12345678i64), to_bv(12345678i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(12345678i64), to_bv(-12345678i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-12345678i64), to_bv(12345678i64))) == -1);
  assert(from_bv<int64_t>(bv_div(to_bv(-12345678i64), to_bv(-12345678i64))) == 1);
  assert(from_bv<int64_t>(bv_div(to_bv(0x8000i64), to_bv(-0x8000i64))) == -1);

  // unit tests with asserts for split_by_operator
  assert(split_by_operator("2+2") == std::make_tuple("2", "+", "2"));
  assert(split_by_operator("2-2") == std::make_tuple("2", "-", "2"));
  assert(split_by_operator("2*2") == std::make_tuple("2", "*", "2"));
  assert(split_by_operator("2/2") == std::make_tuple("2", "/", "2"));
  assert(split_by_operator("2+-2") == std::make_tuple("2", "+", "-2"));
  assert(split_by_operator("2--2") == std::make_tuple("2", "-", "-2"));
  assert(split_by_operator("-2-2") == std::make_tuple("-2", "-", "2"));
  assert(split_by_operator("-2+2") == std::make_tuple("-2", "+", "2"));
  assert(split_by_operator("+2++2") == std::make_tuple("+2", "+", "+2"));
  assert(split_by_operator("-2+-2") == std::make_tuple("-2", "+", "-2"));
  assert(split_by_operator("-2--2") == std::make_tuple("-2", "-", "-2"));
}