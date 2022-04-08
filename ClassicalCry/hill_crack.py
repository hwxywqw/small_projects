import matrix


def crack(n, plain, cipher):
    matrix_p = [[0 for i in range(n)] for j in range(n)]
    matrix_c = [[0 for i in range(n)] for j in range(n)]
    cnt = 0
    for i in range(n):
        for j in range(n):
            matrix_p[i][j] = ord(plain[cnt]) - ord('a')
            matrix_c[i][j] = ord(cipher[cnt]) - ord('a')
            cnt += 1

    t1 = matrix.det(matrix_p)
    t2 = matrix.det(matrix_c)
    while t1 % 2 == 0 or t1 % 2 == 0 or t2 % 13 == 0 or t2 % 13 == 0:
        for i in range(n - 2):
            matrix_p[i], matrix_p[i + 1] = matrix_p[i + 1], matrix_p[i + 2]
            matrix_c[i], matrix_c[i + 1] = matrix_c[i + 1], matrix_c[i + 2]
        matrix_p[n - 1] = [0] * n
        matrix_c[n - 1] = [0] * n
        for i in range(n):
            matrix_p[n - 1][i] = ord(plain[cnt]) - ord('a')
            matrix_c[n - 1][i] = ord(cipher[cnt]) - ord('a')
            cnt += 1
        t1 = matrix.det(matrix_p) % 26
        t2 = matrix.det(matrix_c) % 26

    matrix_pinv = matrix.inv_mod26(matrix_p)
    ans = matrix.multiply_mod26(matrix_pinv, matrix_c)
    return ans


if __name__ == '__main__':
    dim = int(input())
    plaintext = input().strip().replace('\n', '').replace('\r', '')
    ciphertext = input().strip().replace('\n', '').replace('\r', '')

    result = crack(dim, plaintext, ciphertext)
    for i in range(dim):
        for j in range(dim):
            print(str(result[i][j]), end=" ")
        print("")
