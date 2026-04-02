#include "testlib.h"
#include <vector>

using namespace std;

// 最大操作步数限制
const int LIMITATION = 3200000;

int main(int argc, char *argv[]) {
  // 初始化 testlib
  registerTestlibCmd(argc, argv);

  // 读取测试数据组数 T
  int T = inf.readInt();

  for (int t = 0; t < T; ++t) {
    setTestCase(t + 1); // 设置当前测试用例，方便报错时定位

    int n = inf.readInt();
    int size = 1 << n;

    // 读取原始排列 p
    vector<unsigned> p(size);
    for (int i = 0; i < size; ++i) {
      p[i] = inf.readInt();
    }

    // 读取目标排列 q
    vector<unsigned> q(size);
    for (int i = 0; i < size; ++i) {
      q[i] = inf.readInt();
    }

    // 读取选手输出的操作步数 m
    int m = ouf.readInt();
    if (m < 0 || m > LIMITATION) {
      quitf(_wa, "Too many operations: %d (limit: %d)", m, LIMITATION);
    }

    // 执行交换操作
    for (int i = 0; i < m; ++i) {
      // 读取交换下标 x, y
      int x = ouf.readInt(0, size - 1, "x");
      int y = ouf.readInt(0, size - 1, "y");

      if (x == y) {
        quitf(_wa, "Step %d: indices cannot be the same (x = y = %d)", i + 1,
              x);
      }

      // 检查交换条件: (p[x] ^ p[y]) <= (x ^ y)
      // 原代码逻辑: if ((p[x] ^ p[y]) > (x ^ y)) return WA;
      if ((p[x] ^ p[y]) > (unsigned(x ^ y))) {
        quitf(_wa,
              "Step %d: invalid swap. p[%d]=%u, p[%d]=%u. Condition "
              "(p[x]^p[y]) <= (x^y) failed.",
              i + 1, x, p[x], y, p[y]);
      }

      swap(p[x], p[y]);
    }

    // 检查最终结果是否匹配目标排列
    for (int i = 0; i < size; ++i) {
      if (p[i] != q[i]) {
        quitf(_wa,
              "Final permutation does not match q at index %d. Expected %u, "
              "found %u.",
              i, q[i], p[i]);
      }
    }
  }

  // 检查选手是否还有多余输出
  ouf.readEof();

  quitf(_ok, "%d test cases passed", T);
  return 0;
}
