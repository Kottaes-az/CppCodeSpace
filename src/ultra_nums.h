/**
 * @file ultra_nums.h
 * @author Kpocc (23687408@qq.com)
 * @brief
 * @version 0.2.0-core
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "ultra_nums_lib.h"
#include <bits/stdc++.h>

/* --(解)构造函数 */

/**
 * @brief vast类的构造与解构函数
 * @param Src:构造函数的值来源, 必须是 (可以转换为) vast, const char * 或
 * num_t的类型, 亦可为空, 则使用默认值0
 * @return void
 */
constexpr fau::vast::vast() noexcept { this->clear(); }
constexpr fau::vast::vast(const vast &vaSrc) noexcept {
    this->clear();
    this->self_data = vaSrc.self_data;
}
constexpr fau::vast::vast(const char *aSrc) noexcept { this->copy_str(aSrc); }
inline fau::vast::vast(const num_t &numSrc) noexcept { this->copy_num(numSrc); }

constexpr fau::vast::~vast() noexcept {
    this->clear();
    free(&(this->self_data));
}
/* (解)构造函数-- */

/* --静态方法 */
/**
 * @brief
 * 针对表示整数的std::string类型的整理函数,用以去除多余的前导0或其他杂糅的ASCII字符.
 * @param strSrc:原整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 包含一个合法整数.
 */
constexpr std::string
fau::basic_vast_operation::law_up(const std::string strNum) noexcept {
    // 虽然传入了可能不合法的%std::string, 但此处只为了去除原数中可能的负号,
    // 以方便下面的操作
    std::string strTemp = abs(strNum);

    for (const char iter : strTemp)
        if (!isdigit(iter)) return "0"; // 排查杂糅的ASCII字符
    while (!strTemp.empty() && strTemp.front() == '0')
        strTemp.erase(0, 1); // 去除前导0
    if (strNum.front() == '-')
        strTemp = '-' + strTemp; // 如果原数是负数, 则结果前插负号
    if (strTemp.empty()) strTemp = "0";
    return strTemp;
}

/**
 * @brief 针对表示整数的%std::string的取绝对值函数.
 * @param strNum:原整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 包含一个正序无符号整数.
 */
inline constexpr std::string
fau::basic_vast_operation::abs(const std::string strNum) noexcept {
    std::string strTemp = strNum;
    if (strTemp.front() == '-') strTemp.erase(0, 1);
    return strTemp;
}

/**
 * @brief 如果%std::string表示的整数为负数, 则返回true.
 * @param strNum:原整数, 必须是 (可以转换为) std::string 的类型.
 * @attention 必须传入一个合法的std::string类型.
 * 如果std::string表示的整数为0或正数, 均返回false.
 * @return bool类型, 表示std::string表示的整数是否为负数.
 */
inline constexpr bool
fau::basic_vast_operation::negative(const std::string strNum) noexcept {
    return strNum.front() == '-';
}

/**
 * @brief
 * 针对表示整数的两个%std::string类型进行的比较操作. 若第一个整数大于第二个整数,
 * 返回1; 若第一个整数小于第二个整数, 返回0; 若第一个整数小于第二个整数, 返回-1.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return int类型, 范围在 {0, 1, -1} 内.
 */
