//数理工学実験テーマ6 //課題14
#include <stdio.h>
#include <math.h>

#define N 10000 //データファイルの行数

int main(int argc, char **argv)
{
    double x[1][N], y[2][N];

    //ファイル読み込みここから
    FILE *fp;
    fp = fopen("/Users/ats/Desktop/数理工学実験/20211213/kadai14/mmse_kadai7.txt", "r");
    if (fp == NULL)
    {
        printf("file not open...\n");
        return -1;
    }
    int e = 0;
    while (fscanf(fp, "%lf,%lf", &x[0][e], &y[0][e]) != EOF)
    {
        e++;
    }
    fclose(fp);
    //ファイル読み込みここまで

    int p = 3; // θ,φの行数
    int q = 1; // yの列数
    double phi[p];
    double phiphi[3][p][p];
    double keep_phiphi[3][p][p];
    double invphiphi[3][p][p]; // phiphiの逆行列を格納する配列
    double temp;               //逆行列を求めるのに一時的に用いる変数
    double phiy[3][p][q];

    double thetaN[3][p][q]; // N=10000,6000,4000の3つ分
    int s;

    double thetaNM[p][q];             //合成したθN=θ_{N+M}
    double large_phinotashizan[p][p]; // (ΦN^{-1}+ΦM^{-1})
    double inv_large_phinotashizan[p][p];
    double large_phitheta[3][p][q];

    // phiphiの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            for (int m = 0; m < 3; m++)
            {
                phiphi[m][k][l] = 0;
            }
        }
    }
    // phiyの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < 3; m++)
            {
                phiy[m][k][l] = 0;
            }
        }
    }

    // N=10000ここから
    s = 0; // N=10000のとき
    for (e = 0; e < N; e++)
    {
        //φの配列に代入
        phi[0] = 1;
        phi[1] = exp(-pow(x[0][e] - 1, 2) / 2);
        phi[2] = exp(-pow(x[0][e] + 1, 2));

        // phiphiの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiphi[s][k][l] = phiphi[s][k][l] + phi[k] * phi[l];
            }
        }

        // phiyの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phiy[s][k][l] = phiy[s][k][l] + phi[k] * y[0][e];
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
                invphiphi[s][k][l] = 1.0;
            }
            else
            {
                invphiphi[s][k][l] = 0;
            }
        }
    }
    // 掃き出し法
    for (int k = 0; k < p; k++)
    {
        temp = 1 / phiphi[s][k][k];
        for (int l = 0; l < p; l++)
        {
            phiphi[s][k][l] = phiphi[s][k][l] * temp;
            invphiphi[s][k][l] = invphiphi[s][k][l] * temp;
        }
        for (int l = 0; l < p; l++)
        {
            if (k != l)
            {
                temp = phiphi[s][l][k];
                for (int m = 0; m < p; m++)
                {
                    phiphi[s][l][m] = phiphi[s][l][m] - phiphi[s][k][m] * temp;
                    invphiphi[s][l][m] = invphiphi[s][l][m] - invphiphi[s][k][m] * temp;
                }
            }
        }
    }

    // θ_Nの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            thetaN[s][k][l] = 0;
        }
    }
    // θ_Nの計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                thetaN[s][k][l] = thetaN[s][k][l] + invphiphi[s][k][m] * phiy[s][m][l];
            }
        }
    }

    printf("N=%dのとき、θ_N=\n", N);
    //θ_Nの出力
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaN[s][k][l]);
        }
    }
    printf("\n");
    // N=10000ここまで

    // N=6000,4000ここから
    for (e = 0; e < N; e++)
    {

        if (e < 6000) // N=6000のとき
        {
            s = 1;
        }
        else if (e >= 6000) // N=4000のとき
        {
            s = 2;
        }
        //φの配列に代入
        phi[0] = 1;
        phi[1] = exp(-pow(x[0][e] - 1, 2) / 2);
        phi[2] = exp(-pow(x[0][e] + 1, 2));

        // phiphiの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                phiphi[s][k][l] = phiphi[s][k][l] + phi[k] * phi[l];
            }
        }

        // phiyの配列に代入
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                phiy[s][k][l] = phiy[s][k][l] + phi[k] * y[0][e];
            }
        }
    }
    for (s = 1; s <= 2; s++)
    {
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                keep_phiphi[s][k][l] = phiphi[s][k][l];
            }
        }
    }

    for (s = 1; s <= 2; s++)
    {
        // phiphiの逆行列の計算
        //  単位行列の生成
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < p; l++)
            {
                if (k == l)
                {
                    invphiphi[s][k][l] = 1.0;
                }
                else
                {
                    invphiphi[s][k][l] = 0;
                }
            }
        }
        // 掃き出し法
        for (int k = 0; k < p; k++)
        {
            temp = 1 / phiphi[s][k][k];
            for (int l = 0; l < p; l++)
            {
                phiphi[s][k][l] = phiphi[s][k][l] * temp;
                invphiphi[s][k][l] = invphiphi[s][k][l] * temp;
            }
            for (int l = 0; l < p; l++)
            {
                if (k != l)
                {
                    temp = phiphi[s][l][k];
                    for (int m = 0; m < p; m++)
                    {
                        phiphi[s][l][m] = phiphi[s][l][m] - phiphi[s][k][m] * temp;
                        invphiphi[s][l][m] = invphiphi[s][l][m] - invphiphi[s][k][m] * temp;
                    }
                }
            }
        }
    }

    // θ_Nの初期化
    for (s = 1; s <= 2; s++)
    {
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                thetaN[s][k][l] = 0;
            }
        }
    }
    for (s = 1; s <= 2; s++)
    {
        // θ_Nの計算
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                for (int m = 0; m < p; m++)
                {
                    thetaN[s][k][l] = thetaN[s][k][l] + invphiphi[s][k][m] * phiy[s][m][l];
                }
            }
        }
    }
    //θ_Nの出力
    for (s = 1; s <= 2; s++)
    {
        if (s == 1)
        {
            printf("N=%dのとき、θ_N=\n", 6000);
        }
        else if (s == 2)
        {
            printf("N=%dのとき、θ_N=\n", 4000);
        }
        for (int k = 0; k < p; k++)
        {
            for (int l = 0; l < q; l++)
            {
                printf("%lf\n", thetaN[s][k][l]);
            }
        }
        printf("\n");
    }
    // N=6000,4000ここまで

    //θ_{N+M}
    // thetaNM,large_phithetaの初期化
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            thetaNM[k][l] = 0;
            large_phitheta[1][k][l] = 0;
            large_phitheta[2][k][l] = 0;
        }
    }

    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            large_phinotashizan[k][l] = keep_phiphi[1][k][l] + keep_phiphi[2][k][l];
        }
    }

    // (ΦN^{-1}+ΦM^{-1})の逆行列の計算
    //  単位行列の生成
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < p; l++)
        {
            if (k == l)
            {
                inv_large_phinotashizan[k][l] = 1.0;
            }
            else
            {
                inv_large_phinotashizan[k][l] = 0;
            }
        }
    }
    // 掃き出し法
    for (int k = 0; k < p; k++)
    {
        temp = 1 / large_phinotashizan[k][k];
        for (int l = 0; l < p; l++)
        {
            large_phinotashizan[k][l] = large_phinotashizan[k][l] * temp;
            inv_large_phinotashizan[k][l] = inv_large_phinotashizan[k][l] * temp;
        }
        for (int l = 0; l < p; l++)
        {
            if (k != l)
            {
                temp = large_phinotashizan[l][k];
                for (int m = 0; m < p; m++)
                {
                    large_phinotashizan[l][m] = large_phinotashizan[l][m] - large_phinotashizan[k][m] * temp;
                    inv_large_phinotashizan[l][m] = inv_large_phinotashizan[l][m] - inv_large_phinotashizan[k][m] * temp;
                }
            }
        }
    }
    // large_phithetaの計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                large_phitheta[1][k][l] = large_phitheta[1][k][l] + keep_phiphi[1][k][m] * thetaN[1][m][l];
                large_phitheta[2][k][l] = large_phitheta[2][k][l] + keep_phiphi[2][k][m] * thetaN[2][m][l];
            }
        }
    }

    //θ_{N+M}の計算
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            for (int m = 0; m < p; m++)
            {
                thetaNM[k][l] = thetaNM[k][l] + inv_large_phinotashizan[k][m] * (large_phitheta[1][m][l] + large_phitheta[2][m][l]);
            }
        }
    }
    //θ_{N+M}の出力
    printf("N=%dのとき、θ_NM=\n", N);
    for (int k = 0; k < p; k++)
    {
        for (int l = 0; l < q; l++)
        {
            printf("%lf\n", thetaNM[k][l]);
        }
    }
    printf("\n");

    return 0;
}