[toc]

# Report for C project 3

## 一、思路

设计一个基于C语言的对用户友好的矩阵库

设计了一个MATRIX的结构体，用于存储矩阵的长度、高度以及数据

使用C的指针操作，为每个矩阵分配适当大小的空间，合理化利用空间

## 二、Highlight

1. 代码结构清晰，功能强大，总代码量200余行
2. 人性化的参数接口设置
3. 良好的代码风格&代码分割
4. 支持多种矩阵与矩阵的操作/矩阵与标量的计算
5. 对用户可能出现的异常行为进行捕获并做出提示

## 三、代码结构

1. 为矩阵设计了一个struct，用于记录矩阵的长、宽以及数据存放的位置
2. 为每个常用的矩阵计算设计了相应的方法，如创建矩阵，删除矩阵，矩阵复制，矩阵相加，矩阵相减，矩阵相乘；矩阵与标量的计算（相加，相减，相乘）；矩阵寻值（最大值，最小值）；打印矩阵等。

![image-20221030190049228](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030190049228.png)

## 四、效果展示

​	使用：`gcc -o test.exe  matrix.c test.c; ./test.exe`

- 创建矩阵
  ![image-20221030191953404](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030191953404.png)

- 删除矩阵
  ![image-20221030193112090](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030193112090.png)

- 矩阵复制
  ![image-20221030192907194](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192907194.png)

- 矩阵相加
  ![image-20221030192055492](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192055492.png)

- 矩阵相减
  ![image-20221030192146218](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192146218.png)
- 矩阵乘法
  ![image-20221030192019245](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192019245.png)

- 矩阵与标量的计算

  - 加法
    ![image-20221030192235594](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192235594.png)
  - 减法
    ![image-20221030192404487](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192404487.png)
  - 乘法
    ![image-20221030192441905](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192441905.png)

- 矩阵寻值

  - 最大值 & 最小值
    ![image-20221030192032548](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030192032548.png)

- 异常处理

  - 维度不一致
    ![image-20221030193720519](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030193720519.png)

  - 空指针处理
    ![image-20221030193927122](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030193927122.png)
  - 创建非法矩阵
    ![image-20221030194119115](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030194119115.png)![image-20221030194103037](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20221030194103037.png)



