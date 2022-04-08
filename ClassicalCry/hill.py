from matrix import *


def encode(d, m, word):
    ans = []
    null = ""
    for p in range(len(word) // d):  # 分组，一组dim个
        for i in range(d):  # 对固定的某一组而言
            tmp = 0
            for j in range(d):
                tmp += m[j][i] * (ord(word[p * d + j]) - ord('a'))
            tmp %= 26
            ans.append(chr(tmp + ord('a')))
    return null.join(ans)


def decode(d, m, word):
    m_inv = inv_mod26(m)
    ans = []
    null = ""
    for p in range(len(word) // d):  # 分组，一组dim个
        for i in range(d):  # 对固定的某一组而言
            tmp = 0
            for j in range(d):
                tmp += m_inv[j][i] * (ord(word[p * d + j]) - ord('a'))
            tmp %= 26
            ans.append(chr(tmp + ord('a')))
    return null.join(ans)


if __name__ == '__main__':
    dim = int(input())
    matrix = [[0 for i in range(dim)] for j in range(dim)]
    for i in range(dim):
        matrix[i] = [int(j) for j in input().split()]
    string = input().strip().replace('\n', '').replace('\r', '')
    mode = int(input())

    if mode == 1:
        result = encode(dim, matrix, string)
    else:
        result = decode(dim, matrix, string)

    print(result)
