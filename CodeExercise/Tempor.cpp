#include <bits/stdc++.h>
int n;
typedef long num_t;
num_t fast_pow(num_t numBase, num_t numPower) {
    num_t numAns = 1;
    if (!numBase && !numPower) return -1;
    while (numPower) {
        if (numPower & 1) numAns *= numBase;
        numPower >>= 1;
        numBase *= numBase;
    }
    return numAns;
}
int main() {
    std::scanf("%d", &n);
    printf("%ld\n", (num_t)fast_pow(2, n));
    return 0;
}