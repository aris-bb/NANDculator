#pragma once

namespace nandculator::logic::boolean {

// each function is implemented using only nand
bool b_nand(bool a, bool b);

bool b_and(bool a, bool b);
bool b_xor(bool a, bool b);
bool b_or(bool a, bool b);
bool b_not(bool a);

}  // namespace nandculator::logic::boolean