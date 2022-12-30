#include <cmath>
#include <iostream>
int main() {
    float n, x, y;
    scanf("%g %g %g", &n, &x, &y);
    printf("%d", int(n - ceil(y / x)));
    return 0;
}