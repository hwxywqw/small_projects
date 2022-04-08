from functools import reduce
from extEuclid import *
from Eratosthenes import eratosthenes


def crt(m, a):  # 用了变长列表，方便日后在不定方程个数时调用
    # m, a = list(num[:len(num) // 2]), list(num[len(num) // 2:])  # 不分行输入时，切割list
    # m, a = process_prime(m, a)
    if a == [0, 0, 0]: return reduce(lambda x, y: x*y//euclid(x, y), m)     # 特判，使输出最小正整数
    product = reduce(lambda x, y: x * y, m)  # M = product(mi)
    result = 0
    for i in range(0, len(a)):
        mi = product // m[i]
        inv = euclid_ex(mi, m[i])[1]  # 调用拓展欧几里得算法来求逆
        result = (result + a[i] * mi * inv) % product
    return result


"当模数不互素时，设计了如下预处理函数，但是正确性无法保证。"
# def process_prime(lm, la):
#     for i in range(0, len(lm)-1):
#         for j in range(i+1, len(lm)-1):
#             temp = euclid(lm[i], lm[j])
#             if (temp != 1) & (lm[i] != lm[j]):
#                 lm.append(lm[i]//temp)
#                 la.append(la[i])
#                 lm.append(lm[j] // temp)
#                 la.append(la[j])
#     return lm, la


# m = list(map(int, input().split()))
# a = list(map(int, input().split()))
# print(crt(m, a))