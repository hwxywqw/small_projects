from functools import reduce
from random import randint

from Exp1.extEuclid import *
from Exp1.fastPower import *
from Exp1.MRtest import *


def plainGen(n):  # 生成n位二进制素数
    ans = randint(2, 2 ** n)
    while not MRtest(ans, 80):
        ans = randint(2, 2 ** n)
    return ans

# 采用中国剩余定理简化运算——输入分别为: 列表m=[p, q], 密文c, 密钥d
def crt_2(m, c, d):
    a = []
    for k in m:
        tmp = fastPower(c, d, k)
        a.append(tmp)

    if a == [0, 0]:
        return reduce(lambda x, y: x*y//euclid(x, y), m)     # 特判，使输出最小正整数

    product = reduce(lambda x, y: x * y, m)
    result = 0
    for i in range(2):
        mi = product // m[i]
        invm = euclid_ex(mi, m[i])[1]  # 调用拓展欧几里得算法来求逆
        result = (result + a[i] * mi * invm) % product
    return result


if __name__ == '__main__':
    p = int(input())
    q = int(input())
    e = int(input())
    m = int(input())
    op = int(input())
    n = p * q

    if op == 1:     # 加密
        c = fastPower(m, e, n)
    else:           # 解密
        f_n = (p - 1) * (q - 1)
        d = inv(e, f_n)
        c = crt_2([p, q], m, d)
        # c = fastPower(m, d, n)

    print(c)