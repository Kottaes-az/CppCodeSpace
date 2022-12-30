#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void wordToken(char **dest, char src[], char opr[2] = {}) {
        size_t j = 0;
        char *token;
        token = strtok(src, opr);
        while (token != NULL) {
            dest[j++] = token;
            token = strtok(NULL, opr);
        }
    }
    bool isLeap(size_t a) { // 判断是否闰年
        return (!(a % 4) && (a % 100)) || !(a % 400);
    }
    void deci2Any(size_t n, int m) { // 将十进制数n转为m进制，2<=m<=16
        if (!n) return;
        long tmp = n % m;
        n /= m;
        deci2Any(n, m);
        if (m > 10 && tmp > 9) {
            printf("%c", tmp + 55);
            return;
        }
        printf("%d", tmp);
    }
    template <class T1> size_t maxIndex(T1 a[], size_t length) {
        // 算法：基础打擂，返回下标
        size_t max = 0;
        for (size_t i = 0; i < length; i++)
            if (a[i] > a[max]) max = i;
        return max;
    }
    template <class T1> size_t minIndex(T1 a[], size_t length) {
        // 算法：基础打擂，返回下标
        size_t min = 0;
        for (size_t i = 0; i < length; i++)
            if (a[i] < a[min]) min = i;
        return min;
    }
    size_t maxDeci(size_t n) { // 求最高位位数
        size_t i = 10;
        while (n / i >= 10) i *= 10;
        return i;
    }
    size_t inv(size_t n) { // 数学方法求倒序数
        if (n < 10) return n;
        return (n % 10) * maxDeci(n) + inv(n / 10);
    }
    size_t inRange(size_t a[], size_t length, size_t bor, size_t min,
                   size_t max, char check[] = "FailCount") {
        //  判断数组里有多少个数不在给定范围(闭集)内(inv的值)，或在此基础上判断有多少个数不在亚范围内(fail的值)
        //    (可理解为考试及格线问题)
        size_t fail = 0, inv = 0;
        for (size_t i = 0; i < length; i++)
            if (a[i] >= min && a[i] < bor)
                fail++;
            else if (!(a[i] >= min && a[i] <= max))
                inv++;
        return ("FailCount" == check) ? fail : inv;
    }
    int minSizeSubarray(int nums[], int len, int target) { // 长度最小的子数组
        int sum = 0, subl = 0, subr = 0, mink = INT_MAX;
        while (subl <= subr) {
            while (subr < len && sum < target) sum += nums[++subr];
            if (subr < len && sum >= target)
                mink = (mink < subr - subl) ? mink : subr - subl;
            else if (subr == len && sum >= target)
                mink = (mink < len - subl) ? mink : len - subl;
            else
                break;
            sum -= nums[++subl];
        }
        return (INT_MAX == mink) ? 0 : mink;
        for (int i = subl; i < subr; i++) printf("%d ", nums[i]);
    }
    size_t numberOfKInRange(const size_t rangeRight, const size_t destNum) {
        // 寻找[0,rangeRight]范围内k(0<=destNum<=10)出现的次数（e.g. destNum =
        // 2,
        //  n = 22,
        //  则cnt = 3(包括2中的一个2,12中的一个2,20中的一个2和22中的2个2))
        size_t cnt = 0;
        for (size_t i = 0; i <= rangeRight; i++) {
            size_t j = i;
            while (j) {
                if (j % 10 == destNum) cnt++;
                j /= 10;
            }
        }
        return cnt;
    }
    size_t josephusProblem(const size_t totNum, const size_t factorNum) {
        // 约瑟夫问题
        // 返回最后被淘汰的人的原始编号,totNum为总人数,factorNum为报数者因数
        size_t *tempArr = (size_t *)malloc(sizeof(size_t) * (totNum + 1));
        fill(tempArr, tempArr + sizeof(tempArr), 0);
        for (int i = 1; i <= totNum; i++) tempArr[i] = i; // 给每一项赋值原始编号
        // restNum标记剩下的人数,curIndex标记当前正在报数的人的编号,lastNum标记最后淘汰的人的原始编号
        size_t restNum = totNum, curIndex = 0, lastIndex = 0;
        while (restNum)
            for (int i = 1; i <= totNum; i++) {
                if (!tempArr[i]) continue;
                curIndex++;
                if (curIndex == factorNum)
                    tempArr[i] = curIndex = 0, lastIndex = i, restNum--;
            }
        return lastIndex; // 返回0表示错误情况
    }
    bool isPrime(const size_t srcNum) {
        // 判断一个数srcNum是否为质数
        if (srcNum <= 3) return srcNum > 1;
        for (size_t i = 2; i * i <= srcNum; i++)
            if (!(srcNum % i)) return false;
        return true;
    }
    int atoiReverse(const double srcNum) {
        // 用字符串倒序方法求一个数srcNum的反序数(e.g. atoiReverse(123)=321)
        string tempStr = to_string(srcNum), retStr;
        for (size_t i = 0; i < tempStr.size(); i++)
            retStr[i] = tempStr[tempStr.size() - i - 1];
        return atoi((const char *)retStr.c_str());
    }
    void decomposeBaseNum(size_t srcNum, ssize_t *destArr,
                          const size_t baseNum = 2) {
        // 数字分解问题，将一个数srcNum分解为若干个baseNum的正整数次幂之和的形式,
        // 当且仅当srcNum为baseNum的倍数数，将操作结果存入数组destArr中
        // curIndex:当前应存入数的数组空间的编号，tempPow:临时分离出的最大baseNum的正整数次幂
        size_t curIndex = 0, tempPow;
        if (srcNum %
            baseNum) // 如果srcNum不为baseNum的倍数，将destArr数组第一项变为-1
            *destArr = -1;
        else
            while (srcNum) {
                for (size_t i = 1; pow(baseNum, i) <= srcNum; i++)
                    tempPow = pow(baseNum, i);
                destArr[curIndex++] = tempPow, srcNum -= tempPow;
            }
    }
    size_t quickPower(size_t oprBase, size_t oprPower) {
        size_t ansNum = 1;
        while (oprPower) {
            if (oprPower & 1) ansNum *= oprBase;
            oprPower >>= 1;
            oprBase *= oprBase;
        }
        return ansNum;
    }
};
int main() {
    Solution modules;
    cout << modules.quickPower(2, 5) << endl;
    return 0;
}