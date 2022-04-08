def encode(key, word):
    ans = []
    null = ""
    cnt = 0
    len_max = 0
    for j in range(len(key)):
        if key[j] != '\n' and key[j] != '\r':
            len_max = j+1
        else:
            break
    for i in range(len(word)):
        if 126 >= ord(word[i]) >= 33:
            ans.append(chr(ord(word[i]) ^ ord(key[cnt])))
            cnt += 1
            if cnt == len_max:
                cnt = 0
    return null.join(ans)


if __name__ == '__main__':
    k = input()
    string = input()
    mode = int(input())

    result = encode(k, string)
    print(result)
