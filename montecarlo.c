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

int main(void){
    sfmt_t sfmt;
    int i,j;
    int max = 20000000;
    int seed = time(NULL);
    sfmt_init_gen_rand(&sfmt, seed);
    double x, y, z;
    unsigned long int count;
    double ans;
    int ja = 0;
    int jb = 10;
    while (ja != jb){
        ja = jb;
        for(i = 0;i < max;i++){
            for(j = 0;j < 1000;j ++){
                x = sfmt_genrand_real2(&sfmt) * 10;
                y = sfmt_genrand_real2(&sfmt) * 720;
                z = f(x);
                if(y <= z){
                    count += 1;
                }
            }
        }
        ans = (double)count / ((double)max * 1000);
        ans *= 720;
        ans *= 10;
        printf("試行回数:%d,積分結果:%lf\n",max * 100,ans);
        max += 1000000;
        jb = ans * 1000;
        count = 0;
        
    }
    printf("\n最終結果:%lf", ans);
}
