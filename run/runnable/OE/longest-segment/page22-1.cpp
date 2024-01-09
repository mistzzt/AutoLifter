#include <cassert>
#include <cstdio>
#include <sys/time.h>
double difftime(timeval start, timeval end) {
    long long second_diff = end.tv_sec - start.tv_sec;
    if (second_diff < 0) second_diff += 24 * 3600;
    long long u_diff = end.tv_usec - start.tv_usec;
    return second_diff + u_diff * 1e-6;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a < b ? b : a;
}
const int N=10000000;
int n, w[N + 10], rpos[N + 10];
struct result {
    int x0,x1,x2;
}info[N + 10];

result mergeRes(int a, const result& lres, const result& rres, int lsize, int rsize) {
    if (lsize) {
        if (rsize) {
            return (result){((((((lres.x1)+(rres.x1))+(1))<=((a)+(rres.x2)))&&((rres.x0)<(lres.x0)))&&((((lres.x1)+(rres.x1))+(1))<=((a)+(lres.x2))))?(lres.x0):((((((lres.x1)+(rres.x1))+(1))<=((a)+(lres.x2)))&&((((lres.x1)+(rres.x1))+(1))<=((a)+(rres.x2))))?(rres.x0):(((lres.x1)+(rres.x1))+(1))),((lres.x1)+(rres.x1))+(1),((lres.x2)<=(rres.x2))?(lres.x2):(rres.x2)};
        } else {
            return (result){(((lres.x1)+(1))<=((a)+(lres.x2)))?(lres.x0):((lres.x1)+(1)),(lres.x1)+(1),lres.x2};
        }
    } else if (rsize) {
        return (result){(((rres.x0)+(1))<=((a)+(rres.x2)))?(rres.x0):((rres.x0)+(1)),(rres.x1)+(1),rres.x2};
    } else {
        return (result){((1)<=(a))?(0):(1),1,a};
    }
}

int lsp() {
    int num = 0;
    for (int i = 1; i <= n; ++i) {
        result rres = (result){0,0,1000000000};
        while (num > 0 && w[rpos[num]] <= w[i]) {
            result lres = info[num]; int a = w[rpos[num]];
            rres = mergeRes(a, lres, rres, rpos[num] - rpos[num - 1] - 1, i - rpos[num] - 1);
            --num;
        }
        num++; rpos[num] = i; info[num] = rres;
    }
    result rres = (result){0,0,1000000000};
    for (int i = num; i; --i) {
        result lres = info[i]; int a = w[rpos[i]];
        rres = mergeRes(a, lres, rres, rpos[i] - rpos[i - 1] - 1, n - rpos[i]);
    }
    return rres.x0;
}

int main() {
    scanf("%d\n",&n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    timeval start;
    gettimeofday(&start, NULL);
    result res;
    int myres = lsp();
    timeval end;
    gettimeofday(&end, NULL);
    double cost = difftime(start, end);
    printf("%d\n", myres);
    printf("%.10lf\n", cost);
}