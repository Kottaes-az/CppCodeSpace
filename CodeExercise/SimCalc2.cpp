#include <bits/stdc++.h>
typedef long long int algo_t;
template <class T> bool in_arr(T x, T *arr, size_t length = sizeof(*arr)) {
    for (int i = 0; i < length; i++)
        if (*(arr + i) == x) return true;
    return false;
};
int main() {
    std::string oprs[21] = {"+", "-", "*", "/", "%"};
    std::string s;
    long double o1, o2, result = 0;
    char opr = '0';
    while (getline(std::cin, s)) {
        for (size_t i = 0; i < s.size(); i++)
            if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ||
                s[i] == '%') {
                o1 = atoi((const char *)s.substr(0, i).c_str());
                o2 = atoi((const char *)s.substr(i + 1).c_str());
                opr = s[i];
                break;
            }
        switch (opr) {
            case '+': result = o1 + o2; break;
            case '-': result = o1 - o2; break;
            case '*': result = o1 * o2; break;
            case '/': result = o1 / o2; break;
            case '%': result = (algo_t)o1 % (algo_t)o2; break;
        }
        std::cout << " = " << result << std::endl;
    }
    return 0;
}