//数理工学実験テーマ4 //4.2節の課題 //2&3(a)
#include <stdio.h>
#include <math.h>

double func(double x)
{
    return 1.0 / x;
}

int main(int argc, char **argv)
{
    double a = 1.0; //左端
    double b = 2.0; //右端

    int n, i; //分割数
    double h; //分点の間隔

    int m; //xの添字
    double x[1025];
    double fx[1025];

    double integralC[11] = {0}; //複合中点公式による積分の値を格納する配列
    double integralT[11] = {0}; //複合台形公式による...
    double integralS[11] = {0}; //複合Simpson公式による...

    double I = log(2.0); //解析的に求めた積分の値

    double EC[11] = {0}; //複合中点公式による積分の値と解析解との差を格納する配列
    double ET[11] = {0}; //複合台形公式による...
    double ES[11] = {0}; //複合Simpson公式による...

    for (i = 0; i <= 10; i++)
    {
        n = pow(2, i);
        h = (b - a) / n;         //刻み幅
        for (m = 0; m <= n; m++) //分点x_iの計算
        {
            x[m] = a + m * h;
            //printf("%d %lf\n", i, x[i]);
        }
        for (m = 0; m <= n; m++) //f(x)の計算
        {
            fx[m] = func(x[m]);
            //printf("%d %lf\n", i, fx[i]);
        }

        //複合中点公式
        for (m = 0; m <= n - 1; m++)
        {
            integralC[i] = integralC[i] + h * fx[(m + m + 1) / 2];
        }
        EC[i] = integralC[i] - I; //誤差の計算

        //複合台形公式
        integralT[i] = h / 2.0 * (fx[0] + fx[n]);
        for (m = 1; m <= n - 1; m++)
        {
            integralT[i] = integralT[i] + h * fx[m];
        }
        ET[i] = integralT[i] - I; //誤差の計算

        //複合Simpson公式
        integralS[i] = h / 6.0 * (fx[0] + fx[n]);
        for (m = 1; m <= n - 1; m++)
        {
            integralS[i] = integralS[i] + h / 3.0 * fx[m];
        }
        for (m = 0; m <= n - 1; m++)
        {
            integralS[i] = integralS[i] + 2 * h / 3.0 * fx[(m + m + 1) / 2];
        }
        ES[i] = integralS[i] - I; //誤差の計算
    }

    printf("複合中点公式の場合\n");
    printf("iの値　積分値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, integralC[i]);
    }
    printf("iの値　E_nの値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, EC[i]);
    }
    printf("\n");

    printf("複合台形公式の場合\n");
    printf("iの値　積分値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, integralT[i]);
    }
    printf("iの値　E_nの値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, ET[i]);
    }
    printf("\n");
    printf("\n");

    printf("複合Simpson公式の場合\n");
    printf("iの値　積分値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, integralS[i]);
    }
    printf("iの値　E_nの値\n");
    for (i = 0; i <= 10; i++)
    {
        printf("%d %lf\n", i, ES[i]);
    }
    printf("\n");
    printf("\n");

    return 0;
}