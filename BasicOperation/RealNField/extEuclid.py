import math


# 常规欧几里得算法
def euclid(a, b):
    if b == 0: return 0
    while b:
        r = a % b
        a, b = b, r
    return a


# 模m求逆元
def inv(n, m):
    return euclid_ex(n, m)[1]


# 拓展欧几里得算法
def euclid_ex(m, n):
    # 对于得到的系数进行处理，使得x为最小正整数
    def process_linear(gcd, x, y, a, b):
        a0, b0 = a // gcd, b // gcd
        if b0 > 0:
            k = math.floor(1 - x / b0)
        else:
            k = math.floor(-x / b0)
        return gcd, x + k * b0, y - k * a0

    a, b = abs(m), abs(n)
    if b == 0:
        return a, 1, 0
    else:
        gcd, x0, y0 = euclid_ex(b, a % b)
        x = y0
        if m < 0: x *= -1
        y = x0 - (a // b) * y0
        if n < 0: y *= -1
        return process_linear(gcd, x, y, m, n)      # 若不要求x最小正整数，则返回gcd,x,y



if __name__ == '__main__':
    print((-5*23)%26)
    # a, b = map(int, input().split())
    # gcd, x, y = euclid_ex(a, b)
    # print(x, y, gcd)
