//数理工学実験テーマ6 //課題12
#include <stdio.h>
#include <math.h>

#define N 1000 //データファイルの行数

int main(int argc, char **argv)
{
    double x[1][N], y[2][N];

    //ファイル読み込みここから
    FILE *fp;
    fp = fopen("/Users/ats/Desktop/数理工学実験/20211213/kadai12/mmse_kadai5.txt", "r");
    if (fp == NULL)
    {
        printf("file not open...\n");
        return -1;
    }
    int e = 0;
    while (fscanf(fp, "%lf,%lf,%lf", &x[0][e], &y[0][e], &y[1][e]) != EOF)
    {
        e++;
    }
    fclose(fp);
    //ファイル読み込みここまで

    int p = 2; // θ,φの行数
    int q = 1; // yの列数
    double phi[p][p];
    double phiQ1[p][p], phiphi[p][p];
    double invphiphi[p][p]; // phiphiの逆行列を格納する配列
    double temp;            //逆行列を求めるのに一時的に用いる変数
    double phiQ2[p][p], phiy[p][q];

    double V[1][2][2] = {{{100.0, 0}, {0, 1.0}}}; //誤差の共分散行列
    double Q[1][2][2];                            //重み行列（Vの逆行列）を格納する配列

    double thetaN[2][p][q]; //式(6.5)と(6.17)の二つ分

    double estVN[2][p][p]; //推定誤差共分散行列
    double phitheta[2][p][q];

    //式(6.5)
    printf("式(6.5)\n");
    // phiphiの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = 0;
        }
    }
    // phiyの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            phiy[k][l] = 0;
        }
    }

    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                if (l == 0)
                {
                    phi[k][l] = 1.0;
                }
                else if (l == 1)
                {
                    phi[k][l] = pow(x[0][e], k + 1);
                }
            }
        }

        // phiphiの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    phiphi[k][l] = phiphi[k][l] + phi[m][k] * phi[m][l];
                }
            }
        }

        // phiyの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    phiy[k][l] = phiy[k][l] + phi[k][m] * y[m][e];
                }
            }
        }
    }

    // phiphiの逆行列の計算
    //  単位行列の生成
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            if (k == l)
            {
                invphiphi[k][l] = 1.0;
            }
            else
            {
                invphiphi[k][l] = 0;
            }
        }
    }
    // 掃き出し法
    for (int k = 0; k < p; k++)
    {
        temp = 1 / phiphi[k][k];
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = phiphi[k][l] * temp;
            invphiphi[k][l] = invphiphi[k][l] * temp;
        }
        for (int l = 0; l < p; l++)
        {
            if (k != l)
            {
                temp = phiphi[l][k];
                for (int m = 0; m < p; m++)
                {
                    phiphi[l][m] = phiphi[l][m] - phiphi[k][m] * temp;
                    invphiphi[l][m] = invphiphi[l][m] - invphiphi[k][m] * temp;
                }
            }
        }
    }

    // θ_Nの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            thetaN[0][k][l] = 0;
        }
    }
    // θ_Nの計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                thetaN[0][k][l] = thetaN[0][k][l] + invphiphi[k][m] * phiy[m][l];
            }
        }
    }

    printf("N=%dのとき、θ_N=\n", N);
    //θ_Nの出力
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaN[0][k][l]);
        }
    }
    printf("\n");
    //式(6.5)ここまで

    //式(6.17)ここから
    printf("式(6.17)\n");
    //重み行列である、共分散行列Vの逆行列Qの計算
    // 単位行列の生成
    for (int k = 0; k < 2; k++)
    {
        for (int l = 0; l < 2; l++)
        {
            if (k == l)
            {
                Q[0][k][l] = 1.0;
            }
            else
            {
                Q[0][k][l] = 0;
            }
        }
    }
    // 掃き出し法
    for (int k = 0; k < 2; k++)
    {
        temp = 1 / V[0][k][k];
        for (int l = 0; l < 2; l++)
        {
            V[0][k][l] = V[0][k][l] * temp;
            Q[0][k][l] = Q[0][k][l] * temp;
        }
        for (int l = 0; l < 2; l++)
        {
            if (k != l)
            {
                temp = V[0][l][k];
                for (int m = 0; m < 2; m++)
                {
                    V[0][l][m] = V[0][l][m] - V[0][k][m] * temp;
                    Q[0][l][m] = Q[0][l][m] - Q[0][k][m] * temp;
                }
            }
        }
    }

    // phiphiの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = 0;
        }
    }
    // phiyの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            phiy[k][l] = 0;
        }
    }

    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                if (l == 0)
                {
                    phi[k][l] = 1.0;
                }
                else if (l == 1)
                {
                    phi[k][l] = pow(x[0][e], k + 1);
                }
            }
        }

        // phiphiの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiQ1[k][l] = 0; //初期化
                for (int m = 0; m < p; m++)
                {
                    phiQ1[k][l] = phiQ1[k][l] + phi[m][k] * Q[0][m][l];
                }
            }
        }
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    phiphi[k][l] = phiphi[k][l] + phiQ1[k][m] * phi[m][l];
                }
            }
        }

        // phiyの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiQ2[k][l] = 0; //初期化
                for (int m = 0; m < p; m++)
                {
                    phiQ2[k][l] = phiQ2[k][l] + phi[m][k] * Q[0][m][l];
                }
            }
        }
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    phiy[k][l] = phiy[k][l] + phiQ2[k][m] * y[m][e];
                }
            }
        }
    }

    // phiphiの逆行列の計算
    //  単位行列の生成
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            if (k == l)
            {
                invphiphi[k][l] = 1.0;
            }
            else
            {
                invphiphi[k][l] = 0;
            }
        }
    }
    // 掃き出し法
    for (int k = 0; k < p; k++)
    {
        temp = 1 / phiphi[k][k];
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = phiphi[k][l] * temp;
            invphiphi[k][l] = invphiphi[k][l] * temp;
        }
        for (int l = 0; l < p; l++)
        {
            if (k != l)
            {
                temp = phiphi[l][k];
                for (int m = 0; m < p; m++)
                {
                    phiphi[l][m] = phiphi[l][m] - phiphi[k][m] * temp;
                    invphiphi[l][m] = invphiphi[l][m] - invphiphi[k][m] * temp;
                }
            }
        }
    }

    // θ_Nの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            thetaN[1][k][l] = 0;
        }
    }
    // θ_Nの計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                thetaN[1][k][l] = thetaN[1][k][l] + invphiphi[k][m] * phiy[m][l];
            }
        }
    }

    printf("N=%dのとき、θ_N=\n", N);
    //θ_Nの出力
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaN[1][k][l]);
        }
    }
    printf("\n");
    //式(6.17)ここまで

    //推定誤差共分散
    for (int t = 0; t < 2; t++)
    {
        if (t == 0)
        {
            printf("式(6.5)\n");
        }
        else if (t == 1)
        {
            printf("式(6.17)\n");
        }
        // estVNの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                estVN[t][k][l] = 0;
            }
        }

        for (e = 0; e < N; e++)
        {
            //φの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    if (l == 0)
                    {
                        phi[k][l] = 1.0;
                    }
                    else if (l == 1)
                    {
                        phi[k][l] = pow(x[0][e], k + 1);
                    }
                }
            }
            //φ(x)*θNの計算
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < q; l++)
                {
                    phitheta[t][k][l] = 0; // phithetaの初期化
                    for (int m = 0; m < p; m++)
                    {
                        phitheta[t][k][l] = phitheta[t][k][l] + phi[k][m] * thetaN[t][m][l];
                    }
                }
            }
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    estVN[t][k][l] = estVN[t][k][l] + (y[k][e] - phitheta[t][k][0]) * (y[l][e] - phitheta[t][l][0]) / (N - p);
                }
            }
        }
        printf("estVN=\n");
        for (int k = 0; k < 2; k++)
        {
            for (int l = 0; l < 2; l++)
            {
                printf("%lf ", estVN[t][k][l]);
            }
            printf("\n");
        }
        printf("\n");
    }
    // 推定値と推定誤差共分散ここまで

    // 収束の仕方ここから
    int varyN;
    double varythetaN[2][p][q];

    //式(6.5)ここから
    printf("式(6.5)\n");
    for (varyN = 100; varyN <= 1000; varyN = varyN + 100)
    {

        // phiphiの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = 0;
            }
        }
        // phiyの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phiy[k][l] = 0;
            }
        }

        for (e = 0; e < varyN; e++)
        {
            //φの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    if (l == 0)
                    {
                        phi[k][l] = 1.0;
                    }
                    else if (l == 1)
                    {
                        phi[k][l] = pow(x[0][e], k + 1);
                    }
                }
            }

            // phiphiの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    for (int m = 0; m < p; m++)
                    {
                        phiphi[k][l] = phiphi[k][l] + phi[m][k] * phi[m][l];
                    }
                }
            }

            // phiyの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < q; l++)
                {
                    for (int m = 0; m < p; m++)
                    {
                        phiy[k][l] = phiy[k][l] + phi[k][m] * y[m][e];
                    }
                }
            }
        }

        // phiphiの逆行列の計算
        //  単位行列の生成
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                if (k == l)
                {
                    invphiphi[k][l] = 1.0;
                }
                else
                {
                    invphiphi[k][l] = 0;
                }
            }
        }
        // 掃き出し法
        for (int k = 0; k < p; k++)
        {
            temp = 1 / phiphi[k][k];
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = phiphi[k][l] * temp;
                invphiphi[k][l] = invphiphi[k][l] * temp;
            }
            for (int l = 0; l < p; l++)
            {
                if (k != l)
                {
                    temp = phiphi[l][k];
                    for (int m = 0; m < p; m++)
                    {
                        phiphi[l][m] = phiphi[l][m] - phiphi[k][m] * temp;
                        invphiphi[l][m] = invphiphi[l][m] - invphiphi[k][m] * temp;
                    }
                }
            }
        }

        // θ_Nの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                varythetaN[0][k][l] = 0;
            }
        }
        // θ_Nの計算
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    varythetaN[0][k][l] = varythetaN[0][k][l] + invphiphi[k][m] * phiy[m][l];
                }
            }
        }

        //printf("N=%dのとき、θ_N=\n", varyN);
        printf("%d ", varyN);
        //θ_Nの出力
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                printf("%lf ", varythetaN[0][k][l]);
            }
        }
        printf("\n");
    }
    //式(6.5)ここまで
    printf("\n");

    //式(6.17)ここから
    printf("式(6.17)\n");
    for (varyN = 100; varyN <= 1000; varyN = varyN + 100)
    {
        //重み行列である、共分散行列Vの逆行列Qの計算
        // 単位行列の生成
        for (int k = 0; k < 2; k++)
        {
            for (int l = 0; l < 2; l++)
            {
                if (k == l)
                {
                    Q[0][k][l] = 1.0;
                }
                else
                {
                    Q[0][k][l] = 0;
                }
            }
        }
        // 掃き出し法
        for (int k = 0; k < 2; k++)
        {
            temp = 1 / V[0][k][k];
            for (int l = 0; l < 2; l++)
            {
                V[0][k][l] = V[0][k][l] * temp;
                Q[0][k][l] = Q[0][k][l] * temp;
            }
            for (int l = 0; l < 2; l++)
            {
                if (k != l)
                {
                    temp = V[0][l][k];
                    for (int m = 0; m < 2; m++)
                    {
                        V[0][l][m] = V[0][l][m] - V[0][k][m] * temp;
                        Q[0][l][m] = Q[0][l][m] - Q[0][k][m] * temp;
                    }
                }
            }
        }

        // phiphiの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = 0;
            }
        }
        // phiyの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phiy[k][l] = 0;
            }
        }

        for (e = 0; e < varyN; e++)
        {
            //φの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    if (l == 0)
                    {
                        phi[k][l] = 1.0;
                    }
                    else if (l == 1)
                    {
                        phi[k][l] = pow(x[0][e], k + 1);
                    }
                }
            }

            // phiphiの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    phiQ1[k][l] = 0; //初期化
                    for (int m = 0; m < p; m++)
                    {
                        phiQ1[k][l] = phiQ1[k][l] + phi[m][k] * Q[0][m][l];
                    }
                }
            }
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    for (int m = 0; m < p; m++)
                    {
                        phiphi[k][l] = phiphi[k][l] + phiQ1[k][m] * phi[m][l];
                    }
                }
            }

            // phiyの配列に代入
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < p; l++)
                {
                    phiQ2[k][l] = 0; //初期化
                    for (int m = 0; m < p; m++)
                    {
                        phiQ2[k][l] = phiQ2[k][l] + phi[m][k] * Q[0][m][l];
                    }
                }
            }
            for (int k = 0; k < p; k++)
            {
                for (int l = 0; l < q; l++)
                {
                    for (int m = 0; m < p; m++)
                    {
                        phiy[k][l] = phiy[k][l] + phiQ2[k][m] * y[m][e];
                    }
                }
            }
        }

        // phiphiの逆行列の計算
        //  単位行列の生成
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                if (k == l)
                {
                    invphiphi[k][l] = 1.0;
                }
                else
                {
                    invphiphi[k][l] = 0;
                }
            }
        }
        // 掃き出し法
        for (int k = 0; k < p; k++)
        {
            temp = 1 / phiphi[k][k];
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = phiphi[k][l] * temp;
                invphiphi[k][l] = invphiphi[k][l] * temp;
            }
            for (int l = 0; l < p; l++)
            {
                if (k != l)
                {
                    temp = phiphi[l][k];
                    for (int m = 0; m < p; m++)
                    {
                        phiphi[l][m] = phiphi[l][m] - phiphi[k][m] * temp;
                        invphiphi[l][m] = invphiphi[l][m] - invphiphi[k][m] * temp;
                    }
                }
            }
        }

        // θ_Nの初期化
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                varythetaN[1][k][l] = 0;
            }
        }
        // θ_Nの計算
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    varythetaN[1][k][l] = varythetaN[1][k][l] + invphiphi[k][m] * phiy[m][l];
                }
            }
        }

        //printf("N=%dのとき、θ_N=\n", varyN);
        printf("%d ", varyN);
        //θ_Nの出力
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                printf("%lf ", varythetaN[1][k][l]);
            }
        }
        printf("\n");
    }
    //式(6.17)ここまで
    // 収束の仕方ここまで

    return 0;
}