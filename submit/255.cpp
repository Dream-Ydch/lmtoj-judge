#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;
const int MAXA = 55; // a_i ≤ 50，颜色范围1~50

// pre[i][c]：前i个位置中，颜色c的球的数量
int pre[MAXN][MAXA];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    // 初始化前缀和数组
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        // 先复制前一个位置的计数
        for (int c = 1; c <= 50; ++c) {
            pre[i][c] = pre[i-1][c];
        }
        // 当前位置的颜色计数+1
        pre[i][a]++;
    }

    // 处理每个查询
    while (t--) {
        int l, r;
        cin >> l >> r;
        ll ans = 0;

        // 步骤1：统计区间[l,r]内每个颜色的数量 cnt[c]
        int cnt[MAXA] = {0};
        for (int c = 1; c <= 50; ++c) {
            cnt[c] = pre[r][c] - pre[l-1][c];
        }

        // 步骤2：计算所有|c1 - c2| ≤ m 的球对数量
        for (int c1 = 1; c1 <= 50; ++c1) {
            if (cnt[c1] == 0) continue;
            // 找c1的匹配范围：[c1-m, c1+m]，且≥1、≤50
            int left = max(1, c1 - m);
            int right = min(50, c1 + m);
            for (int c2 = left; c2 <= c1; ++c2) { // 只算到c1，避免重复计数
                if (cnt[c2] == 0) continue;
                if (c1 == c2) {
                    // 同颜色：C(cnt,2) = cnt*(cnt-1)/2
                    ans += (ll)cnt[c1] * (cnt[c1] - 1) / 2;
                } else {
                    // 不同颜色：cnt[c1] * cnt[c2]
                    ans += (ll)cnt[c1] * cnt[c2];
                }
            }
        }
        
        cout << ans;
        if (t >= 2)
             cout << '\n';
    }

    return 0;
}