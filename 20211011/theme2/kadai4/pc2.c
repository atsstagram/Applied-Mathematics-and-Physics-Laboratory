//数理工学実験テーマ２ //課題４ //予測子・修飾子法２
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double U0 = 1.0;     //u_0の値
    double alpha = 10.0; //αの値
    double beta = 1.0;   //βの値

    double deltaT = 0.1; //ステップ幅 0.36, 0.37あたりから発散？？ → 0.1, 0.3, 0.4 で確認

    double Un, preUn, pre2Un;
    double preFn, pre2Fn;

    //printf("\n");
    printf("Δt=%lfのとき\n", deltaT);

    pre2Un = U0;
    preUn = (U0 - beta / alpha) * exp(-alpha * deltaT) + beta / alpha; //解析解から得たu_1の値

    printf("%lf %lf \n", 0.0, pre2Un);
    printf("%lf %lf \n", deltaT, preUn);

    for (int i = 2; i <= 10 / deltaT; i++)
    {
        pre2Fn = (-alpha * pre2Un + beta) * deltaT;
        preFn = (-alpha * preUn + beta) * deltaT;

        Un = preUn + deltaT / 4 * (5 * preFn - pre2Fn); //予測子・修飾子法２

        pre2Un = preUn; //次の試行のための代入
        preUn = Un;

        printf("%lf %lf \n", deltaT * i, Un);
    }

    return 0;
}