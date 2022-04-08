# coding=utf-8

from GFextEuclid import *


def power(a, b):
    result = 1
    while b != 0:
        if b % 2 == 1:
            result = result * a
        b >>= 1
        a = a * a
    return result


def poly(n):  # 生成n次本原多项式
    scope = [2, 3, 7, 11, 13, 19, 25, 31]
    result = []
    for i in range(257, 512, 2):
        flag = 0
        for k in range(len(scope)):
            if euclid_ex(i, scope[k])[0] != 1:
                flag = 1
                break
        if flag == 0:
            for j in range(8, 255):
                tmp = power(2, j) + 1
                if divide(tmp, i)[1] == 0:
                    flag = 1
                    break
        if flag == 0:
            result.append(i)
    return result


if __name__ == '__main__':
    ans = poly(8)
    for num in ans:
        print(bin(num)[2:] + " ", end="")
