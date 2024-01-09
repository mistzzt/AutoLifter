#include <cstdio>
#include <sys/time.h>
#include <omp.h>
const int N=100000000;
int w[N + 10];
int n, lim;
double difftime(timeval start, timeval end) {
    long long second_diff = end.tv_sec - start.tv_sec;
    if (second_diff < 0) second_diff += 24 * 3600;
    long long u_diff = end.tv_usec - start.tv_usec;
    return second_diff + u_diff * 1e-6;
}
struct result {
    int result1 = 0;
};
result dac(int l, int r)
{
    if (l == r) {
        int a = w[l];
        return result{a};
    } else {
        result lres, rres;
        int mid = l + r >> 1;
#pragma omp task shared(lres) if(r - l > lim)
        lres = dac(l, mid);
#pragma omp task shared(rres) if(r - l > lim)
        rres = dac(mid + 1, r);
#pragma omp taskwait
        return result{lres.result1 + rres.result1};
    }
}
int main(){
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d",&w[i]);
    }
    lim = n / 100;
    timeval start;
    gettimeofday(&start, NULL);
    result res;
    omp_set_num_threads(8);
#pragma omp parallel
    {
#pragma omp single
        {
            printf("thread num: %d\n", omp_get_num_threads());
            res = dac(1, n);
        }
    }
    timeval end;
    gettimeofday(&end, NULL);
    double cost = difftime(start, end);
    printf("%d\n", res.result1);
    printf("%.10lf\n", cost);
}


//  SUCCESS  Parsed /root/parsynt/inputs/AutoLifter/sum.minic.
//  SUCCESS  Equation system: 
// // --- Lifted function ---
// _s1 = { result1 = 0; }for(x in a){
//                         _s1 = {
//                           result1 = x + _s1.result1;
//                         }
//                         }
//                         return _s1;
// //--- Splitting predicate: (empty)
// //--- Join function ---
// join($L,$R) = { result1 = $R.result1 + $L.result1;
// }
// // Synthesized in (predicate : 0.10 s) + (join : 3.76 s)