//数理工学実験テーマ6 //課題8
#include <stdio.h>
#include <math.h>

#define N 10000 //データファイルの行数

int main(int argc, char **argv)
{
    double x1[N], x2[N], y[N];

    //ファイル読み込みここから
    FILE *fp;
    fp = fopen("/Users/ats/Desktop/数理工学実験/20211213/kadai8/mmse_kadai1.txt", "r");
    if (fp == NULL)
    {
        printf("file not open...\n");
        return -1;
    }
    int e = 0;
    while (fscanf(fp, "%lf,%lf,%lf", &x1[e], &x2[e], &y[e]) != EOF)
    {
        e++;
    }
    fclose(fp);
    //ファイル読み込みここまで

    int p = 2; // φの要素数
    int q = 1; // yの要素数
    double phiphi[p][p];
    double invphiphi[p][p]; //phiphiの逆行列を格納する配列
    double phiy[p][q];
    //int i, j;

    for (int k = 0; k < p; k++)
    { // phiphiの初期化
        for (int l = 0; l < p; l++)
        {
            phiphi[k][l] = 0;
        }
    }
    for (int k = 0; k < p; k++)
    { // phiyの初期化
        for (int l = 0; l < q; l++)
        {
            phiy[k][l] = 0;
        }
    }

    for (e = 0; e < N; e++)
    {
        phiphi[0][0] = phiphi[0][0] + x1[e] * x1[e];
        phiphi[0][1] = phiphi[0][1] + x2[e] * x1[e];
        phiphi[1][0] = phiphi[1][0] + x1[e] * x2[e];
        phiphi[1][1] = phiphi[1][1] + x2[e] * x2[e];

        phiy[0][0] = phiy[0][0] + x1[e] * y[e];
        phiy[1][0] = phiy[1][0] + x2[e] * y[e];
    }

    double det1 = phiphi[0][0] * phiphi[1][1] - phiphi[0][1] * phiphi[1][0];
    if (det1 == 0)
    {
        printf("逆行列は存在しない\n");
    }
    else
    {
        invphiphi[0][0] = phiphi[1][1] / det1;
        invphiphi[0][1] = -phiphi[0][1] / det1;
        invphiphi[1][0] = -phiphi[1][0] / det1;
        invphiphi[1][1] = phiphi[0][0] / det1;
    }

    double thetaN[p][q];
    thetaN[0][0] = invphiphi[0][0] * phiy[0][0] + invphiphi[0][1] * phiy[1][0];
    thetaN[1][0] = invphiphi[1][0] * phiy[0][0] + invphiphi[1][1] * phiy[1][0];

    printf("N=%dのとき、θ_N=\n", N);
    for (int k = 0; k < p; k++)
    { //θ_Nの出力
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaN[k][l]);
        }
    }

    double estVN = 0; //推定誤差共分散行列
    for (e = 0; e < N; e++)
    {
        estVN = estVN + (y[e] - (x1[e] * thetaN[0][0] + x2[e] * thetaN[1][0])) * (y[e] - (x1[e] * thetaN[0][0] + x2[e] * thetaN[1][0]));
    }
    estVN = estVN / (N - p);
    printf("estVN=%lf\n", estVN);
    printf("\n");
    // 8-1ここまで

    // 8-2ここから
    int varyN;
    for (varyN = 2; varyN <= 8192; varyN = varyN * 2)
    {

        for (int k = 0; k < p; k++)
        { // phiphiの初期化
            for (int l = 0; l < p; l++)
            {
                phiphi[k][l] = 0;
            }
        }
        for (int k = 0; k < p; k++)
        { // phiyの初期化
            for (int l = 0; l < q; l++)
            {
                phiy[k][l] = 0;
            }
        }

        for (e = 0; e < varyN; e++)
        {
            phiphi[0][0] = phiphi[0][0] + x1[e] * x1[e];
            phiphi[0][1] = phiphi[0][1] + x2[e] * x1[e];
            phiphi[1][0] = phiphi[1][0] + x1[e] * x2[e];
            phiphi[1][1] = phiphi[1][1] + x2[e] * x2[e];

            phiy[0][0] = phiy[0][0] + x1[e] * y[e];
            phiy[1][0] = phiy[1][0] + x2[e] * y[e];
        }

        det1 = phiphi[0][0] * phiphi[1][1] - phiphi[0][1] * phiphi[1][0];
        if (det1 == 0)
        {
            printf("逆行列は存在しない\n");
        }
        else
        {
            invphiphi[0][0] = phiphi[1][1] / det1;
            invphiphi[0][1] = -phiphi[0][1] / det1;
            invphiphi[1][0] = -phiphi[1][0] / det1;
            invphiphi[1][1] = phiphi[0][0] / det1;
        }

        double varythetaN[p][q];
        varythetaN[0][0] = invphiphi[0][0] * phiy[0][0] + invphiphi[0][1] * phiy[1][0];
        varythetaN[1][0] = invphiphi[1][0] * phiy[0][0] + invphiphi[1][1] * phiy[1][0];

        //printf("N=%dのとき、θ_N=\n", varyN);
        printf("%d ", varyN);
        for (int k = 0; k < p; k++)
        { //θ_Nの出力
            for (int l = 0; l < q; l++)
            {
                printf("%lf ", varythetaN[k][l]);
            }
        }
        printf("\n");
    }
    // 8-2ここまで

    // 8-3ここから
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
        CU = CU + pow(x1[e] * thetaN[0][0] + x2[e] * thetaN[1][0] - avy, 2);
        CB = CB + pow(y[e] - avy, 2);
    }
    C = CU / CB;
    printf("決定変数C=%lf\n", C);

    return 0;
}