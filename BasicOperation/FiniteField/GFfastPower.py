from GF4opreations import *


def fastPower(a, b):
    a = divide(a, irrP)[1]
    result = 1
    while b != 0:
        if b % 2 == 1:
            result = multiply(result, a)
        b >>= 1
        a = multiply(a, a)
    return result


if __name__ == '__main__':
    "快速幂所用主函数"
    a, b = input().split()
    a = int(a, 16)
    b = int(b, 10)
    print("%02x " % fastPower(a, b))