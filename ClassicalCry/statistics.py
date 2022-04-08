# if __name__ == '__main__':
#     buf = input()
#     sta = [0] * 26
#     ch = ord('a')
#     for i in range(len(buf)):
#         sta[ord(buf[i]) - ch] += 1
#     maxl = 0
#     maxi = 0
#     for i in range(26):
#         if sta[i] > maxl:
#             maxl = sta[i]
#             maxi = i
#
#     print((maxi - 4) % 26)


if __name__ == '__main__':
    string = input().strip().replace('\n', '').replace('\r', '')
    sta = [0] * 26
    for c in string:
        sta[ord(c) - ord("a")] += 1
    maxl = 0
    ch = "a"
    for i in range(26):
        if sta[i] > maxl:
            maxl = sta[i]
            ch = chr(i + ord("a"))
    print((ord(ch) - ord("a")) - (ord("e") - ord("a")) % 26)
