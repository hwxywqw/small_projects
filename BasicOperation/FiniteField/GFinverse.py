from Exp2.GFextEuclid import *


def inverse(n):
    return euclid_ex(n, irrP)[1]


if __name__ == '__main__':
    n = int(input(), 16)
    print("%02x " % inverse(n))