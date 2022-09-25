[toc]

# Report

## 一、思路

1. 定义了一个结构体num，储存了表示一个数的具体信息。
2. 对输入的字符串进行处理，用结构体num对数字进行表示。
3. 对num结构的数据进行高精度乘法操作，并将结果整合为可供输出的字符串。
4. 在过程中，对异常输入进行捕获，并输出提示。



## 二、Highlight

1. **功能强大**而代码**精简**，总计**100余行**
2. 良好的代码风格**&**方法分割，**高内聚低耦合**
3. 支持**任意位数**的乘法
4. 支持**科学计数法**计算
5. 支持**多种计算组合**，详见*第四部分效果展示*



<div STYLE="page-break-after: always;"></div>

## 三、代码

### 1. 总览

由一个`struct`，两个方法`mul()`和`formal()`以及`main()`构成。

![image-20220925144429826](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925144429826.png)

### 2. 结构体`num`

```c++
struct num
{
    int sign = 1; // 符号位 1 / -1
    string value; // e之前 除去小数点的数字
    long long point; // 小数点位置
    double e; // 指数部分
};
```

### 3. 字符串预处理`num formal(string);`

```c++
num formal(string ss)
{
    num result;
    int idx = ss.find("e");
    if (idx == string::npos)
    {
        result.e = 0;
        idx = ss.length();
    }
    else
    {
        result.e = stold(ss.substr(idx+1));
    }

    string s = ss.substr(0,idx);
    if (s.substr(0,1) == "-")
    {
        result.sign = -1;
        s = s.substr(1);
    }
    else
    {
        result.sign = 1;
    }

    int idx2 = s.find(".");
    if (idx2 == string::npos)
    {
        result.point = 0;
        result.value = s;
    }
    else
    {
        result.point = s.length() - 1 - idx2;
        result.value = s.erase(idx2, 1);
    }
    
    return result;
}
```

### 4.高精度乘法`string mul(num str1, num str2)`

```c++
string mul(num str1, num str2)
{
    int len1 = str1.value.size();
    int len2 = str2.value.size();
    int len3 = len1 + len2;
    long long p = str1.point + str2.point;
    int n1[len1] = {};
    int n2[len2] = {};
    int n3[len3] = {};
    string result = "";

    int sign = str1.sign * str2.sign;
    if (sign == -1)
    {
        result += "-";
    }

    for (int i = 0; i < len1; i++)
    {
        n1[i] = stoi(str1.value.substr(len1 - 1 - i, 1));
    }
    for (int i = 0; i < len2; i++)
    {
        n2[i] = stoi(str2.value.substr(len2 - 1 - i, 1));
    }

    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            n3[len3 - 1 - i - j] += n1[i] * n2[j];
            n3[len3 - 2 - i - j] += n3[len3 - 1 - i - j] / 10;
            n3[len3 - 1 - i - j] %= 10;
        }
    }

    // 整合成用于输出的字符串
    int cnt = 0;
    for (; cnt < len3 - p - 1; cnt++)
    {
        if (n3[cnt] != 0)
            break;
    }

    for (; cnt < len3; cnt++)
    {
        if (p != 0 && cnt == len3 - p)
            result += ".";
        result += to_string(n3[cnt]);
    }

    if (str1.e + str2.e != 0)
    {
        result += "e";
        result += to_string(str1.e + str2.e);
    }

    return result;
}
```

### 5. `main()`

```c++
int main(int argc, char *argv[])
{
    try
    {
        num num1 = formal(argv[1]);
        num num2 = formal(argv[2]);

        string result = mul(num1, num2);
        printf("%s * %s = %s", argv[1], argv[2], result.c_str());
    }
    catch(const std::exception& e)
    {
        printf("The input cannot be interpret as numbers!");
    }
   return 0;
}
```

<div STYLE="page-break-after: always;"></div>

 ## 四、效果展示

1. 基础乘法

   ![image-20220925152016512](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925152016512.png)

2. 小数乘法

   ![image-20220925152150684](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925152150684.png)

3. 高精度小数

   ![image-20220925153306912](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925153306912.png)

4. 小数与科学计数法

   ![image-20220925152244081](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925152244081.png)

5. 大整数相乘

   ![image-20220925153436371](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925153436371.png)

6. 科学计数法相乘

   ![image-20220925153544257](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925153544257.png)

7. 非法输入提示

   ![image-20220925153911610](C:\Users\86158\AppData\Roaming\Typora\typora-user-images\image-20220925153911610.png)