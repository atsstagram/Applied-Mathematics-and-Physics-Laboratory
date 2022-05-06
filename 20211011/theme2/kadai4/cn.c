//数理工学実験テーマ２ //課題４ //クランク・ニコルソン法
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double U0 = 1.0;     //u_0の値
    double alpha = 10.0; //αの値
    double beta = 1.0;   //βの値

    double deltaT; //ステップ幅

    double Un, preUn; //それぞれ、u_n, u_(n-1)

    for (int i = 0; i < 3; i++) //i = 0.01, 0.1, 1.0
    {
        deltaT = 0.01 * pow(10, i);

        printf("\n");
        printf("Δt=%lfのとき\n", deltaT);

        preUn = U0;
        printf("%lf %lf \n", 0.0, preUn);

        for (int j = 1; j <= 10 / deltaT; j++)
        {
            Un = (2 - alpha * deltaT) / (2 + alpha * deltaT) * preUn + 2 * beta * deltaT / (2 + alpha * deltaT); //クランク・ニコルソン法

            preUn = Un; //次の試行のための代入

            printf("%lf %lf \n", deltaT * j, Un);
        }
    }
    return 0;
}