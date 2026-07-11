// 设置CPU时间限制（防止死循环）
#include <sys/resource.h>
struct rlimit rl;
rl.rlim_cur = 1;  // 1秒CPU时间
rl.rlim_max = 1;
setrlimit(RLIMIT_CPU, &rl);

// 设置内存限制
rl.rlim_cur = 256 * 1024 * 1024;  // 256MB
rl.rlim_max = 256 * 1024 * 1024;
setrlimit(RLIMIT_AS, &rl);