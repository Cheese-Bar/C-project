#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

enum OP
{
    RIGHT = -2,
    NONE = 0,
    ADD = 1,
    MUL = 2,
    LEFT = -1
};

struct num
{
    int sign = 1;        // 符号位 1 / -1
    string value = "";   // e之前 除去小数点的数字
    long long point = 0; // 小数点位置
    double e = 0.0;      // 指数部分
    OP op = NONE;
};

bool isOp(string s)
{
    if (s.compare("+") == 0 || s.compare("*") == 0 || s.compare("(") == 0 || s.compare(")") == 0)
    {
        return true;
    }
    return false;
}

string output(num n)
{
    string result = "";
    int cnt = 0;

    while (n.value.substr(cnt, 1).compare("0") == 0)
    {
        if (cnt != n.value.length() - 1)
        {
            cnt++;
        }
    }

    for (; cnt < n.value.size(); cnt++)
    {
        if (n.point != 0 && cnt == n.value.size() - n.point)
            result += ".";
        result += n.value.substr(cnt, 1);
    }

    if (n.e != 0)
    {
        result += "e";
        result += to_string(n.e);
    }

    return result;
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

vector<num> formalAll(string s)
{
    vector<num> result;
    size_t i = 0;
    size_t j = 0;
    for (; i < s.length();)
    {
        num next_num;

        if (!isOp(s.substr(i, 1)) && ('0'>s.at(i) || '9'< s.at(i)))
        {
            throw exception();
        }

        if (isOp(s.substr(i, 1)))
        {
            if (s.substr(i, 1).compare("+") == 0)
            {
                next_num.op = ADD;
            }
            else if (s.substr(i, 1).compare("*") == 0)
            {
                next_num.op = MUL;
            }
            else if (s.substr(i, 1).compare("(") == 0)
            {
                next_num.op = LEFT;
            }
            else if (s.substr(i, 1).compare(")") == 0)
            {
                next_num.op = RIGHT;
            }

            result.push_back(next_num);
            i++;
            continue;
        }

        for (j = i + 1; j < s.length() + 1; j++)
        {
            if (j == s.length() || isOp(s.substr(j, 1)))
            {
                result.push_back(formal(s.substr(i, j - i)));
                i = j;
                break;
            }
        }
    }
    // cout << result.size() << endl;
    return result;
}

stack<num> getPostfix(vector<num> &v)
{
    stack<num> nums;
    stack<num> ops;
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i].op == NONE)
        {
            nums.push(v[i]);
        }
        else
        {
            if (ops.empty())
            {
                ops.push(v[i]);
            }
            else
            {
                if (v[i].op > 0)
                {
                    while (!ops.empty() && (v[i].op <= ops.top().op))
                    {
                        nums.push(ops.top());
                        ops.pop();
                    }
                }
                ops.push(v[i]);
            }

            if (ops.top().op == RIGHT)
            {
                ops.pop();
                while (ops.top().op != LEFT)
                {
                    nums.push(ops.top());
                    ops.pop();
                }
                ops.pop();
            }
        }
    }

    while (!ops.empty())
    {
        nums.push(ops.top());
        ops.pop();
    }

    return nums;
}

string addHelp(string a, string b)
{
    int diff = a.length() - b.length();
    if (diff > 0)
    {
        for (size_t i = 0; i < diff; i++)
        {
            b.insert(0, "0");
        }
    }
    else
    {
        for (size_t i = 0; i < -diff; i++)
        {
            a.insert(0, "0");
        }
    }

    int up = 0;
    string result = "";
    for (size_t i = 0; i < a.length(); i++)
    {
        int sum = up + stoi(a.substr(a.length() - 1 - i, 1)) + stoi(b.substr(b.length() - 1 - i, 1));
        up = sum / 10;
        result.insert(0, to_string(sum % 10));
    }
    result.insert(0, to_string(up));
    return result;
}

num add(num a, num b)
{
    num result;
    string aint = a.value.substr(0, a.value.length() - a.point);
    string apoint = a.value.substr(a.value.length() - a.point);
    string bint = b.value.substr(0, b.value.length() - b.point);
    string bpoint = b.value.substr(b.value.length() - b.point);

    int diff = apoint.length() - bpoint.length();
    if (diff > 0)
    {
        for (size_t i = 0; i < diff; i++)
        {
            bpoint = bpoint + "0";
        }
    }
    else
    {
        for (size_t i = 0; i < -diff; i++)
        {
            apoint = apoint + "0";
        }
    }

    string sumPoint = addHelp(apoint, bpoint);
    string sumInt = addHelp(aint, bint);
    sumInt = addHelp(sumInt, sumPoint.substr(0, 1));
    result.value = sumInt + sumPoint.substr(1);
    result.point = max(a.point, b.point);

    return result;
}

num caculate(stack<num> &s)
{
    stack<num> cac;
    num result;
    while (!s.empty() || cac.size() != 1)
    {
        int cnt = 0;
        if (!s.empty())
        {
            OP ttttt = s.top().op;
            // cout << output(s.top()) << endl;
            cac.push(s.top());
            s.pop();
        }

        if (cac.top().op == NONE)
        {
            num tempNum = cac.top();
            cac.pop();
            if (!cac.empty() && cac.top().op == NONE)
            {
                cnt = 2;
            }
            cac.push(tempNum);
        }

        while (cnt == 2)
        {
            cnt = 0;
            num num1 = cac.top();
            cac.pop();
            num num2 = cac.top();
            cac.pop();
            num op0 = cac.top();
            cac.pop();
            if (op0.op == MUL)
            {
                string temp = mul(num1, num2);
                num temp1 = formal(temp);
                cac.push(temp1);
            }
            else if (op0.op == ADD)
            {
                cac.push(add(num1, num2));
            }

            if (cac.top().op == NONE)
            {
                num tempNum = cac.top();
                cac.pop();
                if (!cac.empty() && cac.top().op == NONE)
                {
                    cnt = 2;
                }
                cac.push(tempNum);
            }
        }
    }
    result = cac.top();
    return result;
}

void trim(string &s)
{
    int index = 0;
    if (!s.empty())
    {
        while ((index = s.find(' ', index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

int main(int argc, char *argv[])
{
    while (true)
    {
        try
        {
            string s ="";
            cout << "Please enter what you want to calculate; type EXIT to exit." << endl;
            getline(cin, s);
            trim(s);
            if (s.compare("EXIT") == 0)
            {
                cout << "Bye~" << endl;
                break;
            }
            vector<num> temp = formalAll(s);
            stack<num> temp2 = getPostfix(temp);
            num result = caculate(temp2);
            string re = output(result);
            cout << re << endl;
        }
        catch (const std::exception &e)
        {
            printf("The input is illegal, please check!\n");
        }
    }

    return 0;
}
