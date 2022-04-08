irrP = 0x11b


def add(x, y):
    return x ^ y


def multiply(a, b):
    result = 0
    while b > 0:
        if b & 1 == 1:
            result ^= a
        a <<= 1
        if a & 0x100 == 0x100:
            a ^= irrP
        a &= 0xff
        b >>= 1
    return result


def divide(a, b):
    if a == 0:
        return [0, 0]    # 被除数为0，特判
    if a.bit_length() < b.bit_length():
        return [0, a]
    if a.bit_length() == b.bit_length():
        return [1, a ^ b]

    result = 0
    while a.bit_length() >= b.bit_length():   # 模仿多项式的竖式除法
        rec = a.bit_length() - b.bit_length()
        a ^= (b << rec)
        result ^= (1 << rec)

    reminder = a
    return [result, reminder]


def printHex(arr):
    for num in arr:
        print("%02x " % num, end="")


if __name__ == '__main__':
    # a, op, b = input().split()
    # a = int(a, 16)
    # b = int(b, 16)
    # ans = add(a, b) if (op == '+' or op == '-') else (multiply(a, b) if (op == '*') else divide(a, b))
    ans = multiply(0x0e, 0x74)
    print(hex(ans))

    ans = divide(0xae, 0x0e)
    print(printHex(ans))
