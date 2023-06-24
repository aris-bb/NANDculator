#pragma once

#include <vector>

namespace nandculator::logic::bitvector {

std::vector<bool> bv_nand(const std::vector<bool>& a,
                          const std::vector<bool>& b);

std::vector<bool> bv_and(const std::vector<bool>& a,
                         const std::vector<bool>& b);

std::vector<bool> bv_or(const std::vector<bool>& a, const std::vector<bool>& b);

std::vector<bool> bv_not(const std::vector<bool>& a);

std::vector<bool> bv_xor(const std::vector<bool>& a,
                         const std::vector<bool>& b);

}  // namespace nandculator::logic::bitvector