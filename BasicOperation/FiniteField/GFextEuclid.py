from Exp2.GF4opreations import *
irrP = 0x11b


def euclid_ex(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, x0, y0 = euclid_ex(b, divide(a, b)[1])
        x = y0
        y = add(x0, multiply(divide(a, b)[0], y0))
        return gcd, x, y


if __name__ == '__main__':
    a, b = input().split()
    a = int(a, 16)
    b = int(b, 16)
    arr = euclid_ex(a, b)
    printHex([arr[1], arr[2], arr[0]])
