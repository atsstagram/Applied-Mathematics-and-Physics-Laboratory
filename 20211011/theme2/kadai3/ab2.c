//数理工学実験テーマ２ //課題３ //2次のアダムス・バッシュホース法
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv){
    int i=10; 
    int N=pow(2,i); //ステップ数
    double deltaT=1.0/N; //ステップ幅
    double U0=exp(0); //u0の値
    double U1=exp(deltaT); //u1の値
    double Un, preUn, prepreUn; //それぞれ、u_n, u_(n-1), u_(n-2)

    double e1=exp(1.0); //解析解

    double E; //数値解と解析解との差

    prepreUn=U0; 
    preUn=U1;

    int k; //試行回数
    for(int k=0; k<N-1; k++){
        Un= preUn + deltaT/2*(3*preUn-prepreUn);

        //次の試行のための代入。順番に注意。
        prepreUn=preUn;
        preUn=Un;
    }
    Un=preUn; //UNにu_Nの値を代入

    E=Un-e1;
    E=fabs(E); //Eの絶対値を返す

    //printf("deltaT=%lf\n", deltaT);
    printf("uN=%lf\n", Un);
    printf("|uN-u1|=%lf\n", E);

    return 0; 
}