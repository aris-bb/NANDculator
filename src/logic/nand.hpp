#pragma once

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

// long multiplication
std::vector<bool> bvmul(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  std::vector<bool> result(a.size() + b.size(), false);
  for (int i = 0; i < a.size(); i++) {
    std::vector<bool> temp(b.size() + i, false);
    if (a[i]) {
      for (int j = 0; j < b.size(); j++) {
        temp.push_back(b[j]);
      }
      result = bvadd(result, temp);
    }
  }
  return result;
}

// this is off by one i think, investigate further
std::vector<bool> bvsub(const std::vector<bool>& a,
                        const std::vector<bool>& b) {
  return bvadd(a, bvnand(b, b));
}

}  // namespace nandculator::logic
