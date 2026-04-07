#include <cstdint>
#include <fstream>
#include <iostream>

namespace W1ngD1nGa5ter {

using u64 = std::uint64_t;
class Solution {
  struct Input {
    int k;
    u64 a;
    friend std::istream &operator>>(std::istream &in, Input &x) noexcept {
      in >> x.k >> x.a;
      return in;
    }
  };

public:
  int operator()(std::istream &in, std::ostream &out,
                 std::ostream &err = std::cerr,
                 std::ostream &log = std::clog) const noexcept {
    Input input;
    in >> input;
    if (input.a & 1) {
      out << "NO\n";
      return 0;
    }
    u64 x{}, y{1};
    for (int i{1}; i < input.k; ++i) {
      x |= (x * x ^ input.a) & (1ull << i);
      y |= (y * y ^ input.a) & (1ull << i);
    }
    out << "YES\n" << std::min(x, y) << '\n';
    return 0;
  }
};
} // namespace W1ngD1nGa5ter

int main() noexcept {
  std::ios_base::sync_with_stdio(false);
  std::ifstream in("begin.in");
  std::ofstream out("begin.out");
  // std::cin.tie(nullptr);
  // std::istream &in(std::cin);
  // std::ostream &out(std::cout);
  int _T{1};
  in >> _T;
  for (int _I{}; _I < _T; ++_I) {
    if (W1ngD1nGa5ter::Solution{}(in, out)) {
      return 1;
    }
  }
  out << std::flush;
  return 0;
}
