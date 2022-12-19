#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
const string SYS_LANG = "zh_CN";
/* string langs[] = {
    "zh_CN", "zh_TW", "zh_HK",
    "en_US", "en_GB", "en_WW", "en_XX",
    "ru_RU",
    "fr_FR", "fr_LU", "fr_CA", "fr_BE", "fr_CH",
    "es_LA", "es_AR", "es_US", "es_MX", "es_CO", "es_CL", "es_ES", "es_PR",
    "pt_PT", "pt_BR",
    "nl_NL", "nl_BE",
    "de_DE", "de_AT", "de_CH",
    "fi_FI", "da_DK", "he_IL", "ko_KR", "it_IT", "no_NO", "hu_HU", "tr_TR",
    "cs_CZ", "sl_SL", "pl_PL", "sv_SE", "UNKNOWN_LANGUAGE"}; */

int fibonacci(int n)
{
    /**
     * 求斐波那契数列的第n个数。
     * 参数1：正整数，所求数的在数列项数。
     * 返回值：正整数，所求的数列中的数。
     * **/
    if (n < 2) return n; //第0,1个数：0,1
    if (n >= 2)
        return (fibonacci(n - 1) +
                fibonacci(n - 2)); //第n(n>2)个数位前两个数之和
    return -1;                     //异常值处理
}
void iArr(int *a, int n)
{
    //输入一个一维数组。首先确定数组元素个数n，然后输入n个整数。
    for (int i = 0; i < n; i++) scanf("%d", a + i);
}

