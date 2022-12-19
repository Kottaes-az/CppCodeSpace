#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
int n_base2deci(int a, int n)
{
    int ret = 0, len = to_string(a).size();
    for (int i = 0; i < len; i++) {
        ret += a % 10 * pow(n, i);
        a /= 10;
    }
    return ret;
}
int main()
{
    int p, q, r, flag = 0;
    cin >> p >> q >> r;
    /*查找三个数里的最大数，进制数i一定大于此数*/
    string coll = to_string(p) + to_string(q) + to_string(r);
    sort(coll.begin(), coll.end(), less<char>());
    int i = coll[(int)coll.length() - 1] - '0';
    /*寻找最小的符合要求的进制i*/
    while (i <= 40 && (!flag))
        if (n_base2deci(p, i++) * n_base2deci(q, i) == n_base2deci(r, i))
            flag = 1;
    printf("%d", flag ? i : 0);
    return 0;
}