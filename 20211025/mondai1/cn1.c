//数理工学実験テーマ3 //問題１ //クランク・ニコルソン法Dirichlet
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

    //境界条件
    double ul = 0.0;
    double ur = 0.0;

    double deltaT = 0.01;               //時間の刻み幅
    double deltaX = 0.05;               //空間の刻み幅
    double c = deltaT / pow(deltaX, 2); //cの定義

    for (int t = 1; t <= 5; t++) //t=1,2,3,4,5の場合（時間の刻み幅ではないことに注意）
    {

        int T = t / deltaT; //時間の刻み数
        int N = L / deltaX; //空間の刻み数=200

        double u[N + 2];     //u_jを格納する配列
        double postu[N + 2]; //一段階後ののu_jを格納する配列

        u[0] = ul;
        u[N + 1] = ur;
        for (j = 1; j <= N; j++) //u_1~u_Nの初期条件を求めるためのfor文
        {
            u[j] = 0.5 * (uic((j - 1) * deltaX) + uic(j * deltaX));
        }

        //LU分解のための配列（u, postuの配列と同様にアドレスが一致するようにしている）
        double a[N + 1], b[N]; //この場合c（行列の要素）は、b=cなのでbにまとめる。
        double alpha[N + 1], beta[N];
        double x[N + 1], y[N + 1], z[N + 1]; //xは、postuに対応
        a[0] = 0;
        b[0] = 0;
        alpha[0] = 0;
        beta[0] = 0;
        x[0] = 0;
        y[0] = 0;
        z[0] = 0;

        for (n = 1; n <= T; n++)
        {
            for (j = 1; j <= N - 1; j++) //a_1~N-1, b_1~N-1に（Dirichlet境界条件の場合の）値を代入
            {
                a[j] = 1.0 + c;
                b[j] = -c / 2;
            }
            a[N] = 1.0 + c;

            for (j = 1; j <= N - 1; j++) //α_1~N-1, β_1~N-1に（Dirichlet境界条件の場合の）値を代入
            {
                alpha[j] = a[j] - b[j - 1] * beta[j - 1]; //b_0(c_0)=β_0=0と代入済み
                beta[j] = b[j] / alpha[j];
            }
            alpha[N] = a[N] - b[N - 1] * beta[N - 1]; //α_Nの値

            z[1] = (1 - c) * u[1] + c * ul + c / 2 * u[2]; //z_1の値
            for (j = 2; j <= N - 1; j++)                   //z_2~N-1に（Dirichlet境界条件の場合の）値を代入
            {
                z[j] = (1 - c) * u[j] + c / 2 * u[j - 1] + c / 2 * u[j + 1];
            }
            z[N] = (1 - c) * u[N] + c * ur + c / 2 * u[N - 1]; //z_Nの値

            for (j = 1; j <= N; j++) //y_1~Nの値 //b_0(c_0)=0と代入済み
            {
                y[j] = (z[j] - b[j - 1] * y[j - 1]) / alpha[j];
            }

            x[N] = y[N];
            for (j = N - 1; j >= 1; j--) //x_N-1~1（降順）の値
            {
                x[j] = y[j] - beta[j] * x[j + 1];
            }

            for (j = 1; j <= N; j++) //postuにxの値を格納
            {
                postu[j] = x[j];
            }

            for (j = 1; j <= N; j++) //postuをuに格納
            {
                u[j] = postu[j];
            }
        }

        printf("t=%dの時(xの値　uの値) \n", t);

        printf("%lf %lf\n", 0.0, ul); //x=0のu:u_0
        for (j = 1; j <= N; j++)      //u1~u_Nを出力するためのfor文
        {
            printf("%lf %lf\n", (j - 0.5) * deltaX, u[j]);
        }
        printf("%lf %lf\n", 10.0, ur); //x=10のu:u_{N+1}
        printf("\n");
    }

    return 0;
}