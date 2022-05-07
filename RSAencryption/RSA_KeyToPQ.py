import random
# from Exp1.fastPower import *
# from Exp1.extEuclid import *


def euclid(a, b):
    if b == 0: return 0
    while b:
        r = a % b
        a, b = b, r
    return a


def getpq(n, e, d):
    p = q = 1
    while p == 1 and q == 1:
        f = d * e - 1
        g = random.randint(0, n)
        while p == 1 and q == 1 and f % 2 == 0:
            f //= 2
            y = pow(g, f, n)
            if y != 1 and euclid(y - 1, n) > 1:
                p = euclid(y - 1, n)
                q = n // p
    return p, q


if __name__ == '__main__':
    e = int(input())
    d = int(input())
    n = int(input())
    p, q = getpq(n, e, d)
    if p < q:
        print(p)
        print(q)
    else:
        print(q)
        print(p)
