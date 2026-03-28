T4

link:
https://www.luogu.com.cn/problem/P13685
【MX-X16-T3】「DLESS-3」XOR and Impossible Problem

难度：黄  
算法：思路简单 Ad-hoc 好题  
出题人：Gold.

注意到对 $2^{64}$ 取模，这很不对劲。  
以往的取模题一般都是对一个质数，像这样 $2^{64}$ 性质太好了。

我们把 $a$ 拆分成两个集合 $A_0=\{a_i \mid a_i \equiv 0 \pmod{2}\},A_1=\{a_i \mid a_i \equiv 1 \pmod{2}\}$

注意到 $A_0$ 中的数两两异或都是偶数，$A_1$ 也是。

我们发现当 $n>64$ 时答案肯定为 `0`（不严格，具体临界值自己算）。

于是 $n\le 64$ 时直接做，$n>64$ 时直接输出 `0` 即可。
