from Exp1.extEuclid import *
from Exp1.fastPower import *


def RSA_CMA(e1, e2, c1, c2, n):
    gcd, r, s = euclid_ex(e1, e2)
    if r < 0:
        c1 = inv(c1, n)
        r *= -1
    elif s < 0:
        c2 = inv(c2, n)
        s *= -1
    result = fastPower(c1, r, n)
    result *= fastPower(c2, s, n)
    result %= n
    return result


if __name__ == '__main__':
    e1 = int(input())
    e2 = int(input())
    c1 = int(input())
    c2 = int(input())
    n = int(input())
    p = RSA_CMA(e1, e2, c1, c2, n)
    print(p)
