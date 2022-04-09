from Exp2.GF4opreations import *
from Exp2.GFinverse import *


if __name__ == '__main__':
    matrix_ini = [0] * 256
    matrix_per1 = [0] * 256
    matrix_per2 = [0] * 256
    matrix_inv = [0] * 256
    for i in range(16):
        for j in range(16):
            tmp = (i << 4) + j
            matrix_ini[i * 16 + j] = tmp
            b = inverse(tmp)
            matrix_per1[i * 16 + j] = b
            for k in range(8):
                tmp = ((b & (1 << k)) >> k) \
                      ^ ((b & (1 << ((k + 4) % 8))) >> ((k + 4) % 8)) \
                      ^ ((b & (1 << ((k + 5) % 8))) >> ((k + 5) % 8)) \
                      ^ ((b & (1 << ((k + 6) % 8))) >> ((k + 6) % 8)) \
                      ^ ((b & (1 << ((k + 7) % 8))) >> ((k + 7) % 8))
                matrix_per2[i * 16 + j] |= tmp << k
            matrix_per2[i * 16 + j] = add(matrix_per2[i * 16 + j], 0x63)
            matrix_inv[matrix_per2[i * 16 + j]] = i * 16 + j

# # 初始化后的S盒
#     for i in range(16):
#         for j in range(16):
#             print("0x%02x" % matrix_ini[i * 16 + j], end=" ")
#         print("")
#
# # 求逆元后的S盒
#     for i in range(16):
#         for j in range(16):
#             print("0x%02x" % matrix_per1[i * 16 + j], end=" ")
#         print("")

# 标准S盒
    for i in range(16):
        for j in range(16):
            print("0x%02x," % matrix_per2[i * 16 + j], end=" ")
        print("")

    print("")
# 逆S盒
    for i in range(16):
        for j in range(16):
            print("0x%02x," % matrix_inv[i * 16 + j], end=" ")
        print("")
