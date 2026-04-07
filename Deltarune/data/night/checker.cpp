#include "testlib.h"
#include <vector>

constexpr int N = 19, LIM = 3.2e6;

void solve() {
  int n = inf.readInt();
  std::vector<int> p(1 << n);
  for (int i = 0; i < (1 << n); ++i)
    p[i] = inf.readInt();
  std::vector<int> q(1 << n);
  for (int i = 0; i < (1 << n); ++i)
    q[i] = inf.readInt();
  int m = ouf.readInt(0, LIM);
  ouf.readEoln();
  for (int i = 1; i <= m; ++i) {
    const int x = ouf.readInt(0, (1 << n) - 1);
    ouf.readSpace();
    const int y = ouf.readInt(0, (1 << n) - 1);
    ouf.readEoln();
    if (x == y)
      quitf(_wa, "fail to swap: i = j");
    if ((p[x] ^ p[y]) > (x ^ y))
      quitf(_wa, "fail to swap: p_i \\oplus p_j > i \\oplus j");
    std::swap(p[x], p[y]);
  }
  for (int i = 0; i < (1 << n); ++i) {
    if (p[i] != q[i])
      quitf(_wa, "fake method: p[%d]=%d but q[%d]=%d", i, p[i], i, q[i]);
  }
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  int T = inf.readInt();
  for (int i = 1; i <= T; ++i) {
    setTestCase(i);
    solve();
  }
  quitf(_ok, "Good job!");
  return 0;
}
