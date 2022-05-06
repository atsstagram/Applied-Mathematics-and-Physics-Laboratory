//数理工学実験テーマ6 //課題11
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    int N = 1000; //データファイルの行数
    double x1[N], y[N];

    //ファイル読み込みここから
    FILE *fp;
    fp = fopen("/Users/ats/Desktop/数理工学実験/20211213/kadai11/mmse_kadai4.txt", "r");
    if (fp == NULL)
    {
        printf("file not open...\n");
        return -1;
    }
    int e = 0;
    while (fscanf(fp, "%lf,%lf", &x1[e], &y[e]) != EOF)
    {
        e++;
    }
    fclose(fp);
    //ファイル読み込みここまで

    int p = 4; // θ,φの要素数
    int q = 1; // yの要素数
    double phi[p];
    double phiphi[p][p];
    double invphiphi[p][p]; // phiphiの逆行列を格納する配列
    double temp;            //逆行列を求めるのに一時的に用いる変数
    double phiy[p][q];

    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = 0; // phiphiの初期化
        }
    }
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            phiy[k][l] = 0; // phiyの初期化
        }
    }

    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        for (int k = 0; k < p; k++)
        {
            phi[k] = pow(x1[e], k);
        }

        // phiphiの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = phiphi[k][l] + phi[k] * phi[l];
            }
        }

        // phiyの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phiy[k][l] = phiy[k][l] + phi[k] * y[e];
            }
        }
    }

    // 単位行列の生成
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

    double thetaN[p][q];
    // θ_Nの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            thetaN[k][l] = 0;
        }
    }
    // θ_Nの計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                thetaN[k][l] = thetaN[k][l] + invphiphi[k][m] * phiy[m][l];
            }
        }
    }

    printf("N=%dのとき、θ_N=\n", N);
    //θ_Nの出力
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaN[k][l]);
        }
    }

    double estVN = 0; //推定誤差共分散行列
    double phitheta = 0;
    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        for (int k = 0; k < p; k++)
        {
            phi[k] = pow(x1[e], k);
        }
        //φ(x)*θNの計算
        phitheta = 0;
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phitheta = phitheta + phi[k] * thetaN[k][l];
            }
        }
        estVN = estVN + pow(y[e] - phitheta, 2);
    }
    estVN = estVN / (N - p);
    printf("estVN=%lf\n", estVN);
    printf("\n");
    // 1ここまで

    // 3ここから
    double avy = 0; // yの平均を格納する変数
    for (e = 0; e < N; e++)
    {
        avy = avy + y[e] / N;
    }
    // printf("yの平均=%lf\n", avy);

    double C;      //決定変数C
    double CU = 0; // Cの分子
    double CB = 0; // Cの分母
    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        for (int k = 0; k < p; k++)
        {
            phi[k] = pow(x1[e], k);
        }
        //φ(x)*θNの計算
        phitheta = 0;
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phitheta = phitheta + phi[k] * thetaN[k][l];
            }
        }
        CU = CU + pow(phitheta - avy, 2);
        CB = CB + pow(y[e] - avy, 2);
    }
    C = CU / CB;
    printf("決定変数C=%lf\n", C);

    return 0;
}