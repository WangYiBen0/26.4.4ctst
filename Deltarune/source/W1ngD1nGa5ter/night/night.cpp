#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace W1ngD1nGa5ter {

using u64 = std::uint64_t;

class Solution {
  struct Input {
    int n;
    friend std::istream &operator>>(std::istream &in, Input &x) noexcept {
      return in >> x.n;
    }
  };

  void rearrange(int l, int r, std::vector<int> &p, std::vector<int> &idx,
                 std::vector<std::pair<int, int>> &res) const noexcept {
    if (r - l == 1) {
      return;
    }

    int mid = (l + r) >> 1;
    int h = 31 - __builtin_clz(r - l) - 1;
    bool flag[2] = {false, false};

    for (int i{l}; i < mid; ++i) {
      flag[(p[i] >> h) & 1] = true;
    }

    if (!flag[1]) {
      rearrange(l, mid, p, idx, res);
      rearrange(mid, r, p, idx, res);
      return;
    }

    if (!flag[0]) {
      for (int i{mid}; i < r; ++i) {
        if ((p[i] & ((1 << h) - 1)) == (p[l] & ((1 << h) - 1))) {
          res.push_back({i, l});
          std::swap(p[i], p[l]);
          break;
        }
      }
    }

    const int mask = (1 << (h + 1)) - 1;
    const int msk = (1 << h) - 1;
    int cp[2];

    for (int i{mid}; i < r; ++i) {
      cp[(p[i] >> h) & 1] = i;
    }

    for (int i{l}; i < r; ++i)
      idx[p[i] & mask] = i;

    for (int i{l}; i < mid; ++i) {
      int ep = idx[(i & msk) | (((p[i] >> h) & 1) << h)];
      if (ep == i)
        continue;
      int hb = (p[i] >> h) & 1;
      if (ep < mid) {
        res.push_back({ep, cp[hb]});
        std::swap(p[ep], p[cp[hb]]);
        std::swap(idx[p[ep] & mask], idx[p[cp[hb]] & mask]);
        ep = cp[hb];
      }
      res.push_back({ep, i});
      std::swap(p[ep], p[i]);
      std::swap(idx[p[ep] & mask], idx[p[i] & mask]);
    }

    for (int i{l}; i < mid; ++i) {
      if (!((p[i] >> h) & 1))
        continue;
      int ep = idx[i & msk];
      res.push_back({i, ep});
      std::swap(p[i], p[ep]);
      std::swap(idx[p[ep] & mask], idx[p[i] & mask]);
    }
    rearrange(mid, r, p, idx, res);
  }

public:
  int operator()(std::istream &in, std::ostream &out,
                 std::ostream &err = std::cerr,
                 std::ostream &log = std::clog) const noexcept {
    Input input;
    if (!(in >> input))
      return 0;

    int total_size = 1 << input.n;
    std::vector<int> p(total_size), q(total_size), idx(total_size);
    for (int i{}; i < total_size; ++i)
      in >> p[i];
    for (int i{}; i < total_size; ++i)
      in >> q[i];

    std::vector<std::pair<int, int>> ans, res;
    ans.reserve(total_size * input.n);
    res.reserve(total_size * input.n);

    std::vector<int> p_copy = p;
    rearrange(0, total_size, p_copy, idx, ans);
    std::vector<int> q_copy = q;
    rearrange(0, total_size, q_copy, idx, res);

    std::reverse(res.begin(), res.end());

    out << (ans.size() + res.size()) << '\n';
    for (const auto &pair : ans) {
      out << pair.first << ' ' << pair.second << '\n';
    }
    for (const auto &pair : res) {
      out << pair.first << ' ' << pair.second << '\n';
    }

    return 0;
  }
};
} // namespace W1ngD1nGa5ter

int main() noexcept {
  std::ios_base::sync_with_stdio(false);

  std::ifstream in("night.in");
  std::ofstream out("night.out");

  // std::cin.tie(nullptr);
  // std::istream &in(std::cin);
  // std::ostream &out(std::cout);

  int _T{1};
  if (!(in >> _T))
    return 0;
  for (int _I{}; _I < _T; ++_I) {
    if (W1ngD1nGa5ter::Solution{}(in, out)) {
      return 1;
    }
  }
  out << std::flush;
  return 0;
}
