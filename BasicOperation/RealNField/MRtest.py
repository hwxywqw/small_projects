import secrets
from fastPower import *


def primetest(n):
    k, q = 0, n - 1
    while q % 2 == 0:  # 求k和q，使n-1=2^k*q
        k += 1
        q >>= 1
    a = secrets.randbelow(n - 1) + 1  # 生成随机数
    if fastPower(a, q, n) == 1:  # a^q与n互素，素数
        return True
    for i in range(k):
        if fastPower(a, (1 << i) * q, n) == n - 1:
            return True
    return False


def main():
    a = int(input())
    for i in range(1, 15):
        if primetest(a) == True:
            print("YES")
            return 0
    print("NO")
    return 0


if __name__ == '__main__':
    main()
    # print("YES" if (primetest(int(input())) == True) else "NO")