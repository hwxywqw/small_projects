class MersenneTwister:
    n = 624
    m = 397
    a = 0x9908b0df
    b = 0x9d2c5680
    c = 0xefc60000
    f = 0x6c078965
    UpperMask = 0x80000000
    LowerMask = 0x7fffffff
    MaxMask = 0xffffffff

    def __init__(self, seed):
        self.MT = [0] * self.n
        self.index = 0

        self.MT[0] = seed
        for i in range(1, self.n):
            temp = self.MT[i - 1]
            self.MT[i] = (self.f * (temp ^ (temp >> 30)) + i) & self.MaxMask

    def extract_number(self):
        if self.index == 0:
            self.twist()

        y = self.MT[self.index]
        y = y ^ (y >> 11)
        y = y ^ (y << 7) & self.b
        y = y ^ (y << 15) & self.c
        y = y ^ (y >> 18)

        self.index = (self.index + 1) % self.n
        return y

    def twist(self):
        for i in range(self.n):
            y = (self.MT[i] & self.UpperMask) + (self.MT[(i + 1) % self.n] & self.LowerMask)
            self.MT[i] = self.MT[(i + self.m) % self.n] ^ (y >> 1)
            if y % 2:
                self.MT[i] ^= self.a


if __name__ == "__main__":
    mt = MersenneTwister(int(input()))
    length = 20
    for i in range(length):
        print(mt.extract_number())
