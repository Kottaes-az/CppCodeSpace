/**
 * @file ultra_nums_lib.h
 * @author Kpocc (23687408@qq.com)
 * @brief
 * @version 0.2.0-lib
 * @date 2022-12-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <cstdint>
#include <string>
/* 来源于网络：
 * tremendous 指某物很大，大得惊人；也可用作引申意义。
 * colossal 侧重尺寸、规模和体积的无比巨大。
 * huge 含义广，强调体积或容积的庞大。也可用于引申意义。
 * gigantic 指面积或体积的巨大，但多用于引申意义。
 * massive 指大的体积、数量和重量，侧重庞大而笨重。
 * vast 多指空间、面积、范围的巨大，不涉及重量。
 * enormous 指体积、数量或程度远远超过一般标准。[异常大，超出了正常的限度和比例]
 * immense 正式用词，侧重空间的广阔，也指面积或分量的巨大。[大得无法测算的]
 */
/* comparing:
    vast(vast) : 用std::string方法构建的无上(下)限任意进制整数. !常用
    gigantic(tant) :
    用std::string方法构建的无上(下)限任意进制有理分数(浮点数).
    colossal_bit(colbin) : 用std::bitset方法构造的64~128位二进制无符号整数.
    immense(mense) :
    以两个不同vast分别存储一个数的整数部分和小数部分,以此种方法来构造有理数.
    enormous(norm) : !常用
    在immense基础上,
    针对无限循环小数进行记录分子和分母的表示(针对数据类型智能分配),以此减小误差.
*/

namespace fau {
    typedef long long num_t;
    typedef char digit_t;
    namespace basic_vast_operation {
        /* --静态方法 */
        constexpr static std::string law_up(std::string) noexcept;
        constexpr static std::string abs(const std::string) noexcept;
        constexpr static bool negative(const std::string) noexcept;
        constexpr static int
            compare(std::string,
                    std::string) noexcept; // if num1>num2,return 1,else if
                                           // num1=num2,return 0,else return -1;
        constexpr static std::string add(std::string,
                                         std::string); // num1+num2
        constexpr static std::string minus(std::string,
                                           std::string); // num1-num2
        constexpr static std::string multiply(std::string,
                                              std::string); // num1*num2
        constexpr static std::string divide(std::string,
                                            std::string); // num1/num2
        constexpr static std::string mod(std::string,
                                         std::string); // num1 mod num2
        constexpr static std::string gcd(std::string,
                                         std::string); // gcd(num1,num2)
        /* 静态方法-- */
    } // namespace basic_vast_operation
    class vast {
      public:
        constexpr vast() noexcept;
        constexpr vast(const vast &) noexcept;
        constexpr vast(const char *) noexcept;
        vast(const num_t &) noexcept;
        constexpr ~vast() noexcept;

      private:
        std::string self_data;

      public:
        /* --重载操作符与声明基本成员函数 */
        constexpr void copy_str(const std::string &) noexcept;
        void copy_num(const num_t &) noexcept;
        constexpr bool positive() const noexcept;
        constexpr bool negative() const noexcept;
        constexpr vast operator+(const vast &) const;  //+
        constexpr vast operator-(const vast &) const;  //-
        constexpr vast operator*(const vast &) const;  // operator*
        constexpr vast operator/(const vast &) const;  ///
        constexpr vast operator%(const vast &) const;  // mod
        constexpr bool operator==(const vast &) const; //==
        constexpr bool operator!=(const vast &) const; // operator!=
        constexpr bool operator>(const vast &) const;  //>
        constexpr bool operator<(const vast &) const;  //<
        constexpr bool operator>=(const vast &) const; //>=
        constexpr bool operator<=(const vast &) const; //<=
        constexpr vast operator=(const vast &);        //=
        constexpr vast operator+=(const vast &);       //+=
        constexpr vast operator-=(const vast &);       //-=
        constexpr vast operator*=(const vast &);       // operator*=
        constexpr vast operator/=(const vast &);       // operator/=
        constexpr vast operator%=(const vast &);       //%=
        vast operator++();                   //++
        vast operator--();                   //--
        constexpr operator std::string() const;
        constexpr operator num_t() const;
        /* 重载操作符与声明基本成员函数-- */

        /* --容器化 */
        constexpr const char *data() const noexcept;
        constexpr const char *c_str() const noexcept;
        constexpr void clear() noexcept;
        constexpr size_t length() const noexcept;
        constexpr size_t size() const noexcept;
        constexpr bool empty() const noexcept;
        constexpr digit_t value_at(size_t) const;
        constexpr digit_t front() const noexcept;
        constexpr digit_t back() const noexcept;
        /* 容器化-- */
    }; // vast integer
} // namespace fau
std::ostream &operator<<(std::ostream &, fau::vast &);
std::istream &operator>>(std::istream &, fau::vast &);