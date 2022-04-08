from Exp1.extEuclid import *


def encode(k, b, line):
    if euclid(k, 26) != 1:
        return "invalid key"
    ans = []
    null = ""
    for i in range(len(line)):
        if line[i].islower():
            tmp = ord(line[i]) - ord('a')
            ans.append(chr((tmp * k + b) % 26 + ord('a')))
    return null.join(ans)


def decode(k, b, line):
    if euclid(k, 26) != 1:
        return "invalid key"
    ans = []
    null = ""
    for i in range(len(line)):
        if line[i].islower():
            tmp = ord(line[i]) - ord('a')
            ans.append(chr((inv(k, 26) * (tmp - b)) % 26 + ord('a')))
    return null.join(ans)


if __name__ == '__main__':
    key_k, key_b = map(int, input().split())
    string = input()
    mode = int(input())

    if mode == 1:
        result = encode(key_k, key_b, string)
    else:
        result = decode(key_k, key_b, string)

    print(result)