void oArr(int *a, int n)
{
    //输出一个一维数组。首先确定需要输出的数组的元素个数n，然后输出n个整数。
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
class SortSolution
{
  private:
    void maxHeapify(int *a, int start, int end)
    {
        // 建立父节点指标和子节点指标
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end) { // 若子节点指标在范围内才做比较
            if (son + 1 <= end &&
                a[son] < a[son + 1]) // 先比较两个子节点大小，选择最大的
                son++;
            if (a[dad] >
                a[son]) // 如果父节点大于子节点代表调整完毕，直接跳出函数
                return;
            else { // 否则交换父子内容再继续子节点和孙节点比较
                swap(a[dad], a[son]);
                dad = son;
                son = dad * 2 + 1;
            }
        }
    }

  public:
    void bubbleSort(int *a, int n, bool fac1 = true, bool fac2 = true)
    {

        /**
         * 冒泡排序算法，包含两种可选择的子算法。
         * 平均(最坏、好)时间复杂度:O(n^2)
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * 参数3:布尔值，是否使用前n项算法(默认)。false为后n项算法，true为前n项算法。
         * 参数4:布尔值，是否使用非降序排序(默认)。false为非升序，true为非降序。
         * 子算法说明:前n项算法:传统冒泡排序，即在第n轮排序中，通过冒泡将前n项中的最大值放置到数组第n个。
         *          后n项算法:改造的冒泡排序，即在第n轮排序中，通过冒泡将后n项中的最大值放置到数组第n个。
         * **/
        int i, j;
        if (fac1) //前n项算法
            for (j = 0; j < n - 1; j++)
                for (i = 0; i < n - 1 - j; i++) {
                    if ((fac2) && (a[i] > a[i + 1]))
                        swap(a[i], a[i + 1]); //非降序排列
                    if ((!fac2) && (a[i] < a[i + 1]))
                        swap(a[i], a[i + 1]); //非升序排列
                }
        if (!fac1) //后n项算法
            for (j = 0; j < n; j++)
                for (i = n - j - 1; i < n; i++) {
                    if ((fac2) && (a[i - 1] > a[i]))
                        swap(a[i], a[i - 1]); //非降序排列
                    if ((!fac2) && (a[i] < a[i + 1]))
                        swap(a[i], a[i + 1]); //非升序排列
                }
        else
            printf("%d", 0);
    }
    void cppSort(int *a, int n, bool fac = true)
    {
        /**
         * algorithm库sort排序算法。
         * 平均(最好)时间复杂度:O(n log n) 最坏时间复杂度:O(n^2)
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * 参数2:布尔值，是否使用非降序(默认)排序。false为非升序，true为非降序。
         * **/
        if (fac) sort(a, a + n, less<int>());     // 非降序排列
        if (!fac) sort(a, a + n, greater<int>()); // 非升序排列
    }
    void quickSort(int *a, int n, int l = 0, int r = 0)
    {
        /**
         * 标准快速排序算法，排序结果为非降序数组。
         * 平均(最好)时间复杂度:O(n log n) 最坏时间复杂度:O(n^2)
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * 参数3,4:分别为数组需要操作的范围左、右区间。参数3默认为0(最初索引)，参数4默认为元素个数-1
         * **/
        if (!r) r = n - 1;  //参数4默认为元素个数-1
        if (l >= r) return; //若待排序序列只有一个元素，返回空
        int i = l, j = r; // i,j作为指针分别从左向右、从右向左扫描
        int key = a[l]; //第一个数作为基准数
        while (i < j) {
            while (a[j] >= key && i < j) //从右边找小于基准数的元素
                //（此处由于j值可能会变，所以仍需判断i是否小于j）
                j--;                     //找不到则j减一
            a[i] = a[j];                 //找到则赋值
            while (a[i] <= key && i < j) //从左边找大于基准数的元素
                i++;                     //找不到则i加一
            a[j] = a[i];                 //找到则赋值
        }
        a[i] = key; //当i和j相遇，将基准元素赋值到指针i处
        quickSort(a, l, i - 1); // i左边的序列继续递归调用快排
        quickSort(a, i + 1, r); // i右边的序列继续递归调用快排
    }
    void selectionSort(int *a, int n, int fac = true)
    {
        /**
         * 选择排序算法。可选结果为非升/降序数组。
         * 平均时间复杂度:O(n^2)
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * 参数3:布尔值，是否使用非降序排序(默认)。false为非升序，true为非降序。
         * **/
        if (fac)
            for (int i = 0; i < n - 1; i++) {
                int min = i;
                for (int j = i + 1; j < n; j++)
                    if (a[j] < a[min]) min = j;
                swap(a[i], a[min]);
            }
        if (!fac)
            for (int i = 0; i < n - 1; i++) {
                int max = i;
                for (int j = i + 1; j < n; j++)
                    if (a[j] > a[max]) max = j;
                swap(a[i], a[max]);
            }
    }
    void insertionSort(int *a, int n)
    {
        /**
         * 插入排序算法。结果为非降序数组。
         * 平均时间复杂度:O(n^(1-2))
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * **/
        for (int i = 1; i < n; i++) {
            int key = a[i];
            int j = i - 1;
            while ((j >= 0) && (key < a[j])) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }
    void shellSort(int *a, int n)
    {
        /**
         * 希尔排序算法。结果为非降序数组。
         * 平均时间复杂度:O(n^(1.3-2))
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * **/
        int h = 1;
        while (h < n / 3) h = 3 * h + 1;
        while (h >= 1) {
            for (int i = h; i < n; i++)
                for (int j = i; j >= h && a[j] < a[j - h]; j -= h)
                    swap(a[j], a[j - h]);
            h /= 3;
        }
        while (h >= 1) {
            for (int i = h; i < n; i++)
                for (int j = i; j >= h && a[j] < a[j - h]; j -= h)
                    swap(a[j], a[j - h]);
            h /= 3;
        }
    }
    void heapSort(int *a, int n)
    {
        /**
         * 堆排序算法。结果为非降序数组。
         * 平均时间复杂度:O(n)
         * 参数1:需要操作的数组。
         * 参数2:控制数组元素个数。
         * **/
        // 初始化，i从最后一个父节点开始调整
        for (int i = n / 2 - 1; i >= 0; i--) maxHeapify(a, i, n - 1);
        // 先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完毕
        for (int i = n - 1; i > 0; i--) {
            swap(a[0], a[i]);
            maxHeapify(a, 0, i - 1);
        }
    }
} sortModule;
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) a[i] = fibonacci(i);
    oArr(a, n);
    return 0;
}