# CPS-P Solution.md

## Chapter 1: The Beginning (`begin`)

link:  
<https://www.luogu.com.cn/problem/T744752>  
XOR and Ugly Equation

难度：绿  
算法：Kitty_Milk  
出题人：Gold.

---

易得。

观察到 $[a \& 1]$ 时无解，否则输出 `YES`。

输出答案即可。

然后就做完了。

## Chapter 2: The Cyber's World (`cyber`)

link:  
<https://www.luogu.com.cn/problem/P12828>  
「DLESS-2」XOR and Number Theory

难度：紫  
算法：树轮（CRT）  
出题人：Gold.

---

原文：[XOR and Number Theory 题解](https://www.luogu.com.cn/article/gnn1prgh)

## Chapter 3: Late Night (`night`)

link:  
<https://www.luogu.com.cn/problem/不知道>  
XOR and Swap

难度：蓝  
算法：分治  
出题人：Gold.

---

考虑到一定有解，所以把两个排列都变成 $0,1,2,\dots,2^n-1$，然后把 $q$ 变成这个排列的过程反转一下，接下来只需考虑如何在一半的次数内将 $p$ 变成 $0,1,2,\dots,2^n-1$ 即可。

分治，分成左右两半，如果第 $n$ 位为 $0$ 的都在左侧，为 $1$ 的都在右侧，那么直接往左右两侧递归就可以，此时 $T(n)=2T(n-1)$。

否则，如果为 $1$ 的都在左侧，为 $0$ 的都在右侧，那么我们任意取左右两侧一对前 $n-1$ 位相同的数，这两个数一定可以交换，接下来只考虑左右两侧的第 $n$ 位都同时有 $0$ 和 $1$ 的情况。

对于左侧，我们尝试在保持 $p_i$ 的第 $n$ 位不变的情况下，让 $p_i$ 的前 $n-1$ 位与 $i$ 的相同，由于左右两侧第 $n$ 位相同的数可以任意交换，所以，我们可以借助右侧的一个最高位与这个数相同的数，使用最多两次交换操作把需要的数换到这个位置上。

然后，左右两侧前 $n-1$ 位相同的数可以任意交换，所以可以使得左侧 $p_i$ 的前 $n$ 位都与 $i$ 相同，此时，左侧花费最多 $3\cdot 2^{n-1}$ 次操作，并且只需往右侧递归，$T(n)=3\cdot 2^{n-1}+T(n-1)$。

容易发现 $T(n)= 3\cdot 2^n$，不超过总次数限制的一半。

## Chapter 4: Prophecy (`prophecy`)

link:  
<https://www.luogu.com.cn/problem/P13685>  
【MX-X16-T3】「DLESS-3」XOR and Impossible Problem

难度：黄  
算法：思路简单 Ad-hoc 好题  
出题人：Gold.

---

注意到对 $2^{64}$ 取模，这很不对劲。  
以往的取模题一般都是对一个质数，像这样 $2^{64}$ 性质太好了。

我们把 $a$ 拆分成两个集合 $A_0=\{a_i \mid a_i \equiv 0 \pmod{2}\},A_1=\{a_i \mid a_i \equiv 1 \pmod{2}\}$

注意到 $A_0$ 中的数两两异或都是偶数，$A_1$ 也是。

我们发现当 $n>64$ 时答案肯定为 `0`（不严格，具体临界值自己算）。

于是 $n\le 64$ 时直接做，$n>64$ 时直接输出 `0` 即可。
