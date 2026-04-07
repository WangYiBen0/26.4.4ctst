#include <bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
using namespace std;
namespace FastIO {
const int BUF_SIZE = 1 << 20;
char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
char *in_ptr = in_buf + BUF_SIZE;
char *out_ptr = out_buf;
char get_char() {
  if (in_ptr == in_buf + BUF_SIZE) {
    in_ptr = in_buf;
    fread(in_buf, 1, BUF_SIZE, stdin);
  }
  return *in_ptr++;
}
void put_char(char c) {
  if (out_ptr == out_buf + BUF_SIZE) {
    fwrite(out_buf, 1, BUF_SIZE, stdout);
    out_ptr = out_buf;
  }
  *out_ptr++ = c;
}
struct Flusher {
  ~Flusher() {
    if (out_ptr != out_buf) {
      fwrite(out_buf, 1, out_ptr - out_buf, stdout);
    }
  }
} flusher;
} // namespace FastIO
#define getchar FastIO::get_char
#define putchar FastIO::put_char
inline int read() {
  int x = 0;
  bool zf = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      zf = 0;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return zf ? x : -x;
}
void print(cint x) {
  if (x == 0) {
    putchar('0');
    return;
  }
  char buf[12];
  int len = 0, y = x;
  if (y < 0) {
    putchar('-');
    y = -y;
  }
  while (y) {
    buf[len++] = (y % 10) + '0';
    y /= 10;
  }
  while (len--) {
    putchar(buf[len]);
  }
}
inline void princh(cint x, const char ch) {
  print(x);
  putchar(ch);
}
cint N = 19;
int n;
int p[1 << N], q[1 << N];
#define pair pair<int, int>
#define x first
#define y second
vector<pair> res, ans;
int idx[1 << N];
void doit(cint l, cint r, int p[], vector<pair> &res) {
  if (r - l == 1)
    return;
  // printf("[%d,%d)\n",l,r);
  cint mid = l + r >> 1;
  cint h = __lg(r - l) - 1;
  bool flag[2] = {0, 0};
  for (int i = l; i < mid; ++i) {
    flag[p[i] >> h & 1] = 1;
  }
  if (!flag[1]) {
    doit(l, mid, p, res);
    doit(mid, r, p, res);
    return;
  }
  if (!flag[0]) {
    for (int i = mid; i < r; ++i) {
      if ((p[i] & ((1 << h) - 1)) == (p[l] & ((1 << h) - 1))) {
        res.push_back(pair(i, l));
        // printf(">%d %d\n",i,l);
        swap(p[i], p[l]);
        break;
      }
    }
  }
  cint mask = (1 << h + 1) - 1, msk = (1 << h) - 1;
  int cp[2];
  for (int i = mid; i < r; ++i) {
    cp[p[i] >> h & 1] = i;
  }
  for (int i = l; i < r; ++i)
    idx[(p[i] & mask)] = i;
  for (int i = l; i < mid; ++i) {
    int ep = idx[(i & msk) | (((p[i] >> h & 1) << h))];
    if (ep == i)
      continue;
    cint hb = (p[i] >> h & 1);
    if (ep < mid) {
      res.push_back(pair(ep, cp[hb]));
      swap(p[ep], p[cp[hb]]);
      swap(idx[p[ep] & mask], idx[p[cp[hb]] & mask]);
      ep = cp[hb];
    }
    res.push_back(pair(ep, i));
    swap(p[ep], p[i]);
    swap(idx[p[ep] & mask], idx[p[i] & mask]);
  }
  for (int i = l; i < mid; ++i) {
    if (!(p[i] >> h & 1))
      continue;
    int ep = idx[i & msk];
    res.push_back(pair(i, ep));
    swap(p[i], p[ep]);
    swap(idx[p[ep] & mask], idx[p[i] & mask]);
  }
  doit(mid, r, p, res);
}
void solve() {
  n = read();
  for (int i = 0; i < (1 << n); ++i)
    p[i] = read();
  for (int i = 0; i < (1 << n); ++i)
    q[i] = read();
  ans.clear();
  res.clear();
  doit(0, (1 << n), p, ans);
  doit(0, (1 << n), q, res);
  reverse(res.begin(), res.end());
  princh(ans.size() + res.size(), '\n');
  for (pair p : ans) {
    princh(p.x, ' ');
    princh(p.y, '\n');
  }
  for (pair p : res) {
    princh(p.x, ' ');
    princh(p.y, '\n');
  }
}
int main() {
  freopen("night.in", "r", stdin);
  freopen("night.out", "w", stdout);
  int T = read();
  while (T--)
    solve();
  return 0;
}
