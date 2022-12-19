#include <iostream>
#include <string.h>
//字符串移位子串问题
using namespace std;
int main()
{
    int flag = 0;
    string s1, s2;
    cin >> s1 >> s2;
    for (int i = 0; s1[i]; i++) {
        s1 = s1.substr(1) + s1[0];
        //上为白科技（雾，实现字符串中第一个元素移动到最后一个元素
        for (int j = 0; j + s2.length() <= s1.length() && (!flag); j++) {
            int k = 0;
            for (; k < (int)s2.length(); k++)
                if (s1[j + k] != s2[k]) break;
            if (k == (int)s2.length()) flag = 1;
        }
    }
    printf((flag) ? "YES" : "NO");
    return 0;
}