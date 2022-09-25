#include <iostream>
#include <string>
using namespace std;

struct num
{
    int sign = 1;    // 符号位 1 / -1
    string value;    // e之前 除去小数点的数字
    long long point; // 小数点位置
    double e;        // 指数部分
};

string mul(num str1, num str2);

num formal(string);

int main(int argc, char *argv[])
{
    try
    {
        num num1 = formal(argv[1]);
        num num2 = formal(argv[2]);

        string result = mul(num1, num2);
        printf("%s * %s = %s", argv[1], argv[2], result.c_str());
    }
    catch (const std::exception &e)
    {
        printf("The input cannot be interpret as numbers!");
    }
    return 0;
}

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
        result.e = stold(ss.substr(idx + 1));
    }

    string s = ss.substr(0, idx);
    if (s.substr(0, 1) == "-")
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
