import sys

if __name__ == '__main__':
    k = input().replace('0x', '').replace('\n', '').replace('\r', '')
    length = (len(k) + (len(k) % 2)) // 2
    list_k = [0] * length
    list_t = [0] * 256
    list_s = [0] * 256
    for i in range(length):
        list_k[i] = int(k[i * 2]+k[i * 2 + 1], 16)
    for i in range(256):
        list_s[i] = i
        list_t[i] = list_k[i % length]

    j = 0
    for i in range(256):
        j = (j + list_s[i] + list_t[i]) % 256
        tmp = list_s[i]
        list_s[i] = list_s[j]
        list_s[j] = tmp

    ch = sys.stdin.read(2)
    if ch == "0x":
        ch = sys.stdin.read(2)
        print("0x", end="")
    i = j = 0
    while ch:
        i = (i + 1) % 256
        j = (j + list_s[i]) % 256
        tmp = list_s[i]
        list_s[i] = list_s[j]
        list_s[j] = tmp
        t = (list_s[i] + list_s[j]) % 256
        k = list_s[t]

        num = int(ch, 16)
        print("%02x" % (num ^ k), end="")
        ch = sys.stdin.read(2)



