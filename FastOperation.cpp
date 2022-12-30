#include <bits/stdc++.h>
#include <src/fauc++.h>
fau::vast a[3];
int main() {
    for (auto &i : a) std::cin >> i;
    for (size_t i = 0; i < 3; i++) std::cout << a[i] << ' ';
    return 0;
}