#include "testlib_for_lemons.h"
#include <vector>

constexpr int LIMITATION = 3'200'000;

int main(int argc, char *argv[]) noexcept {
  // registerTestlibCmd(argc, argv);
  registerLemonChecker(argc, argv);

  const int T = inf.readInt();

  for (int t = 0; t < T; ++t) {
    setTestCase(t + 1);

    const int n = inf.readInt();
    const unsigned size = 1u << n;

    std::vector<unsigned> p(size);
    for (unsigned i = 0; i < size; ++i) {
      p[i] = inf.readInt();
    }

    std::vector<unsigned> q(size);
    for (unsigned i = 0; i < size; ++i) {
      q[i] = inf.readInt();
    }

    const unsigned m = ouf.readInt(0, LIMITATION, "m");
    ouf.readEoln();

    for (unsigned i = 0; i < m; ++i) {
      const unsigned x = ouf.readInt(0, size - 1, "x");
      ouf.readSpace();
      const unsigned y = ouf.readInt(0, size - 1, "y");
      ouf.readEoln();

      if (x == y) {
        quitf(_wa, "Step %d: indices cannot be the same (x = y = %d)", i + 1,
              x);
      }

      if ((p[x] ^ p[y]) > (unsigned(x ^ y))) {
        quitf(_wa,
              "Step %d: invalid swap. p[%d]=%u, p[%d]=%u. Condition "
              "(p[x]^p[y]) <= (x^y) failed.",
              i + 1, x, p[x], y, p[y]);
      }

      std::swap(p[x], p[y]);
    }

    for (unsigned i = 0; i < size; ++i) {
      if (p[i] != q[i]) {
        quitf(_wa,
              "Final permutation does not match q at index %d. Expected %u, "
              "found %u.",
              i, q[i], p[i]);
      }
    }
  }

  ouf.readEof();

  quitf(_ok, "%d test cases passed", T);
  return 0;
}
