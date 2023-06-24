#pragma once

#include "boolean.hpp"

using namespace nandculator::logic;

// each function is implemented using only nand
bool boolean::b_nand(bool a, bool b) { return !(a && b); }

bool boolean::b_and(bool a, bool b) {
  return b_nand(b_nand(a, b), b_nand(a, b));
}

bool boolean::b_xor(bool a, bool b) {
  return b_nand(b_nand(a, b_nand(a, b)), b_nand(b, b_nand(a, b)));
}

bool boolean::b_or(bool a, bool b) {
  return b_nand(b_nand(a, a), b_nand(b, b));
}

bool boolean::b_not(bool a) { return b_nand(a, a); }