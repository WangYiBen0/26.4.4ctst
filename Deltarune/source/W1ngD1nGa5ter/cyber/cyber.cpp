#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace W1ngD1nGa5ter {

using u64 = std::uint64_t;

int bit_width(unsigned x) noexcept { return 32 - __builtin_clz(x); }

class InvDataBase {
  static constexpr int MASK = (1 << 30) - 1;
  std::vector<int> inv;

public:
  InvDataBase() {
    inv.reserve(1000001);
    inv.emplace_back(0);
  }

  int operator()(int x) {
    // assert(x % 2 == 1);
    if (x >= static_cast<int>(inv.size())) {
      int current = inv.size();
      int t = x;
      if ((t & 1) == 0)
        t |= 1;
      inv.resize(t + 1);
      int start = (current % 2 == 0) ? current + 1 : current;
      for (int i = start; i <= t; i += 2) {
        int a = i, b = 1;
        for (int j = 1; j <= 22; ++j) {
          b = ((1ll * b * a) & MASK);
          a = ((1ll * a * a) & MASK);
        }
        inv[i] = b;
      }
    }
    return inv[x];
  }
};

class Solution {
  static constexpr int MOD = 1'000'000'007;

public:
  Solution() noexcept {}

  int operator()(std::istream &in, std::ostream &out,
                 std::ostream &err = std::cerr,
                 std::ostream &log = std::clog) const noexcept {
    static InvDataBase inv;

    int n, m;
    in >> n >> m;

    int ans = -1ll * m * (m + 1) * (m * 2 + 1) / 6 % MOD;
    int base = 1;

    auto calc = [](int x, int y, int mod, int n) -> int {
      long long d = ((1ll * inv(x) * y) & (mod - 1)) * x;
      if (d > n)
        return 0;
      return static_cast<int>((n - d) / (1ll * x * mod) + 1);
    };

    auto solve = [calc](int cur_n, int cur_m, int cur_base, int &cur_ans) {
      int m_bits = bit_width(static_cast<unsigned>(cur_m));
      int M = (1 << m_bits) - 1;
      for (int i = 1; i <= M; i += 2) {
        int i_bits = bit_width(static_cast<unsigned>(i));
        int mod = 1 << i_bits;
        for (int j = i;; j = ((j - 2) & i)) {
          if (bit_width(static_cast<unsigned>(j)) != i_bits)
            break;
          if (j > cur_m)
            continue;
          cur_ans = (cur_ans + 1ll * cur_base * j * cur_base * j % MOD *
                                   calc(j, i, mod, cur_n)) %
                    MOD;
          if (j == 1)
            break;
        }
      }
    };

    while (m) {
      solve(n, m, base, ans);
      base <<= 1;
      n >>= 1;
      m >>= 1;
    }

    ans = (ans % MOD + MOD) % MOD;
    out << ans << '\n';
    return 0;
  }
};

} // namespace W1ngD1nGa5ter

int main() noexcept {
  std::ios_base::sync_with_stdio(false);
  std::ifstream in("cyber.in");
  std::ofstream out("cyber.out");
  // std::istream &in(std::cin);
  // std::ostream &out(std::cout);
  // std::cin.tie(nullptr);

  W1ngD1nGa5ter::Solution solution;
  int T = 1;
  in >> T;
  for (int t = 0; t < T; ++t) {
    if (solution(in, out))
      return 1;
  }
  out << std::flush;
  return 0;
}
