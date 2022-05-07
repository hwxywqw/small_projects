def generateBBS(length, p, q, s):
    ans = 0
    n = p * q
    x = (s ** 2) % n
    for i in range(length):
        tmp = (x ** 2) % n
        ans |= (tmp % 2) << i
        x = tmp
    return ans


if __name__ == '__main__':
    length = int(input())
    p = int(input())
    q = int(input())
    s = int(input())
    result = generateBBS(length, p, q, s)
    print(result)

