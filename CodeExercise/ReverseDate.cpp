#include <iostream>
using namespace std;
int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool reverse(long a)
{
    string b = to_string(a);
    for (int i = 0; i < 8; i++)
        if (b[i] != b[7 - i]) return false;
    return true;
}
int main()
{
    long date1, date2, cnt = 0, flag = 0;
    cin >> date1 >> date2;
    while (date1 <= date2) {
        if (reverse(date1)) cnt++;
        date1++;
        long y = date1 / 10000, m = date1 / 100 % 100, d = date1 % 100;
        if (m == 2 && ((y % 4 == 0 && y % 100) || (y % 400 == 0)))
            flag = 1;
        else
            flag = 0;
        if (d + flag > mon[m]) {
            d = 1; //日归一
            m++;

        } //对溢出日进行进位
        if (m > 12) {
            m = 1; //月归一
            y++;
        } //对溢出月份进行进位
        date1 = y * 10000 + m * 100 + d;
    }
    cout << cnt;
    return 0;
}