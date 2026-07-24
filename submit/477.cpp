#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

// 快速输入输出优化
namespace FastIO {
    inline char nc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
    }
    
    inline void read(string &s) {
        s.clear();
        char c = nc();
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = nc();
        while (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != EOF) {
            s += c;
            c = nc();
        }
    }
    
    inline void write(char c) {
        putchar(c);
    }
    
    inline void write(const string &s) {
        for (char c : s) {
            putchar(c);
        }
    }
}

// 支持负数的高精度数类
class BigInt {
public:
    vector<int> digits;  // 逆序存储，digits[0]是个位
    bool isNegative;     // 符号位
    
    // 默认构造函数
    BigInt() {
        digits.push_back(0);
        isNegative = false;
    }
    
    // 字符串构造函数
    BigInt(const string& s) {
        isNegative = false;
        string str = s;
        
        // 处理负号
        if (str[0] == '-') {
            isNegative = true;
            str = str.substr(1);
        }
        
        for (int i = str.length() - 1; i >= 0; i--) {
            digits.push_back(str[i] - '0');
        }
        removeLeadingZeros();
        
        // 如果是0，确保不是负数
        if (digits.size() == 1 && digits[0] == 0) {
            isNegative = false;
        }
    }
    
    // 整数构造函数
    BigInt(long long num) {
        isNegative = false;
        if (num < 0) {
            isNegative = true;
            num = -num;
        }
        
        if (num == 0) {
            digits.push_back(0);
            return;
        }
        
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
    
    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }
    
    // 比较绝对值大小
    bool absLess(const BigInt& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() < other.digits.size();
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i];
            }
        }
        return false; // 相等
    }
    
    // 绝对值加法
    BigInt absAdd(const BigInt& other) const {
        BigInt result(0LL);
        result.digits.clear();
        result.isNegative = false;
        
        int carry = 0;
        int maxLen = max(digits.size(), other.digits.size());
        
        for (int i = 0; i < maxLen || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        
        result.removeLeadingZeros();
        return result;
    }
    
    // 绝对值减法（假设this >= other）
    BigInt absSub(const BigInt& other) const {
        BigInt result(0LL);
        result.digits.clear();
        result.isNegative = false;
        
        int borrow = 0;
        for (int i = 0; i < digits.size(); i++) {
            int diff = digits[i] - borrow;
            if (i < other.digits.size()) {
                diff -= other.digits[i];
            }
            
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            result.digits.push_back(diff);
        }
        
        result.removeLeadingZeros();
        return result;
    }
    
    BigInt operator+(const BigInt& other) const {
        // 同号：绝对值相加
        if (isNegative == other.isNegative) {
            BigInt result = absAdd(other);
            result.isNegative = isNegative;
            return result;
        }
        
        // 异号：绝对值相减
        if (absLess(other)) {
            BigInt result = other.absSub(*this);
            result.isNegative = other.isNegative;
            return result;
        } else {
            BigInt result = absSub(other);
            result.isNegative = isNegative;
            return result;
        }
    }
    
    // 优化的输出函数
    void fastPrint() const {
        if (isNegative && !(digits.size() == 1 && digits[0] == 0)) {
            FastIO::write('-');
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            FastIO::write('0' + digits[i]);
        }
    }
    
    // 传统输出函数（备用）
    void print() const {
        if (isNegative && !(digits.size() == 1 && digits[0] == 0)) {
            cout << '-';
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            cout << digits[i];
        }
    }
};

// 支持高精度数的线段树
class BigIntSegmentTree {
private:
    vector<BigInt> tree;
    int n;
    
    void build(vector<BigInt>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    void update(int node, int start, int end, int idx, const BigInt& val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    BigInt query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return BigInt(0LL);
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        BigInt leftSum = query(2*node, start, mid, l, r);
        BigInt rightSum = query(2*node+1, mid+1, end, l, r);
        return leftSum + rightSum;
    }
    
public:
    BigIntSegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
        vector<BigInt> arr(n, BigInt(0LL));
        build(arr, 1, 0, n-1);
    }
    
    // 单点修改
    void update(int idx, const BigInt& val) {
        update(1, 0, n-1, idx, val);
    }
    
    // 区间求和
    BigInt query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};

int main() {
    // IO优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 创建一个大小为2的线段树，用来存储两个数
    BigIntSegmentTree segTree(2);
    
    // 优化的输入方式
    string input1, input2;
    
    // 方法1：使用快速IO
    FastIO::read(input1);
    FastIO::read(input2);
    
    // 方法2：使用优化的cin（备选）
    // cin >> input1 >> input2;
    
    BigInt num1(input1);
    BigInt num2(input2);
    
    // 单点修改：将第一个数存储在位置0
    segTree.update(0, num1);
    
    // 单点修改：将第二个数存储在位置1
    segTree.update(1, num2);
    
    // 区间求和：求[0,1]区间的和
    BigInt result = segTree.query(0, 1);
    
    // 优化的输出
    result.fastPrint();
    FastIO::write('\n');
    
    // 刷新输出缓冲区
    fflush(stdout);
    
    return 0;
}