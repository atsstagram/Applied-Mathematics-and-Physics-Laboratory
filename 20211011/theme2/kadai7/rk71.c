//数理工学実験テーマ２ //課題7-1 //ルンゲ・クッタ法
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    double deltaT = 0.01;                   //ステップ幅
    int N = 100 / deltaT;                   //ステップ数
    double X0, Y0, Z0;                      //x_0, y_0, z_0の値
    double Xn, preXn, Yn, preYn, Zn, preZn; //x_n, x_(n-1), y_n, y_(n-1), z_n, z_(n-1)
    double preFnx, preFny, preFnz;          //f_(n-1) : x', y', z'
    double F1x, F2x, F3x, F4x, F1y, F2y, F3y, F4y, F1z, F2z, F3z, F4z;

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
        F1x = 10 * (preYn - preXn);
        F2x = 10 * (preYn - preXn) + F1x * deltaT / 2;
        F3x = 10 * (preYn - preXn) + F2x * deltaT / 2;
        F4x = 10 * (preYn - preXn) + F3x * deltaT;

        F1y = 28 * preXn - preYn - preXn * preZn;
        F2y = 28 * preXn - preYn - preXn * preZn + F1y * deltaT / 2;
        F3y = 28 * preXn - preYn - preXn * preZn + F2y * deltaT / 2;
        F4y = 28 * preXn - preYn - preXn * preZn + F3y * deltaT;

        F1z = preXn * preYn - 8 / 3 * preZn;
        F2z = preXn * preYn - 8 / 3 * preZn + F1z * deltaT / 2;
        F3z = preXn * preYn - 8 / 3 * preZn + F2z * deltaT / 2;
        F4z = preXn * preYn - 8 / 3 * preZn + F3z * deltaT;

        //ルンゲ・クッタ法
        Xn = preXn + deltaT / 6 * (F1x + 2 * F2x + 2 * F3x + F4x);
        Yn = preYn + deltaT / 6 * (F1y + 2 * F2y + 2 * F3y + F4y);
        Zn = preZn + deltaT / 6 * (F1z + 2 * F2z + 2 * F3z + F4z);

        printf("%lf %lf %lf %lf\n", deltaT * k, Xn, Yn, Zn);

        //次の試行のための代入
        preXn = Xn;
        preYn = Yn;
        preZn = Zn;
    }

    return 0;
}