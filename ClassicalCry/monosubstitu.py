def encode(str1, str2, word):
    ans = []
    null = ""
    for i in range(len(word)):
        for j in range(len(str1)):
            if str1[j] == word[i]:
                ans.append(str2[j])
    return null.join(ans)


def decode(str1, str2, word):
    ans = []
    null = ""
    for i in range(len(word)):
        for j in range(len(str2)):
            if str2[j] == word[i]:
                ans.append(str1[j])
    return null.join(ans)


if __name__ == '__main__':
    key1 = input()
    key2 = input()
    string = input()
    mode = int(input())

    if mode == 1:
        result = encode(key1, key2, string)
    else:
        result = decode(key1, key2, string)

    print(result)