//数理工学実験テーマ３ //問題３ //Visscherのスキーム
#include <stdio.h>
#include <math.h>

const double pi = 3.14159265358979; //円周率の定義

double Ric(double x) //R_1~R_Nの初期条件を求めるための関数定義
{
    double u0 = sqrt(2) / pow(pi, 0.25) * exp(-2 * pow(x - 5, 2));
    return u0;
}

int main(int argc, char **argv)
{
    int n, j;

    int L = 20; //幅

    double deltaT = 0.001; //時間の刻み幅
    double deltaX = 0.05;  //空間の刻み幅

    for (int t = 1; t <= 8; t++) //t=1,2,3,4,5,6,7,8の場合
    {
        int T = t / deltaT; //時間の刻み数
        int N = L / deltaX; //空間の刻み数=400

        double R[N + 2];     //R_jを格納する配列
        double postR[N + 2]; //一段階後のR_jを格納する配列
        double I[N + 2];     //I_jを格納する配列
        double postI[N + 2]; //一段階後のI_jを格納する配列

        double P[N + 2]; //確率密度P_jを格納する配列

        //R_1~Nの初期条件を求めるためのfor文
        for (j = 1; j <= N; j++)
        {
            R[j] = 0.5 * (Ric((j - 1) * deltaX - L / 2) + Ric(j * deltaX - L / 2));
        }
        //Rの境界条件(t=0)
        R[0] = R[N];
        R[N + 1] = R[1];

        //I_1~Nの初期条件を求めるためのfor文
        for (j = 1; j <= N; j++)
        {
            I[j] = -deltaT * (-0.5 * (R[j - 1] - 2 * R[j] + R[j + 1]) / pow(deltaX, 2) + 0.5 * pow((j - 0.5) * deltaX - L / 2, 2) * R[j]);
        }
        //Iの境界条件(t=0)
        I[0] = I[N];
        I[N + 1] = I[1];

        for (n = 1; n <= T; n++)
        {
            //Rの時間発展
            for (j = 1; j <= N; j++)
            {
                postR[j] = R[j] + deltaT * (-0.5 * (I[j - 1] - 2 * I[j] + I[j + 1]) / pow(deltaX, 2) + 0.5 * pow((j - 0.5) * deltaX - L / 2, 2) * I[j]);
            }
            //Rの境界条件
            postR[0] = postR[N];
            postR[N + 1] = postR[1];

            //Iの時間発展
            for (j = 1; j <= N; j++)
            {
                postI[j] = I[j] - deltaT * (-0.5 * (postR[j - 1] - 2 * postR[j] + postR[j + 1]) / pow(deltaX, 2) + 0.5 * pow((j - 0.5) * deltaX - L / 2, 2) * postR[j]);
            }
            //Iの境界条件
            postI[0] = postI[N];
            postI[N + 1] = postI[1];

            //確率密度P_jの計算（毎回確率密度Pを計算する必要はないが、I[j]がI[j] = postI[j]と代入されてしまう前に計算しておくため）
            P[0] = pow(postR[0], 2) + postI[0] * I[0];
            for (j = 1; j <= N; j++)
            {
                P[j] = pow(postR[j], 2) + postI[j] * I[j];
            }
            P[N + 1] = pow(postR[N + 1], 2) + postI[N + 1] * I[N + 1];

            //R_j,I_jを次の段階で、一段前のR_j,I_jとして用いるためのfor文
            for (j = 1; j <= N; j++)
            {
                R[j] = postR[j];
                I[j] = postI[j];
            }
        }

        printf("t=%dの時(xの値　Pの値) \n", t);

        printf("%lf %lf\n", -10.0, P[0]); //x=-10のP
        for (j = 1; j <= N; j++)          //u1~u_Nを出力するためのfor文
        {
            printf("%lf %lf\n", (j - 0.5) * deltaX - L / 2, P[j]);
        }
        printf("%lf %lf\n", 10.0, P[N + 1]); //x=10のP
        printf("\n");
    }

    return 0;
}