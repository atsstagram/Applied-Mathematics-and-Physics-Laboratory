//数理工学実験テーマ２ //課題6
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double deltaT = 0.01;
    int N = 10 / deltaT;  //ステップ数
    double U0, U1;        //u_0の値
    double Un, preUn;     //それぞれ、u_n, u_(n-1)
    double preFn;         //f_(n-1) : u'
    double duds;          //du/ds

    U0 = 0.5; //u_0の値→ 0.5, 1.0, 1.5

    printf("tの値 unの値\n");
    printf("%lf %lf\n", 0.0, U0);

    preUn = U0;

    for (int k = 1; k <= N; k++)
    {
        preFn = pow(preUn, 2.0) - preUn;
        duds = preFn / sqrt(1.0 + pow(preFn, 2.0));

        Un = preUn + duds * deltaT; //オイラー法

        printf("%lf %lf\n", deltaT * k, Un);

        preUn = Un; //次の試行のための代入
    }

    return 0;
}