//数理工学実験テーマ２ //課題４ //ホイン法
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double U0 = 1.0;     //u_0の値
    double alpha = 10.0; //αの値
    double beta = 1.0;   //βの値

    double deltaT = 0.1; //ステップ幅 0.44, 0.45あたりから発散？？ → 0.1, 0.4, 0.5 で確認

    double Un, preUn;
    double Fn, preFn;

    //printf("\n");
    printf("Δt=%lfのとき\n", deltaT);

    preUn = U0;

    printf("%lf %lf \n", 0.0, preUn);

    for (int i = 1; i <= 10 / deltaT; i++)
    {
        preFn = (-alpha * preUn + beta) * deltaT;

        Un = preUn + preFn * deltaT;            //u_n^*
        Fn = (-alpha * Un + beta) * deltaT;     //f(t_n, u_n^*)
        Un = preUn + deltaT / 2 * (preFn + Fn); //ホイン法

        preUn = Un; //次の試行のための代入

        printf("%lf %lf \n", deltaT * i, Un);
    }

    return 0;
}