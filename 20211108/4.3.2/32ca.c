//数理工学実験テーマ4 //4.3節の課題 //2(c) //(a)のやり方
#include <stdio.h>
#include <math.h>

double func(double x)
{
    return (exp(-x) - 1) / sqrt(x);
}

int main(int argc, char **argv)
{
    double a = 0;   //左端
    double b = 1.0; //右端

    int N, i; //分割数

    int j; //xの添字
    double x[1025];

    int m;                                             //yとωの添字
    double y2[3] = {0, -1.0 / sqrt(3), 1.0 / sqrt(3)}; //M=2のときのy、添字mに対応
    double omega2[3] = {0, 1, 1};                      //M=2のときのω
    double y3[4] = {0, -sqrt(0.6), 0, sqrt(0.6)};      //M=3のときのy
    double omega3[4] = {0, 5.0 / 9, 8.0 / 9, 5.0 / 9}; //M=3のときのω

    double integral2[11] = {0}; //複合M(=2)次Gauss型積分公式の値を格納する配列
    double integral3[11] = {0}; //複合M(=3)次Gauss型積分公式の値を格納する配列

    double I = 1.49364826562; //与えられた（解析的に求めた?）積分の値

    for (i = 0; i <= 10; i++)
    {
        N = pow(2, i);           //分割数
        for (j = 0; j <= N; j++) //分点x_iの計算
        {
            x[j] = a + j * (b - a) / N;
        }

        //複合M(=2)次Gauss型積分公式
        for (j = 0; j <= N - 1; j++)
        {
            for (m = 1; m <= 2; m++)
            {
                integral2[i] = integral2[i] + omega2[m] * func((y2[m] + 1) * (x[j + 1] - x[j]) / 2 + x[j]) * (x[j + 1] - x[j]) / 2;
            }
        }

        //複合M(=3)次Gauss型積分公式
        for (j = 0; j <= N - 1; j++)
        {
            for (m = 1; m <= 3; m++)
            {
                integral3[i] = integral3[i] + omega3[m] * func((y3[m] + 1) * (x[j + 1] - x[j]) / 2 + x[j]) * (x[j + 1] - x[j]) / 2;
            }
        }
    }

    printf("複合M(=2)次Gauss型積分公式\n");
    printf("iの値　積分値\n");
    for (i = 0; i <= 10; i++) //数値積分の値を出力
    {
        printf("%d %lf\n", i, 2 + integral2[i]);
    }
    printf("\n");
    printf("iの値　|E_n|の値\n");
    for (i = 0; i <= 10; i++) //解析値との誤差を出力
    {
        printf("%d %lf\n", i, fabs(2 + integral2[i] - I));
    }
    printf("\n\n");

    printf("複合M(=3)次Gauss型積分公式\n");
    printf("iの値　積分値\n");
    for (i = 0; i <= 10; i++) //数値積分の値を出力
    {
        printf("%d %lf\n", i, 2 + integral3[i]);
    }
    printf("\n");
    printf("iの値　|E_n|の値\n");
    for (i = 0; i <= 10; i++) //解析値との誤差を出力
    {
        printf("%d %lf\n", i, fabs(2 + integral3[i] - I));
    }
    printf("\n");

    return 0;
}