#include <bits/stdc++.h>
using namespace std;
const int LIM = 5e5 + 10;
int n, m, p, x, nums[LIM], bucket[LIM], pwr[LIM], cnt[4];
multiset<int> arr;
void checkUp() {
    if (cnt[3] || bucket[*arr.begin()] > 1)
        puts("0");
    else
        printf("%d\n", pwr[cnt[1]]);
}
void enterNum(int *pos) {
    scanf("%d", pos);
    arr.insert(*pos);
    ++bucket[*pos];
    if (bucket[*pos] == 1) cnt[1]++;
    if (bucket[*pos] == 2) cnt[1]--;
    if (bucket[*pos] >= 3) cnt[3]++;
}
void delNum(int *pos) {
    arr.erase(arr.lower_bound(*pos));
    if (bucket[*pos] == 1) cnt[1]--;
    if (bucket[*pos] == 2) cnt[1]++;
    if (bucket[*pos] >= 3) cnt[3]--;
    --bucket[*pos];
}
int main() {
    scanf("%d %d %d", &n, &m, &p);
    pwr[1] = 1;
    for (int i = 2; i <= n; i++) pwr[i] = pwr[i - 1] * 2 % p;
    for (int i = 1; i <= n; i++) enterNum(nums + i);
    checkUp();
    while (m--) {
        scanf("%d", &x);
        delNum(nums + x);
        enterNum(nums + x);
        checkUp();
    }
    return 0;
}
