#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "SFMT-src-1.5.1/SFMT.h"

/* 与式の関数 */
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

/* yの範囲を求めるための関数 */
double range(int a, int b){
    double max = 0;  /* 最大値を保持する変数の初期化 */
    double min = 0;
    double i;
    for (i = a; i <= b; i += 0.00001){
        if(f(i) > max){
            max = f(i);  /* 最大値の保持 */
        }
    }
    double ran = max -min;
    return ran;
}

int main(void){
    sfmt_t sfmt;  /* 構造体の保持 */
    int seed = time(NULL);  /* 時刻情報を取得 */
    sfmt_init_gen_rand(&sfmt, seed);  /* 時刻情報をシード値とする */
    double x, y, z;
    unsigned long int hit, count;
    double ans;
    count = hit = 0;  /* 内側にある回数と試行回数を保持する変数の初期化 */
    double ran = range(0, 10);  /* yの範囲を求める関数を呼び出し */
    double difference = 10;  /* 相対誤差を求める変数の初期化 */
    double temp = 10;  /* S(n-10000)の解を保持する変数の初期化 */
    while (difference >= 0.00001){
            for(int j = 0;j < 1000;j ++){
                x = sfmt_genrand_real2(&sfmt) * 10;
                y = sfmt_genrand_real2(&sfmt) * ran;
                z = f(x);
                if(y <= z){
                    hit += 1;  /* yの値が与式にxを代入をした値以下であるとき内側にあるとする */
                }
                count += 1;
            }
        ans = (double)hit / ((double)count) * ran * 10;  /* 面積の比率を求め面積をかける */
        difference = fabs(temp - ans);  /* 相対誤差を求める */
        temp = ans;  /* 現在の解を保持 */
    }
    printf("x^4 -15 * x^3 + 62 * x^2 + 48 * xを[0,10]で積分した解は%lf", ans);
    return 0;
}
