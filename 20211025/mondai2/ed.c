//数理工学実験テーマ3 //問題２ //Fisher方程式 オイラー陽解法Dirichlet
#include <stdio.h>
#include <math.h>

double uic(double b, double x) //u_1~u_Nの初期条件を求めるための関数定義
{
    double u0 = 1 / pow(1 + exp(b * x - 5), 2);
    return u0;
}

int main(int argc, char **argv)
{
    int n, j;

    int L = 200; //幅

    //境界条件
    double ul = 1.0;
    double ur = 0.0;

    double deltaT = 0.001; //時間の刻み幅
    double deltaX = 0.05;  //空間の刻み幅

    for (double b = 0.25; b <= 1.0; b = b * 2)
    {
        for (int t = 10; t <= 40; t = t + 10) //t=10,20,30,40の場合
        {
            int T = t / deltaT; //時間の刻み数
            int N = L / deltaX; //空間の刻み数=4000

            double u[N + 2];     //u_jを格納する配列
            double postu[N + 2]; //一段階後のu_jを格納する配列

            u[0] = ul;
            u[N + 1] = ur;
            for (j = 1; j <= N; j++) //u_1~u_Nの初期条件を求めるためのfor文
            {
                u[j] = 0.5 * (uic(b, (j - 1) * deltaX) + uic(b, j * deltaX));
            }

            /*
            //u_1~u_Nの初期条件の確認
            printf("b=%lf t=0の時(xの値　uの値) \n", b);

            printf("%lf %lf\n", 0.0, ul);
            for (j = 1; j <= N; j++) //u1~u_Nの初期条件を出力するためのfor文
            {
                printf("%lf %lf\n", (j - 0.5) * deltaX, u[j]);
            }
            printf("%lf %lf\n", 200.0, ur);
            printf("\n");
            */

            for (n = 1; n <= T; n++)
            {
                for (j = 1; j <= N; j++)
                {
                    postu[j] = u[j] + deltaT * (u[j] * (1 - u[j]) + (u[j - 1] - 2 * u[j] + u[j + 1]) / pow(deltaX, 2)); //オイラー陽解法
                }
                for (j = 1; j <= N; j++) //u_jを次の段階で、一段前のu_jとして用いるためのfor文
                {
                    u[j] = postu[j];
                }
            }

            printf("b=%lf t=%dの時(xの値　uの値) \n", b, t);

            printf("%lf %lf\n", 0.0, ul); //x=0のu:u_0
            for (j = 1; j <= N; j++)      //u1~u_Nを出力するためのfor文
            {
                printf("%lf %lf\n", (j - 0.5) * deltaX, u[j]);
            }
            printf("%lf %lf\n", 200.0, ur); //x=200のu:u_{N+1}
            printf("\n");
        }
    }

    return 0;
}