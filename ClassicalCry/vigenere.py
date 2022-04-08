def encode(key, word):
    ans = []
    null = ""
    ch = ord('a')
    cnt = 0
    len_max = 0
    for j in range(len(key)):
        if key[j].isalpha():
            len_max = j+1
        else:
            break
    for i in range(len(word)):
        if word[i].isalpha():
            ans.append(chr((ord(word[i])+ord(key[cnt]) - 2*ch) % 26 + ch))
            cnt += 1
            if cnt == len_max:
                cnt = 0
    return null.join(ans)


def decode(key, word):
    ans = []
    null = ""
    ch = ord('a')
    len_max = len(key)
    cnt = 0
    len_max = 0
    for j in range(len(key)):
        if key[j].isalpha():
            len_max = j+1
        else:
            break
    for i in range(len(word)):
        if word[i].isalpha():
            ans.append(chr((ord(word[i]) - ord(key[cnt])) % 26 + ch))
            cnt += 1
            if cnt == len_max:
                cnt = 0
    return null.join(ans)


if __name__ == '__main__':
    k = input()
    string = input()
    mode = int(input())

    if mode == 1:
        result = encode(k, string)
    else:
        result = decode(k, string)
    print(result)
