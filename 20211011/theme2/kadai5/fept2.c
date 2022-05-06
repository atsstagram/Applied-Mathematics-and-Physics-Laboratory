//数理工学実験テーマ２ //課題5
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double deltaT = 0.1;      //ステップ幅 → 0.1, 0.01, 0.001
    int N = 10 / deltaT;      //ステップ数
    double U0, U1;            //u_0, u_1の値
    double Un, preUn, pre2Un; //それぞれ、u_n, u_(n-1),u_(n-2)

    U0 = 1.0;
    U1 = 0.5 * exp(-2 * deltaT) + 0.5; //解析解から求めたu_1の値

    printf("tの値 unの値\n");
    printf("%lf %lf\n", 0.0, U0);
    printf("%lf %lf\n", deltaT, U1);

    pre2Un = U0;
    preUn = U1;

    for (int k = 2; k <= N; k++)
    {
        Un = pre2Un + 2 * (-2 * preUn + 1) * deltaT; //式(2.33)

        printf("%lf %lf\n", deltaT * k, Un);

        pre2Un = preUn; //次の試行のための代入
        preUn = Un;     //次の試行のための代入
    }

    return 0;
}