#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1e6 + 5;
const int MAX_COLOR = 51; // a_i ≤ 50（核心约束，不可改）

// 前缀和数组：优化为「行优先」，减少缓存失效，避免越界
int prefix[MAX_COLOR][MAXN]; // 51 * 1e5 = 5.1MB，完全在内存限制内
int a[MAXN];

int main() {
    // 强制关闭同步，避免输入输出超时导致的隐性崩溃
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;


    // 读取数组 + 构建前缀和（严格控制边界，避免数组越界）
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        // 复制上一行（i-1）的计数，循环替代 memcpy，避免越界
        for (int c = 1; c < MAX_COLOR; ++c) {
            prefix[c][i] = prefix[c][i - 1];
        }
        // 确保 a[i] 在 1~50 范围内（避免非法访问）
        if (a[i] >= 1 && a[i] < MAX_COLOR) {
            prefix[a[i]][i]++;
        }
    }

    // 处理查询（极简逻辑，避免冗余计算）
    while (t--) {
        int l, r;
        cin >> l >> r;
        // 严格检查区间合法性（避免 l > r 或越界）
        if (l < 1) l = 1;
        if (r > n) r = n;
        int len = r - l + 1;
        if (len < 2) { // 无成对球，直接输出0，跳过所有计算
            cout << "0\n";
            continue;
        }

        // 计算总对数（用 long long 避免溢出）
        long long total = 1LL * len * (len - 1) / 2;
        long long bad = 0;

        // 统计区间内各颜色数量（仅一次循环）
        int cnt[MAX_COLOR] = {0};
        for (int c = 1; c <MAX_COLOR; ++c) {
            cnt[c] = prefix[c][r] - prefix[c][l - 1];
        }

        // 计算颜色差 > m 的球对（仅 50*50=2500 次循环，无压力）
        for (int c1 = 1; c1 < MAX_COLOR; ++c1) {
            if (cnt[c1] == 0) continue;
            for (int c2 = 1; c2 <= c1 - m - 1; ++c2) {
                if (cnt[c2] == 0) continue;
                bad += 1LL * cnt[c1] * cnt[c2];
            }
        }

        cout << (total - bad) << "\n";
    }

    return 0;
}