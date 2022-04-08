import math
import sys
import time


def eratosthenes(n):
    num = [True] * (n + 1)  # False 代表素数，默认所有数都是素数
    prime = []  # 存储素数的空列表
    for i in range(2, int(math.sqrt(n))+1):
        if num[i]:
            for j in range(2*i, n+1, i):
                # if (j//i) % i == 0: break
                num[j] = False
    for i in range(2, len(num)):
        if num[i]:
            prime.append(i)
    return prime


def eratosthenes2(n):
    num = [True] * (n + 1)  # False 代表素数，默认所有数都是素数
    prime = []  # 存储素数的空列表
    for i in range(2, n + 1):   # i代表当前的数
        if num[i]:  # 选出余下的第一个素数
            prime.append(i)

        for j in range(len(prime)):  # 遍历2-n，筛去所有素数的i倍
            if prime[j] * i > n: break
            num[prime[j] * i] = False
            if i % prime[j] == 0: break  # 线性筛法优化，将i看作最大因子
    return prime


# list_p = eratosthenes2(int(input()))
# for i in range(len(list_p)):
#     print(str(list_p[i])+" ", end="")

if __name__ == '__main__':
    # start = time.time()
    print(eratosthenes(103))
    # end = time.time()
    # print(end-start)