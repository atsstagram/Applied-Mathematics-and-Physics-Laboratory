//数理工学実験テーマ２ //課題４ //予測子・修飾子法３
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double U0 = 1.0;     //u_0の値
    double alpha = 10.0; //αの値
    double beta = 1.0;   //βの値

    double deltaT = 0.1; //ステップ幅 0.296, 0.297あたりから発散？？ → 0.1, 0.2, 0.3 で確認

    double Un, preUn, pre2Un, pre3Un;
    double preFn, pre2Fn, pre3Fn;

    //printf("\n");
    printf("Δt=%lfのとき\n", deltaT);

    pre3Un = U0;
    pre2Un = (U0 - beta / alpha) * exp(-alpha * deltaT) + beta / alpha;    //解析解から得たu_1の値
    preUn = (U0 - beta / alpha) * exp(-alpha * deltaT * 2) + beta / alpha; //解析解から得たu_2の値

    printf("%lf %lf \n", 0.0, pre3Un);
    printf("%lf %lf \n", deltaT, pre2Un);
    printf("%lf %lf \n", deltaT * 2, preUn);

    for (int i = 3; i <= 10 / deltaT; i++)
    {
        pre3Fn = (-alpha * pre3Un + beta) * deltaT;
        pre2Fn = (-alpha * pre2Un + beta) * deltaT;
        preFn = (-alpha * preUn + beta) * deltaT;

        Un = preUn + deltaT / 144 * (211 * preFn - 92 * pre2Fn + 25 * pre3Fn); //予測子・修飾子法３

        pre3Un = pre2Un;
        pre2Un = preUn; //次の試行のための代入
        preUn = Un;

        printf("%lf %lf \n", deltaT * i, Un);
    }

    return 0;
}