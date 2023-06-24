#pragma once

#include <vector>

namespace nandculator::arithmetic {

std::vector<bool> bv_add(const std::vector<bool>& a,
                         const std::vector<bool>& b);

std::vector<bool> bv_sub(const std::vector<bool>& minuend,
                         const std::vector<bool>& subtrahend);

std::vector<bool> bv_mul(const std::vector<bool>& a,
                         const std::vector<bool>& b);

std::vector<bool> bv_div(const std::vector<bool>& dividend,
                         const std::vector<bool>& divisor);

}  // namespace nandculator::arithmetic