#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <stdexcept>
using namespace std;

class BigInteger {
private:
    vector<int> digits;  // 存储数字，低位在前
    bool is_negative;    // 是否为负数
    
    // 移除前导零
    void trim() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) {
            is_negative = false;
        }
    }
    
    // 比较绝对值大小
    int compare_abs(const BigInteger& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size() ? 1 : -1;
        }
        for (int i = (int)digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i] ? 1 : -1;
            }
        }
        return 0;
    }
    
    // 无符号加法
    static BigInteger add_abs(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        int carry = 0;
        size_t n = max(a.digits.size(), b.digits.size());
        result.digits.resize(n, 0);
        
        for (size_t i = 0; i < n; i++) {
            int sum = carry;
            if (i < a.digits.size()) sum += a.digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        
        if (carry) {
            result.digits.push_back(carry);
        }
        
        return result;
    }
    
    // 无符号减法，假设a >= b
    static BigInteger sub_abs(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        int borrow = 0;
        result.digits.resize(a.digits.size(), 0);
        
        for (size_t i = 0; i < a.digits.size(); i++) {
            int diff = a.digits[i] - borrow;
            if (i < b.digits.size()) diff -= b.digits[i];
            
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            result.digits[i] = diff;
        }
        
        result.trim();
        return result;
    }
    
    // 朴素乘法
    static BigInteger naive_multiply(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        result.digits.resize(a.digits.size() + b.digits.size(), 0);
        
        for (size_t i = 0; i < a.digits.size(); i++) {
            int carry = 0;
            for (size_t j = 0; j < b.digits.size(); j++) {
                int product = result.digits[i + j] + a.digits[i] * b.digits[j] + carry;
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
            if (carry) {
                result.digits[i + b.digits.size()] += carry;
            }
        }
        
        result.trim();
        return result;
    }
    
    // 除法辅助函数：试商
    static int estimate_quotient(const BigInteger& a, const BigInteger& b) {
        int left = 0, right = 9;
        int result = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            BigInteger temp = b * BigInteger(mid);
            
            if (temp.compare_abs(a) <= 0) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }

public:
    // 构造函数
    BigInteger() : is_negative(false) {
        digits.push_back(0);
    }
    
    BigInteger(long long num) {
        if (num < 0) {
            is_negative = true;
            num = -num;
        } else {
            is_negative = false;
        }
        
        if (num == 0) {
            digits.push_back(0);
        } else {
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
        }
    }
    
    BigInteger(const string& str) {
        is_negative = false;
        
        if (str.empty()) {
            digits.push_back(0);
            return;
        }
        
        int start = 0;
        if (str[0] == '-') {
            is_negative = true;
            start = 1;
        } else if (str[0] == '+') {
            start = 1;
        }
        
        // 跳过前导零
        while (start < (int)str.size() - 1 && str[start] == '0') {
            start++;
        }
        
        for (int i = (int)str.size() - 1; i >= start; i--) {
            if (isdigit(str[i])) {
                digits.push_back(str[i] - '0');
            } else {
                throw invalid_argument("Invalid character in number string");
            }
        }
        
        trim();
    }
    
    // 比较运算符
    bool operator<(const BigInteger& other) const {
        if (is_negative != other.is_negative) {
            return is_negative;
        }
        
        int cmp = compare_abs(other);
        if (is_negative) {
            return cmp > 0;
        } else {
            return cmp < 0;
        }
    }
    
    bool operator<=(const BigInteger& other) const {
        return !(other < *this);
    }
    
    bool operator>(const BigInteger& other) const {
        return other < *this;
    }
    
    bool operator>=(const BigInteger& other) const {
        return !(*this < other);
    }
    
    bool operator==(const BigInteger& other) const {
        if (is_negative != other.is_negative || digits.size() != other.digits.size()) {
            return false;
        }
        
        for (size_t i = 0; i < digits.size(); i++) {
            if (digits[i] != other.digits[i]) {
                return false;
            }
        }
        
        return true;
    }
    
    bool operator!=(const BigInteger& other) const {
        return !(*this == other);
    }
    
    // 一元运算符
    BigInteger operator-() const {
        BigInteger result = *this;
        if (result != BigInteger(0)) {
            result.is_negative = !result.is_negative;
        }
        return result;
    }
    
    // 加法运算符
    BigInteger operator+(const BigInteger& other) const {
        if (is_negative == other.is_negative) {
            BigInteger result = add_abs(*this, other);
            result.is_negative = is_negative;
            return result;
        } else {
            int cmp = compare_abs(other);
            if (cmp == 0) {
                return BigInteger(0);
            } else if (cmp > 0) {
                BigInteger result = sub_abs(*this, other);
                result.is_negative = is_negative;
                return result;
            } else {
                BigInteger result = sub_abs(other, *this);
                result.is_negative = other.is_negative;
                return result;
            }
        }
    }
    
    // 减法运算符
    BigInteger operator-(const BigInteger& other) const {
        return *this + (-other);
    }
    
    // 乘法运算符
    BigInteger operator*(const BigInteger& other) const {
        if (*this == BigInteger(0) || other == BigInteger(0)) {
            return BigInteger(0);
        }
        
        BigInteger result = naive_multiply(*this, other);
        result.is_negative = is_negative ^ other.is_negative;
        result.trim();
        return result;
    }
    
    // 除法运算符
    BigInteger operator/(const BigInteger& other) const {
        if (other == BigInteger(0)) {
            throw runtime_error("Division by zero");
        }
        
        BigInteger dividend = *this;
        BigInteger divisor = other;
        dividend.is_negative = false;
        divisor.is_negative = false;
        
        if (dividend < divisor) {
            return BigInteger(0);
        }
        
        BigInteger quotient;
        quotient.digits.clear();
        
        BigInteger current;
        for (int i = (int)dividend.digits.size() - 1; i >= 0; i--) {
            current.digits.insert(current.digits.begin(), dividend.digits[i]);
            current.trim();
            
            if (current < divisor) {
                quotient.digits.insert(quotient.digits.begin(), 0);
            } else {
                int q = estimate_quotient(current, divisor);
                quotient.digits.insert(quotient.digits.begin(), q);
                current = current - divisor * BigInteger(q);
            }
        }
        
        quotient.trim();
        quotient.is_negative = is_negative ^ other.is_negative;
        if (quotient.digits.empty()) {
            quotient.digits.push_back(0);
            quotient.is_negative = false;
        }
        
        return quotient;
    }
    
    // 取模运算符
    BigInteger operator%(const BigInteger& other) const {
        if (other == BigInteger(0)) {
            throw runtime_error("Modulo by zero");
        }
        return *this - (*this / other) * other;
    }
    
    // 复合赋值运算符
    BigInteger& operator+=(const BigInteger& other) {
        *this = *this + other;
        return *this;
    }
    
    BigInteger& operator-=(const BigInteger& other) {
        *this = *this - other;
        return *this;
    }
    
    BigInteger& operator*=(const BigInteger& other) {
        *this = *this * other;
        return *this;
    }
    
    BigInteger& operator/=(const BigInteger& other) {
        *this = *this / other;
        return *this;
    }
    
    BigInteger& operator%=(const BigInteger& other) {
        *this = *this % other;
        return *this;
    }
    
    // 递增递减运算符
    BigInteger& operator++() {
        *this += BigInteger(1);
        return *this;
    }
    
    BigInteger operator++(int) {
        BigInteger temp = *this;
        ++(*this);
        return temp;
    }
    
    BigInteger& operator--() {
        *this -= BigInteger(1);
        return *this;
    }
    
    BigInteger operator--(int) {
        BigInteger temp = *this;
        --(*this);
        return temp;
    }
    
    // 类型转换运算符
    explicit operator bool() const {
        return *this != BigInteger(0);
    }
    
    explicit operator int() const {
        int result = 0;
        int multiplier = 1;
        
        for (size_t i = 0; i < digits.size() && i < 10; i++) {
            result += digits[i] * multiplier;
            multiplier *= 10;
        }
        
        return is_negative ? -result : result;
    }
    
    // 输入输出运算符
    friend ostream& operator<<(ostream& os, const BigInteger& num) {
        if (num.is_negative) {
            os << '-';
        }
        
        for (int i = (int)num.digits.size() - 1; i >= 0; i--) {
            os << num.digits[i];
        }
        
        return os;
    }
    
    friend istream& operator>>(istream& is, BigInteger& num) {
        string str;
        is >> str;
        num = BigInteger(str);
        return is;
    }
    
    // 实用函数
    bool is_zero() const {
        return digits.size() == 1 && digits[0] == 0;
    }
    
    bool is_positive() const {
        return !is_negative && !is_zero();
    }
    
    bool is_negative_val() const {
        return is_negative;
    }
    
    string to_string() const {
        string result;
        if (is_negative) {
            result += '-';
        }
        
        for (int i = (int)digits.size() - 1; i >= 0; i--) {
            result += char(digits[i] + '0');
        }
        
        return result;
    }
    
    // 绝对值
    BigInteger abs() const {
        BigInteger result = *this;
        result.is_negative = false;
        return result;
    }
    
    // 快速幂
    static BigInteger pow(const BigInteger& base, const BigInteger& exponent) {
        if (exponent < BigInteger(0)) {
            return BigInteger(0);
        }
        
        if (exponent == BigInteger(0)) {
            return BigInteger(1);
        }
        
        BigInteger result = BigInteger(1);
        BigInteger temp_base = base;
        BigInteger temp_exp = exponent;
        
        while (temp_exp > BigInteger(0)) {
            if (temp_exp % BigInteger(2) == BigInteger(1)) {
                result = result * temp_base;
            }
            temp_base = temp_base * temp_base;
            temp_exp = temp_exp / BigInteger(2);
        }
        
        return result;
    }
    
    // 最大公约数
    static BigInteger gcd(BigInteger a, BigInteger b) {
        a = a.abs();
        b = b.abs();
        
        while (b != BigInteger(0)) {
            BigInteger temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // 最小公倍数
    static BigInteger lcm(const BigInteger& a, const BigInteger& b) {
        BigInteger g = gcd(a, b);
        if (g == BigInteger(0)) {
            return BigInteger(0);
        }
        return (a * b) / g;
    }
};
BigInteger a,b;
int main(){
    cin >> a >> b;
    cout << a+b;
    return 0;
}