def encode(key, word):
    ans = []
    null = ""
    for i in range(key):
        for j in range(i, len(word), key):
            ans.append(word[j])
    return null.join(ans)


def decode(key, word):
    ans = []
    null = ""
    cnt = [len(word)//key] * key
    for i in range(len(word) % key):
        cnt[i] += 1

    for i in range(cnt[0]):         # 第 i 个
        for j in range(len(cnt)):   # 第 j 组
            tmp = (0 if j == 0 else sum(cnt[:j])) + i
            if tmp < len(word) and i < cnt[j]:
                ans.append(word[tmp])
    return null.join(ans)


if __name__ == '__main__':
    k = int(input())
    string = input().strip().replace('\n','').replace('\r','')
    mode = int(input())

    if mode == 1:
        result = encode(k, string)
    else:
        result = decode(k, string)

    print(result)