#include <bits/stdc++.h>
const int LIM = 1e5 + 10;
int n, m, cnt;
std::set<int> infos;
int main() {
    scanf("%d %d", &n, &m);
    while (n--) {
        int v;
        scanf("%d", &v);
        infos.insert(v);
    }
    while (m--) {
        int f;
        scanf("%d", &f);
        std::set<int>::iterator iter;
        for (iter = infos.begin(); iter != infos.end(); iter++) {
            std::bitset<30> temp(f ^ *iter);
            if (temp.count() == 2) {
                cnt++;
                infos.erase(iter);
                break;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}