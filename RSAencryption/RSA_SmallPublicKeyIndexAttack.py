from Exp1.CNReminder import *
import gmpy2


def RSA_SPKA(e, c, N):
    return gmpy2.iroot(crt(N, c), e)


# def RSA_SPKA(e, item):
#     cyph = CRT(item)
#     return gmpy2.iroot(cyph, e)


if __name__ == '__main__':
    n = int(input())
    e = int(input())
    # item = []
    # for i in range(n):
    #     a = int(input())
    #     b = int(input())
    #     item.append([a, b])
    #
    # m = RSA_SPKA(e, item)
    c = N = [0] * n
    for i in range(n):
        c[i] = int(input())
        N[i] = int(input())
    m = RSA_SPKA(e, c, N)
    print(m)