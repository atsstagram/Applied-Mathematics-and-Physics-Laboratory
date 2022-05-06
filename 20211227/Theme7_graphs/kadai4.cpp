//数理工学実験テーマ7 //課題4

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <math.h>
#include <numeric>
#include <time.h>
using namespace std;
#define suf 100000000 //十分大きい数

//探索済か判定する配列
vector<bool> searching;

//負の重みを持つ枝の長さの和を格納する配列
vector<int> NegaBranches;

//課題3で設定した分枝限定アルゴリズムを実装（nodecountは探索したノード数を数える変数）
void BOSPA(int x, vector<int> &F, vector<vector<int>> G, int n, int &temp, int64_t &nodecount)
{
    for (int y = 0; y < n; y++)
    {
        //グラフ上に枝(x,y)が存在するかを判定
        if (G[x][y] != suf)
        {
            // yが探索済かを判定
            if (searching[y])
            {
                nodecount++;
                if (y == n - 1)
                {
                    int sum = 0;
                    for (int i = 0; i < F.size() - 1; i++)
                    {
                        sum += G[F[i]][F[i + 1]];
                    }
                    sum += G[F[F.size() - 1]][n - 1];
                    if (sum < temp)
                        temp = sum;
                }
                else
                {
                    //限定操作
                    int sum = 0;
                    for (int i = 0; i < F.size() - 1; i++)
                    {
                        sum += G[F[i]][F[i + 1]];
                    }
                    sum += G[F[F.size() - 1]][y];
                    int edge = n - 1 - F.size();
                    int NegaBranch = NegaBranches[edge];
                    if (sum + NegaBranch > temp)
                    {
                        //終端
                        continue;
                    }
                    else
                    {
                        //継続
                        F.push_back(y);
                        // y を探索済にする
                        searching[y] = false;
                        BOSPA(y, F, G, n, temp, nodecount);
                    }
                }
            }
        }
    }
    //探索できる点がないので、1つ前の節点に戻る
    searching[x] = true;
    F.pop_back();
}

int main()
{
    for (int n = 6; n <= 20; n++) //調べるnの範囲を指定
    {
        for (int m = n * 2; m <= n * (n - 1); m++)
        {
            string a = to_string(m);
            string b = to_string(n);
            ifstream fin("n_" + b + "/n_" + b + "_m_" + a + ".txt");
            int check_n, check_m;
            fin >> check_n >> check_m;
            vector<vector<int>> G(n, vector<int>(n, suf));
            for (int i = 0; i < m; i++)
            {
                int from, to, length;
                fin >> from >> to >> length;
                G[from][to] = length;
            }

            vector<int> MinLength(n, suf);
            NegaBranches.assign(n, 0);
            for (int j = 1; j < n; j++)
            {
                for (int i = 0; i < n - 1; i++)
                {
                    MinLength[j] = min(MinLength[j], G[i][j]);
                }
            }
            sort(MinLength.begin(), MinLength.end());
            int sum = 0;
            for (int i = 0; i < n; i++)
            {
                NegaBranches[i] = sum;
                if (MinLength[i] < 0)
                    sum += MinLength[i];
            }

            //全ての節点を未探索にする
            searching.assign(n, true);
            //節点集合
            vector<int> F;
            // Fに始点sを格納
            F.push_back(0);
            searching[0] = false;

            //探索前の最短路の長さの暫定値を十分大きく設定しておく
            int temp = suf;

            //探索したノード数を数える
            int64_t nodecount = 0;

            double starttime = clock();
            BOSPA(0, F, G, n, temp, nodecount);
            double endtime = clock();
            double time = (endtime - starttime) / CLOCKS_PER_SEC;

            cout << n << " " << m << " ";
            cout << temp << " ";
            cout << nodecount << " ";
            cout << fixed << setprecision(8) << time << endl;

            //計算に30s以上かかった場合次のnを調べる
            if (time > 30.0)
            {
                break;
            }
        }
    }
}