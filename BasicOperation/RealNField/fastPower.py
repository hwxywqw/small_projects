def fastPower(a, b, c):
    a = a % c       # if a>c, the (a-c) part makes no effort
    result = 1
    while b != 0:
        if b % 2 == 1:  # if the last number of b(binary)==1
            result = (result * a) % c   # result *= a, because (a^b) mod c = (a mod c)^b mod c
        b >>= 1
        a = (a * a) % c
    return result


# a, b, c = map(int, input().split())
# print(fastPower(a, b, c))
