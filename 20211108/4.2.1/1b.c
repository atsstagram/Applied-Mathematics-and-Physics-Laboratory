//数理工学実験テーマ4 //4.2節の課題 //1(b)
#include <stdio.h>
#include <math.h>

double fb(double x)
{
    return 1.0 / pow(x, 3.0);
}

int main(int argc, char **argv)
{
    int n;

    int i;        //xの添字
    double x[17]; //x[0]は空、他は添字に対応
    double fx[17];

    int k;         //yの添字
    double y[152]; //x_iよりもさらに細かい分点y_k
    double l[17];  //l_i(x)
    double P[152]; //P(x)

    double a = 0.1; //左端
    double b = 2.0; //右端

    for (n = 2; n <= 16; n = n * 2)
    {
        printf("n=%dの時\n", n);
        for (i = 1; i <= n; i++) //分点x_iの計算
        {
            x[i] = a + (b - a) / (n - 1) * (i - 1);
        }
        for (i = 1; i <= n; i++) //f(x)の計算
        {
            fx[i] = fb(x[i]);
        }

        //ここからP(x)を数値的に計算
        for (k = 1; k <= (n - 1) * 10 + 1; k++) //Pの初期化
        {
            P[k] = 0;
        }

        for (k = 1; k <= (n - 1) * 10 + 1; k++) //x_iより10倍細かい分点y_k
        {
            y[k] = a + (b - a) / (10 * (n - 1)) * (k - 1);
        }

        for (k = 1; k <= (n - 1) * 10 + 1; k++)
        {
            for (i = 1; i <= n; i++) //lの初期化
            {
                l[i] = 1.0;
            }

            for (i = 1; i <= n; i++) //l_i(y_k)の計算
            {
                for (int j = 1; j <= n; j++)
                {
                    if (j != i)
                    {
                        l[i] = l[i] * (y[k] - x[j]) / (x[i] - x[j]);
                    }
                }
            }
            for (i = 1; i <= n; i++) //P(y_k)の計算
            {
                P[k] = P[k] + fx[i] * l[i];
            }

            printf("%lf %lf\n", y[k], P[k]);
        }

        printf("\n");
    }

    return 0;
}