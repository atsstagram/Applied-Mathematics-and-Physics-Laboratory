//数理工学実験テーマ２ //課題３ //mix.cを改良したもの
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
    int i;
    int N;         //ステップ数
    double deltaT; //ステップ幅

    double U0 = exp(0); //u0の値

    double Un, preUn, prepreUn, preprepreUn; //それぞれ、u_n ~ u_(n-3)

    double UN[5] = {0, 1, 2, 3, 4}; //数値解法ごとのu_N

    double e = exp(1.0); //u(1)の解析解

    double E[5] = {0, 1, 2, 3, 4}; //数値解法ごとの、数値解と解析解との差の絶対値
    double preE[5] = {0, 1, 2, 3, 4};

    double Er[5] = {0, 1, 2, 3, 4}; //=E/preE

    for (int i = 1; i <= 10; i++) //i=1, 2, ... , 10
    {
        N = pow(2, i);    //ステップ数
        deltaT = 1.0 / N; //ステップ幅

        double U1 = exp(deltaT);     //u1の値
        double U2 = exp(2 * deltaT); //u2の値

        printf("\n");
        printf("i=%dのとき（FE, AB2, AB3, H, RKの順）", i);
        printf("\n");

        //前進オイラー法ここから
        preUn = U0;

        for (int k = 0; k < N; k++)
        {
            Un = preUn + preUn * deltaT; //前進オイラー法

            preUn = Un; //次の試行のための代入
        }
        UN[0] = Un; //UNにu_Nの値を代入
        //前進オイラー法ここまで

        //2次のアダムス・バッシュフォース法ここから
        prepreUn = U0;
        preUn = U1;

        for (int l = 0; l < N - 1; l++)
        {
            Un = preUn + deltaT / 2 * (3 * preUn - prepreUn); //2次のアダムス・バッシュフォース法

            prepreUn = preUn; //次の試行のための代入。順番に注意。
            preUn = Un;
        }
        UN[1] = Un; //UNにu_Nの値を代入
        //2次のアダムス・バッシュフォース法ここまで

        //3次のアダムス・バッシュフォース法ここから
        preprepreUn = U0;
        prepreUn = U1;
        preUn = U2;

        for (int m = 0; m < N - 2; m++)
        {
            Un = preUn + deltaT / 12 * (23 * preUn - 16 * prepreUn + 5 * preprepreUn); //3次のアダムス・バッシュフォース法

            preprepreUn = prepreUn; //次の試行のための代入。順番に注意。
            prepreUn = preUn;
            preUn = Un;
        }
        UN[2] = Un; //UNにu_Nの値を代入
        //3次のアダムス・バッシュフォース法ここまで

        //ホイン法（2次のルンゲ・クッタ法）ここから
        preUn = U0;
        double temporaryUn; //un*

        for (int p = 0; p < N; p++)
        {
            temporaryUn = preUn + preUn * deltaT;
            Un = preUn + deltaT / 2 * (preUn + temporaryUn); //ホイン法（2次のルンゲ・クッタ法）

            preUn = Un; //次の試行のための代入
        }
        UN[3] = Un; //UNにu_Nの値を代入
        //ホイン法（2次のルンゲ・クッタ法）ここまで

        //（4次の）ルンゲ・クッタ法ここから
        preUn = U0;
        double F1, F2, F3, F4; //4次のルンゲ・クッタ法で用いられているF1~F4

        for (int q = 0; q < N; q++)
        {
            F1 = preUn;
            F2 = preUn + F1 * deltaT / 2;
            F3 = preUn + F2 * deltaT / 2;
            F4 = preUn + F3 * deltaT;
            Un = preUn + deltaT / 6 * (F1 + 2 * F2 + 2 * F3 + F4); //（4次の）ルンゲ・クッタ法

            preUn = Un; //次の試行のための代入
        }
        UN[4] = Un; //UNにu_Nの値を代入
        //（4次の）ルンゲ・クッタ法ここまで

        for (int c = 0; c < 5; c++)
        {
            E[c] = fabs(UN[c] - e); //数値解と解析解との差の絶対値

            printf("uN=%.15lf\n", UN[c]);
            printf("E%d=%.15lf\n", c, E[c]);

            if (i >= 2)
            {
                Er[c] = E[c] / preE[c];
                printf("Er%c=%lf\n", c, Er[c]);
            }
            printf("\n");
            preE[c] = E[c]; //E(i)をE(i-1)として保存
        }
    }

    return 0;
}