#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace W1ngD1nGa5ter {

using u64 = std::uint64_t;
class Solution {
  struct Input {
    int n;
    std::vector<std::uint64_t> a;
    friend std::istream &operator>>(std::istream &in, Input &x) noexcept {
      in >> x.n;
      x.a.resize(x.n);
      for (auto &i : x.a) {
        in >> i;
      }
      return in;
    }
  };

public:
  int operator()(std::istream &in, std::ostream &out,
                 std::ostream &err = std::cerr,
                 std::ostream &log = std::clog) const noexcept {
    Input input;
    in >> input;
    if (input.n > 64) {
      out << "0\n";
      return 0;
    }
    u64 ans{1};
    for (int i{}; i < input.n; ++i) {
      for (int j{i + 1}; j < input.n; ++j) {
        ans *= input.a[i] ^ input.a[j];
      }
    }
    out << ans << '\n';
    return 0;
  }
};
} // namespace W1ngD1nGa5ter

int main() noexcept {
  std::ios_base::sync_with_stdio(false);
  std::ifstream in("prophecy.in");
  std::ofstream out("prophecy.out");
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
