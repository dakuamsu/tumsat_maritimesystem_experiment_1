#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "SFMT-src-1.5.1/SFMT.h"

double f(double x){
    double a, b, c, d;
    a = 0;
    b = 6;
    c = 8;
    d = 1;
    double A, B, C, D;
    A = a + b + c + d;
    B = a * b + b * c + c * d + a * d + a * c +  b * d;
    C = a * b * c + b * c * d + a * c * d + a * b * d;
    D = a * b * c * d;
    return fabs(pow(x,4) - 15 * pow(x, 3) + 62 * pow(x, 2) - 48 * x);
}

double range(int a, int b){
    double max = 0;
    double min = 10;
    double r;
    for (r = a;r <= b;r += 0.01){
        if(f(r) > max){
            max = f(r);
        }
        if(f(r) < min){
            min = f(r);
        }
    }
    double ran = max -min;
    return ran;
}

double min(int a, int b){
    double low = 10;
    double r;
    for (r = a;r <= b;r += 0.01){
        if(f(r) < low){
            low = f(r);
        }
    }
    return low;
}

int main(void){
    sfmt_t sfmt;
    int j;
    int seed = time(NULL);
    sfmt_init_gen_rand(&sfmt, seed);
    double x, y, z;
    unsigned long int i, count;
    double ans;
    i = 0;
    int start = 0;
    int finish = 10;
    double ran = range(start, finish);
    unsigned long int before = 0;
    unsigned long int after = 10;
    double low = min(start, finish);
    printf("range = %f\n",ran);
    while (before != after){
        before = after;
            for(j = 0;j < 1000000;j ++){
                x = sfmt_genrand_real2(&sfmt) * 10;
                y = sfmt_genrand_real2(&sfmt) * ran + low;
                z = f(x);
                if(y <= z){
                    count += 1;
                }
            }
        i += 1;
        ans = (double)count / ((double)i * 1000000);
        ans *= ran;
        ans *= 10;
        printf("試行回数:%u,積分結果:%lf\n",i * 1000000,ans);
        after = ans * 10000 + 0.5;
    }
    printf("\n最終結果:%lf", ans);
}
