#include <bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch - '0');
    ch = getchar();
  }
  return x;
}
void print(cint x) {
  if (x < 10) {
    putchar(x + '0');
    return;
  }
  print(x / 10);
  putchar(x % 10 + '0');
}
void princh(cint x, const char ch) {
  print(x);
  putchar(ch);
}
cint p = 1e9 + 7;
int n, m;
int ans;
int inv[1000001], hb[1 << 20 | 1], chb[1 << 20 | 1];
void init() {
  cint M = (1 << 30) - 1;
  for (int i = 1; i <= 1e6; i += 2) {
    int a = i, b = 1;
    for (int j = 1; j <= 22; ++j) {
      b = ((1ll * b * a) & M);
      a = ((1ll * a * a) & M);
    }
    inv[i] = b;
  }
  for (int i = 1; i <= 1 << 20; ++i) {
    hb[i] = max(hb[i - 1], i & (-i));
    chb[i] = chb[i - 1] + (hb[i] != hb[i - 1]);
  }
}
int calc(cint x, cint y, cint mod) {
  cll d = ((1ll * inv[x] * y) & (mod - 1)) * x;
  return (d > n ? 0 : (n - d) / (1ll * x * mod) + 1);
}
int base;
void solve() {
  cint M = (1 << chb[m]) - 1;
  for (int i = 1; i <= M; i += 2) {
    cint mod = (1 << chb[i]);
    for (int j = i;; j = ((j - 2) & i)) {
      if (hb[j] != hb[i])
        break;
      if (j > m)
        continue;
      ans = (ans + 1ll * base * j * base * j % p * calc(j, i, mod)) % p;
      if (j == 1)
        break;
    }
  }
}
void doit() {
  n = read();
  m = read();
  base = 1;
  ans = -1ll * m * (m + 1) * (m << 1 | 1) / 6 % p;
  while (m) {
    solve();
    base <<= 1;
    n >>= 1;
    m >>= 1;
  }
  princh(ans, '\n');
}
int main() {
  freopen("cyber.in", "r", stdin), freopen("cyber.out", "w", stdout);
  init();
  int T = read();
  while (T--)
    doit();
  return 0;
}
