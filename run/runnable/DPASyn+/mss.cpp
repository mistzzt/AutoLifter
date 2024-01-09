#include <cstdio>
#include <sys/time.h>
#include <algorithm>
const int N=100000000;
int a[N + 10];
int n;
double difftime(timeval start, timeval end) {
    long long second_diff = end.tv_sec - start.tv_sec;
    if (second_diff < 0) second_diff += 24 * 3600;
    long long u_diff = end.tv_usec - start.tv_usec;
    return second_diff + u_diff * 1e-6;
}
struct result {
    int p1;
    int p2;
};
int main(){
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d",&a[i]);
    }
    timeval start;
    gettimeofday(&start, NULL);
    int x = a[1];
    result res = result{0, 0};
    for (int i = 1; i <= n; ++i) {
        x = a[i];
        res.p1 = (res.p2 + x < res.p1) ? res.p1 : res.p2 + x;
        res.p2 = (0 < res.p2 + x) ? res.p2 + x : 0;
    }
    timeval end;
    gettimeofday(&end, NULL);
    double cost = difftime(start, end);
    printf("%d\n", std::max(res.p1, res.p2));
    printf("%.10lf\n", cost);
}

// Just def f(a = [a1, ..., an]):
//   p1 = array()
//   p2 = array()
//   p1[0] = CI 0
//   p2[0] = CI 0
//   for i from 1 to n:
//     p1[i] = max((id(p2[i - 1]) + id(a[i])), id(p1[i - 1]))
//     p2[i] = max(zero(p2[i - 1]), (id(p2[i - 1]) + id(a[i])))
//   return max(p1[n], p2[n])