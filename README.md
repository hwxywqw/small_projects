```c
D:.
│  README.md
│  
├─AESencryption -> AES加密标准
│      AES_256.c -> AES加密，支持 128/192/256 bits
│      AES_DiffAttack.c -> AES差分攻击
│      in.txt -> AES差分攻击的一组输入
│      Sbox_generate.py ->逆S盒生成
│      testdata.txt -> 差分攻击的debug测试数据
│      
├─BasicOperation -> 实数域及有限域运算
│  ├─FiniteField -> 有限域
│  │      GF4opreations.py -> 四则运算
│  │      GFextEuclid.py -> 拓展欧几里得
│  │      GFfastPower.py -> 快速幂
│  │      GFinverse.py -> 求逆
│  │      GFpolynomial.py -> 不可约多项式
│  │      
│  ├─Matrix -> 矩阵运算
│  │      matrix.py
│  │      
│  └─RealNField
│          CNReminder.py -> 中国剩余
│          Eratosthenes.py -> 厄拉多塞
│          extEuclid.py -> 拓展欧几里得
│          fastPower.py -> 快速幂
│          MRtest.py -> MR素数检测
│          
├─ClassicalCry -> 古典密码
│  │  affine.py -> 仿射密码
│  │  hill.py -> 希尔密码
│  │  hill_crack.py -> 希尔密码的明文攻击
│  │  matrixCipher.py ->矩阵密码
│  │  monosubstitu.py -> 单表代替密码
│  │  railfence.py -> 栅栏密码
│  │  statistics.py -> 一阶统计攻击
│  │  vernam.py -> 弗纳姆密码
│  │  vigenere.py -> 维吉尼亚密码
│  │  
│  └─StatisticsAttack
│          articleall.txt -> 测试输入
│          statistics.c -> 一阶统计攻击(完全版)
│          translateall.txt -> 测试输出
│          
├─DESencryption
│      advanced.c -> 优化版DES
│      des.c -> 未优化版
│      DES_Tables.txt -> 盒
│      SPgenerate.c -> SP盒生成
│      weakkeygenerate.c -> 弱密钥生成
│      
├─PesudoRandomNumGen -> 伪随机数生成器
│      BBS_generate.py -> BBS生成器
│      MersenneTwister.py -> 梅森旋转
│      
├─RegionCoding -> 区间编码
│  │  coding.c -> 函数
│  │  decode.c -> 解码
│  │  encode.c -> 编码
│  │  filedecode.txt -> 一些测试文件
│  │  filein.txt
│  │  fileout.txt
│  │  filetmp.txt
│  │  r.txt
│  │  
│  └─backups
│          coding.c
│          decode.c
│          encode.c
│          
├─RSAencryption -> RSA加密算法
│      RSA.py -> 标准RSA
│      RSA_CommonModulusAttack.py -> RSA共模攻击
│      RSA_KeyToPQ.py -> 已知密钥对, 分解大合数n
│      RSA_SmallPublicKeyIndexAttack.py -> RSA小指数广播攻击
│      
├─SM4encryption -> SM4及工作模式
│      CBC.c
│      CTR.c
│      ECB.c
│      SM4.c
│      SM4_main.c
│      SM4参数.txt
│      
└─StreamCipher -> 流密码
    │  RC4.py -> RC4标准流密码
    │  ZUC.py -> 祖冲之序列密码
    │  
    └─RC4_test -> RC4的一个测试文件
            test.in.txt
            test.out.txt
```

