import copy
import Exp1.extEuclid

"""
这一部分是矩阵运算的函数整理
 - determinant: 求行列式，输入n*n方阵
 - adjudate: 求伴随矩阵，输入n*n方阵
"""


def det(m):
    result = 0
    length = len(m)
    if length == 1:
        result = m[0][0]
    else:
        for i in range(length):
            x = m[0][i]
            tmp = copy.deepcopy(m)
            del tmp[0]
            sub = []
            for j in range(1, length):
                del tmp[j - 1][i]
                sub.append(tmp[j - 1])
            result += pow(-1, i + 2) * x * det(sub)
    return result


def adjudate(m):
    d = len(m)
    inv = copy.deepcopy(m)
    for i in range(d):
        for j in range(d):  # 对逆矩阵中的某一个元素而言
            # 先求他的代数余子式（必定是一个整数）
            m_cof = copy.deepcopy(m)
            del (m_cof[i])
            for k in range(d - 1):
                del (m_cof[k][j])
            det_cof = det(m_cof)
            inv[j][i] = ((1 if (i + j) % 2 == 0 else -1) * det_cof)
    return inv


def multiply(m1, m2):
    d = len(m1)
    ans = [[0 for i in range(d)] for j in range(d)]
    for i in range(d):
        for j in range(d):
            tmp = 0
            for cnt in range(d):
                tmp += m1[i][cnt] * m2[cnt][j]
            ans[i][j] = tmp
    return ans


def multiply_mod26(m1, m2):
    d = len(m1)
    ans = [[0 for i in range(d)] for j in range(d)]
    for i in range(d):
        for j in range(d):
            tmp = 0
            for cnt in range(d):
                tmp += m1[i][cnt] * m2[cnt][j]
            ans[i][j] = tmp % 26
    return ans


"注意，矩阵可能在模26的条件下是不可逆的"


def inv_mod26(m):
    d = len(m)
    det_ = det(m)
    det_inv = Exp1.extEuclid.inv(det_, 26)
    m_inv = adjudate(m)

    for i in range(d):
        for j in range(d):
            m_inv[i][j] = (det_inv * m_inv[i][j]) % 26

    return m_inv


if __name__ == '__main__':
    test = [[19, 7, 8], [18, 8, 18], [19, 4, 18]]
    d = det(test)
    print(d, d % 26)

    testinv = inv_mod26(test)
    result = multiply_mod26(test, testinv)
    for i in range(3):
        for j in range(3):
            print(str(result[i][j]), end=" ")
        print("")
