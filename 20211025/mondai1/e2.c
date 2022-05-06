//数理工学実験テーマ3 //問題１ //オイラー陽解法Neumann
#include <stdio.h>
#include <math.h>

const double pi = 3.14159265358979; //円周率の定義

double uic(double x) //u_1~u_Nの初期条件を求めるための関数定義
{
    double u0 = 1 / sqrt(2 * pi) * exp(-0.5 * pow(x - 5, 2));
    return u0;
}

int main(int argc, char **argv)
{
    int n, j;

    int L = 10; //幅

    double deltaT = 0.01;               //時間の刻み幅
    double deltaX = 0.5;                //空間の刻み幅
    double c = deltaT / pow(deltaX, 2); //cの定義

    for (int t = 1; t <= 5; t++) //t=1,2,3,4,5の場合（時間の刻み幅ではないことに注意）
    {

        int T = t / deltaT; //時間の刻み数
        int N = L / deltaX; //空間の刻み数=20

        double u[N + 2];    //u_jを格納する配列
        double preu[N + 2]; //一段階前ののu_jを格納する配列

        for (j = 1; j <= N; j++) //u_1~u_Nの初期条件を求めるためのfor文
        {
            preu[j] = 0.5 * (uic((j - 1) * deltaX) + uic(j * deltaX));
        }

        //境界条件
        preu[0] = preu[1];
        preu[N + 1] = preu[N];

        for (n = 1; n <= T; n++)
        {
            for (j = 1; j <= N; j++)
            {
                u[j] = preu[j] + c * (preu[j - 1] - 2 * preu[j] + preu[j + 1]); //オイラー陽解法
            }
            for (j = 1; j <= N; j++) //u_jを次の段階で、一段前のu_jとして用いるためのfor文
            {
                preu[j] = u[j];
            }

            //次の段階のための境界条件
            preu[0] = preu[1];
            preu[N + 1] = preu[N];
        }

        printf("t=%dの時(xの値　uの値) \n", t);

        printf("%lf %lf\n", 0.0, u[1]); //x=0のu:u_0
        for (j = 1; j <= N; j++)        //u1~u_Nを出力するためのfor文
        {
            printf("%lf %lf\n", (j - 0.5) * deltaX, u[j]);
        }
        printf("%lf %lf\n", 10.0, u[N]); //x=10のu;u_{N+1}
        printf("\n");
    }

    return 0;
}