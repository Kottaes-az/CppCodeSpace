#include <iostream>
int n, m, d[10010], lr = 0, hr = 0, max = 0, j = 0;
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    while (j <= n) {
        int sum = 0;
        j++;
        for (int i = j; i <= n; i++) {
            sum += d[i];
            if (sum > m) {
                sum -= d[i];
                break;
            }
            if (sum > max) {
                lr = j;
                hr = i;
                max = sum;
            }
        }
    }
    printf("%d %d %d", lr, hr, max);
    return 0;
}