//数理工学実験テーマ２ //課題7-1 //前進オイラー法
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double deltaT = 0.01;                   //ステップ幅
    int N = 100 / deltaT;                   //ステップ数
    double X0, Y0, Z0;                      //x_0, y_0, z_0の値
    double Xn, preXn, Yn, preYn, Zn, preZn; //x_n, x_(n-1), y_n, y_(n-1), z_n, z_(n-1)
    double preFnx, preFny, preFnz;          //f_(n-1) : x', y', z'

    X0 = 1.0;
    Y0 = 0;
    Z0 = 0;

    printf("t xn yn zn\n");
    printf("%lf %lf %lf %lf\n", 0.0, X0, Y0, Z0);

    preXn = X0;
    preYn = Y0;
    preZn = Z0;

    for (int k = 1; k <= N; k++)
    {
        preFnx = 10 * (preYn - preXn);
        preFny = 28 * preXn - preYn - preXn * preZn;
        preFnz = preXn * preYn - 8 / 3 * preZn;

        //前進オイラー法
        Xn = preXn + preFnx * deltaT;
        Yn = preYn + preFny * deltaT;
        Zn = preZn + preFnz * deltaT;

        printf("%lf %lf %lf %lf\n", deltaT * k, Xn, Yn, Zn);

        //次の試行のための代入
        preXn = Xn;
        preYn = Yn;
        preZn = Zn;
    }

    return 0;
}