constexpr int fau::basic_vast_operation::compare(std::string strNum1,
                                                 std::string strNum2) noexcept {
    if (!negative(strNum1) && !negative(strNum2)) {
        strNum1 = law_up(strNum1), strNum2 = law_up(strNum2); // 合法化
        size_t length1 = strNum1.size(), length2 = strNum2.size();
        if (length1 > length2)
            return 1;
        else if (length1 == length2)
            return strNum1.compare(strNum2);
        return -1;
    }
    else if (negative(strNum1) && !negative(strNum2))
        return -1;
    else if (!negative(strNum1) && negative(strNum2))
        return 1;
    return compare(abs(strNum1), abs(strNum2)) * -1; // 表明两个数均为负数
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的加法操作.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为两个整数的和.(无序)
 */
constexpr std::string fau::basic_vast_operation::add(std::string strNum1,
                                                     std::string strNum2) {
    if (!negative(strNum1) && !negative(strNum2)) {
        size_t iter, length1 = strNum1.size(), length2 = strNum2.size();
        std::string result = "";

        // 翻转, 便于之后的相加与进位操作
        reverse(strNum1.begin(), strNum1.end());
        reverse(strNum2.begin(), strNum2.end());

        // 每一位相加, 减去一次ASCII的'0', 以防止溢出ASCII码范围
        for (iter = 0; iter < length1 && iter < length2; iter++)
            result += (char)(strNum1[iter] + strNum2[iter] - '0');

        // 加上较长的数的剩余部分
        while (iter < length1) result += strNum1[iter++];
        while (iter < length2) result += strNum2[iter++];

        // 进位操作, 因为翻转过, 所以从左往右
        int carry = 0; // 进位变量
        for (auto &tempIter : result) {
            int value = tempIter - '0' + carry;
            tempIter = (char)(value % 10 + '0');
            carry = value / 10;
        }

        // 如果可能, 另创一位加上进位剩余
        if (carry) result += (char)(carry + '0');

        reverse(result.begin(), result.end()); // 翻转回来
        result = law_up(result); // 合法化, 主要为去除前导0
        return result;
    }
    // 形如a+(-b)(a, b均为非负数)的加法算式可以变为a与b的减法算式
    else if (!negative(strNum1) && negative(strNum2))
        return minus(strNum1, abs(strNum2));
    // 原理同上
    else if (negative(strNum1) && !negative(strNum2))
        return minus(strNum2, abs(strNum1));
    // 到这里说明均为负数
    return "-" + add(abs(strNum1), abs(strNum2));
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的减法操作.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为第一个整数减去第二个整数的结果(即差, 有序).
 */
constexpr std::string fau::basic_vast_operation::minus(std::string strNum1,
                                                       std::string strNum2) {
    if (!negative(strNum1) && !negative(strNum2)) {
        // 减数大于被减数
        if (compare(strNum2, strNum1) > 0) return "-" + minus(strNum2, strNum1);

        // 到这里被减数就必然大于减数
        size_t iter, length1 = strNum1.size(), length2 = strNum2.size();
        std::string result = "";

        reverse(strNum1.begin(), strNum1.end());
        reverse(strNum2.begin(), strNum2.end());

        for (iter = 0; iter < length2; iter++)
            result += (char)(strNum1[iter] - strNum2[iter] + '0');

        while (iter < length1) result += strNum1[iter++];

        int carry = 0; // 借位变量
        for (auto &i : result) {
            int value = i - '0' + carry;
            (value < 0) ? (value += 10, carry = -1) : (carry = 0);
            i = (char)(value + '0');
        }

        reverse(result.begin(), result.end());
        result = law_up(result);
        return result;
    }
    // 原理同add方法
    else if (!negative(strNum1) && negative(strNum2))
        return add(strNum1, abs(strNum2));
    // 原理同上
    else if (negative(strNum1) && !negative(strNum2))
        return "-" + add(strNum2, abs(strNum1));
    // 到这里说明均为负数, -a - (-b) (a, b均为正数) 可以转化为b - a
    return minus(abs(strNum2), abs(strNum1));
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的乘法操作.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为第一个整数乘上第二个整数的结果(即积, 无序).
 */
constexpr std::string fau::basic_vast_operation::multiply(std::string strNum1,
                                                          std::string strNum2) {
    if (!negative(strNum1) && !negative(strNum2)) {
        size_t iter, jter, *arrResult;
        size_t length1 = strNum1.size(), length2 = strNum2.size();
        std::string result = "";

        reverse(strNum1.begin(), strNum1.end());
        reverse(strNum2.begin(), strNum2.end());

        // 以变量为数组长度以动态内存分配创建数组的一种方法
        arrResult = (size_t *)malloc(sizeof(size_t) * (length1 + length2 + 1));
        memset(arrResult, 0, sizeof(size_t) * (length1 + length2 + 1));

        for (iter = 0; iter < length1; iter++)
            for (jter = 0; jter < length2; jter++)
                arrResult[iter + jter] +=
                    ((strNum1[iter] - '0') * (strNum2[jter] - '0'));

        int carry = 0;
        for (iter = 0; iter < length1 + length2; iter++) {
            int value = arrResult[iter] + carry;
            arrResult[iter] = value % 10;
            carry = value / 10;
        }

        // 去除前导0
        for (iter = length1 + length2 - 1; iter >= 0; iter--)
            if (arrResult[iter] != 0) break;
        while (iter-- > 0) result += (char)(arrResult[iter] + '0');
        free(arrResult); // 释放数组的内存
        if (result.empty()) result = "0";
        return result;
    }
    // 形如a * (-b) (a, b均为正数)的乘法算式可以转化为 - (a * b)
    else if (negative(strNum1) && !negative(strNum2))
        return '-' + multiply(strNum2, abs(strNum1));
    // 原理同上
    else if (!negative(strNum1) && negative(strNum2))
        return '-' + multiply(strNum1, abs(strNum2));
    // 到这里表明两个整数均为负数, 在作乘法运算时负号抵消, 结果为正数
    return multiply(abs(strNum1), abs(strNum2));
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的整除操作.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为第一个整数整除第二个整数的结果(即整数商, 有序).
 */
constexpr std::string fau::basic_vast_operation::divide(std::string strNum1,
                                                        std::string strNum2) {
    if (!negative(strNum1) && !negative(strNum2)) {
        // 如果除数比被除数大, 则商为0
        if ((compare(strNum2, strNum1) > 0)) return "0";

        // 到这里被除数必然大于除数
        size_t nPos;
        size_t length1 = strNum1.size(), length2 = strNum2.size();
        std::string result = "", strTemp = "";

        // 从高位向低位取被除数与除数长度相同位数
        strTemp = strNum1.substr(0, length2);
        nPos = length2 - 1;

        while (nPos < length1) {
            int quotient = 0; // 临时商变量
            while (compare(strTemp, strNum2) >= 0) {
                quotient++;
                strTemp = minus(strTemp, strNum2);
            }
            result += (char)(quotient + '0');
            nPos++;
            if (nPos < length1) strTemp += strNum1[nPos];
        }

        result = law_up(result);
        return result;
    }
    else if (negative(strNum1) && !negative(strNum2))
        return "-" + divide(abs(strNum1), strNum2);
    else if (!negative(strNum1) && negative(strNum2))
        return "-" + divide(strNum1, abs(strNum2));
    return divide(abs(strNum1), abs(strNum2));
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的求余操作.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为第一个整数模以第二个整数的结果(即余数, 有序).
 */
constexpr std::string fau::basic_vast_operation::mod(std::string strNum1,
                                                     std::string strNum2) {
    if (compare(strNum1, strNum2) == 0)
        return "0";
    else if (negative(strNum1) || negative(strNum2))
        throw "a negative number when modding";
    std::string result =
        minus(strNum1, multiply(divide(strNum1, strNum2), strNum2));
    if (compare("0", result) > 0) result = add(result, strNum2);
    return result;
}

/**
 * @brief
 * 针对表示整数的两个std::string类型进行的求最大公约数操作. 使用欧几里得算法.
 * @param strNum1: 第一个整数, 必须是 (可以转换为) std::string 的类型.
 * @param strNum2: 第二个整数, 必须是 (可以转换为) std::string 的类型.
 * @return std::string类型, 为第一个整数和第二个整数的最大公约数(无序).
 */
constexpr std::string fau::basic_vast_operation::gcd(std::string strNum1,
                                                     std::string strNum2) {
    if (strNum1 == "0") return strNum2;
    if (strNum2 == "0") return strNum1;
    if (compare(strNum1, strNum2) == 0) std::swap(strNum1, strNum2);
    std::string result = mod(strNum1, strNum2);
    while (result != "0")
        strNum1 = strNum2, strNum2 = result, result = mod(strNum1, strNum2);
    return strNum2;
}

/* 静态方法-- */

/* --重载操作符与定义基本成员函数 */

/**
 * @brief 从std::string (或可以转换为std::string的) 类型复制并覆盖数据.
 * @attention 在操作前会强制使源数据合法化, 但这不改变其真实值.
 * @param strSrc:源数据, 必须是 (可以转换为) std::string 的类型.
 * @return void
 */
inline constexpr void fau::vast::copy_str(const std::string &strSrc) noexcept {
    this->clear();
    this->self_data = basic_vast_operation::law_up(strSrc);
}

/**
 * @brief 从一个fau::num_t类型 (一般定义为
 * long long int 或者被称为 int64_t) 复制并覆盖数据.
 * @attention 在操作前会强制使源数据合法化, 但这不改变其真实值.
 * @param numSrc:源数据, 必须是 (可以转换为) fau::num_t 的类型.
 * @return void
 */
inline void fau::vast::copy_num(const num_t &numSrc) noexcept {
    num_t numTemp = std::abs(numSrc); // 首先去除符号
    this->clear();
    while (numTemp) // 尾插法
        this->self_data += (char)(numTemp % 10 + '0'), numTemp /= 10;
    if (numSrc < 0) this->self_data = '-' + this->self_data; // 操作后加回符号
}

/**
 * @brief 如果%vast为负数, 则返回true.
 * @attention 如果%vast为0或正数, 均返回false.
 * @return bool类型, 表示%vast是否为负数.
 */
inline constexpr bool fau::vast::negative() const noexcept {
    return basic_vast_operation::negative(this->self_data);
}

/**
 * @brief 如果%vast为正数, 则返回true, 与negative方法相反.
 * @attention 如果%vast为0或负数, 均返回false.
 * @return bool类型, 表示%vast是否为正数.
 */
inline constexpr bool fau::vast::positive() const noexcept {
    return !basic_vast_operation::negative(this->self_data) &&
           this->self_data != "0";
}

/**
 * @brief 针对两个vast类型进行的整数加法操作.
 * @return vast类型, 为两个整数的和.(无序)
 */
inline constexpr fau::vast fau::vast::operator+(const vast &vaX) const {
    vast vaTemp(*this);
    vaTemp.self_data =
        basic_vast_operation::add(vaTemp.self_data, vaX.self_data);
    return vaTemp;
}

/**
 * @brief 针对两个vast类型进行的整数减法操作.
 * @return vast类型, 为两个整数的差.(有序)
 */
inline constexpr fau::vast fau::vast::operator-(const vast &vaX) const {
    vast vaTemp(*this);
    vaTemp.self_data =
        basic_vast_operation::minus(vaTemp.self_data, vaX.self_data);
    return vaTemp;
}

/**
 * @brief 针对两个vast类型进行的整数乘法操作.
 * @return vast类型, 为两个整数的积.(无序)
 */
inline constexpr fau::vast fau::vast::operator*(const vast &vaX) const {
    vast vaTemp(*this);
    vaTemp.self_data =
        basic_vast_operation::multiply(vaTemp.self_data, vaX.self_data);
    return vaTemp;
}

/**
 * @brief 针对两个vast类型进行的整数除法操作.
 * @return vast类型, 为两个整数的整数商.(有序)
 */
inline constexpr fau::vast fau::vast::operator/(const vast &vaX) const {
    vast vaTemp(*this);
    vaTemp.self_data =
        basic_vast_operation::divide(vaTemp.self_data, vaX.self_data);
    return vaTemp;
}

/**
 * @brief 针对两个vast类型进行的整数求余操作.(有序)
 * @return vast类型, 为第一个整数模以第二个整数的结果.
 */
inline constexpr fau::vast fau::vast::operator%(const vast &vaX) const {
    vast vaTemp(*this);
    vaTemp.self_data =
        basic_vast_operation::mod(vaTemp.self_data, vaX.self_data);
    return vaTemp;
}

/**
 * @brief 针对两个vast类型进行的判等操作.(无序) 若两个vast相等, 则返回true.
 * @return bool类型, 表示两个整数是否相等.
 */
constexpr bool fau::vast::operator==(const vast &vaX) const {
    return this->self_data == vaX.self_data;
}

/**
 * @brief 针对两个vast类型进行的不等于比较操作.(无序) 若两个vast不等,
 * 则返回true.
 * @return bool类型, 表示两个整数是否不等.
 */
constexpr bool fau::vast::operator!=(const vast &vaX) const {
    return !(this->operator==(vaX));
}
constexpr bool fau::vast::operator>(const vast &vaX) const {
    return basic_vast_operation::compare(this->self_data, vaX.self_data) > 0;
}
constexpr bool fau::vast::operator<(const vast &vaX) const {
    return basic_vast_operation::compare(this->self_data, vaX.self_data) < 0;
}
constexpr bool fau::vast::operator>=(const vast &vaX) const {
    return basic_vast_operation::compare(this->self_data, vaX.self_data) >= 0;
}
constexpr bool fau::vast::operator<=(const vast &vaX) const {
    return basic_vast_operation::compare(this->self_data, vaX.self_data) <= 0;
}

constexpr fau::vast fau::vast::operator=(const vast &vaX) {
    this->copy_str(vaX.self_data);
    return *this;
}
constexpr fau::vast::operator std::string() const { return this->self_data; }
constexpr fau::vast::operator num_t() const {
    num_t numTemp = 0;
    std::string strTemp = fau::basic_vast_operation::abs(this->self_data);
    while (!strTemp.empty()) // 尾插法
        numTemp = (numTemp * 10) + strTemp.front() - '0', strTemp.erase(0, 1);
    if (this->self_data.front() == '-') numTemp = -numTemp;
    return numTemp;
}
constexpr fau::vast fau::vast::operator+=(const vast &vaX) {
    *this = (this->operator+(vaX));
    return *this;
}
constexpr fau::vast fau::vast::operator-=(const vast &vaX) {
    *this = (this->operator-(vaX));
    return *this;
}
constexpr fau::vast fau::vast::operator*=(const vast &vaX) {
    *this = (this->operator*(vaX));
    return *this;
}
constexpr fau::vast fau::vast::operator/=(const vast &vaX) {
    *this = (this->operator/(vaX));
    return *this;
}
constexpr fau::vast fau::vast::operator%=(const vast &vaX) {
    *this = (this->operator%(vaX));
    return *this;
}
inline fau::vast fau::vast::operator++() {
    *this = (this->operator+(1));
    return *this;
}
inline fau::vast fau::vast::operator--() {
    *this = (this->operator-(1));
    return *this;
}
/* --重载操作符与定义基本成员函数 */

/* --容器化 */
inline constexpr const char *fau::vast::data() const noexcept {
    return this->self_data.data();
}
inline constexpr const char *fau::vast::c_str() const noexcept {
    return this->self_data.c_str();
}

/**
 * @brief 清除%vast, 使其为空.
 * @return void
 */
inline constexpr void fau::vast::clear() noexcept { this->self_data.clear(); }

/**
 * @brief 返回%vast中的数字个数, 不包含任何符号.
 * @return size_t类型, 为当前%vast中的数字位数(该vast的长度).
 */
inline constexpr size_t fau::vast::length() const noexcept {
    return fau::basic_vast_operation::abs(this->self_data).length();
}

/**
 * @brief 返回%vast中的数字个数, 不包含任何符号.
 * @return size_t类型, 为当前%vast中的数字位数(该vast的长度).
 */
inline constexpr size_t fau::vast::size() const noexcept {
    return fau::basic_vast_operation::abs(this->self_data).size();
}

/**
 * @brief 如果%vast为空, 则返回true.
 * @return bool类型, 表示%vast是否为空.
 */
inline constexpr bool fau::vast::empty() const noexcept {
    return this->self_data.empty();
}
/**
 * @brief 访问下标位上的数字.
 * @param nPos:要访问处的下标.
 * @attention 下标从1开始, 从低位向高位(从右至左).
 * @return digit_t类型(一般定义为char, 或者被称为int8_t), 为下标nPos处的数字.
 * @throw 如果 nPos 是无效数字, 抛出std::out_of_range.
 * 此函数不同于std::string类型的at方法, 仅返回下标处的值.
 * 首先将检查请求的下标是否在当前%vast长度范围内. 如果发生检查错误,
 * 则抛出std::out_of_range.
 */
inline constexpr fau::digit_t fau::vast::value_at(size_t nPos) const {
    return (this->self_data.at(this->self_data.size() - nPos) - '0');
}

/**
 * @brief 返回%vast的最高位上的数字.
 * @attention 下标从1开始, 从低位向高位(从右至左).
 * @return digit_t类型, 为最高位上的数字.
 */
inline constexpr fau::digit_t fau::vast::front() const noexcept {
    return this->self_data.front() - '0';
}

/**
 * @brief 返回%vast的个位上的数字.
 * @attention 下标从1开始, 从低位向高位(从右至左).
 * @return digit_t类型, 为个位上的数字.
 */
inline constexpr fau::digit_t fau::vast::back() const noexcept {
    return this->self_data.back() - '0';
}
/* 容器化-- */

inline std::ostream &operator<<(std::ostream &strmOut, fau::vast &vaSrc) {
    strmOut << vaSrc.data();
    return strmOut;
}
inline std::istream &operator>>(std::istream &strmIn, fau::vast &vaDest) {
    vaDest.clear();
    std::string strTemp;
    strmIn >> strTemp;
    vaDest.copy_str(strTemp);
    return strmIn;
}