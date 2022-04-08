def encode(n, k, word):
    null = ""
    ans = []
    seq = [i+1 for i in range(n)]
    mat = dict.fromkeys(seq, None)
    cnt = 0
    for i in range(len(word)):
        if mat[key[cnt]] is None:
            mat[key[cnt]] = []
        mat[key[cnt]].append(word[i])
        cnt += 1
        if cnt == len(key):
            cnt = 0

    for i in range(len(key)):
        ans.append(null.join(mat[i+1]))

    return null.join(ans)


def decode(n, k, word):
    null = ""
    ans = []
    seq = [i + 1 for i in range(n)]
    mat = dict.fromkeys(seq, None)
    cnt = 0     # 对word的字母计数
    for i in range(len(key)):   # 对dict的键计数
        for j in range(len(word)//len(key)):
            if mat[i+1] is None:
                mat[i + 1] = []
            mat[i + 1].append(word[cnt])
            cnt += 1

    for i in range(len(word)//len(key)):
        for j in range(len(key)):
            ans.append(mat[key[j]][i])

    return null.join(ans)


if __name__ == '__main__':
    length = int(input())
    key_str = input().strip().replace('\n', '').replace('\r', '')
    string = input().strip().replace('\n', '').replace('\r', '')
    key = []
    for i in range(len(key_str)):
        key.append(int(key_str[i]))
    mode = int(input())

    if mode == 1:
        result = encode(length, key, string)
    else:
        result = decode(length, key, string)

    print(result)
