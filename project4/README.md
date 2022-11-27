# Report for Project 4

### 运行

```shell
gcc .\test.c .\matrix.c -mfma -static -I ./OpenBLAS/include/ -L ./OpenBLAS/lib -lopenblas -lpthread -lgfortran; .\a.exe
```



## 一、思路

在project3的基础上，对比不同的矩阵乘法实现的计算速度

利用SIMD等方法对矩阵乘法进行加速

## 二、Highlight

1. 良好的代码风格
2. 加速效果对比

## 三、代码结构

![image-20221127215008175](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221127215008175.png)

## 四、实验对比（单位：微秒）

|  N   | matmul_plain | matmul_improved | matmul_openblas |
| :--: | :----------: | :-------------: | :-------------: |
|  16  |      0       |        0        |        0        |
| 128  |     9973     |      1031       |        0        |
| 256  |    94775     |      8004       |      1961       |
| 512  |   1094105    |      65371      |      4955       |
| 1024 |   12543672   |     521605      |      30409      |
| 2048 |  261143387   |     5549194     |     107677      |
| 4096 |      ——      |    49706198     |     721038      |
| 8192 |      ——      |       ——        |     6259263     |

实验总结：

- 使用SIMD可以起到非常显著的加速效果
- 实验中openMP并没有显著提升，且有时反而会减缓计算速度
- openblas提速效果非常明显，使用了多线程

## 五、实验结果截图

- 基础矩阵乘法

![image-20221127215912197](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221127215912197.png)

- 使用SIMD进行加速

![image-20221127214731710](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221127214731710.png)

- 使用openblas加速

![image-20221127223819155](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221127223819155.png)

