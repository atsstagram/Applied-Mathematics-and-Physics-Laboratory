//数理工学実験テーマ２ //課題３ //前進オイラー法
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv){
    int i=10; 
    int N=pow(2,i); //ステップ数
    double deltaT=1.0/N; //ステップ幅
    double U0=exp(0); //u0の値
    double Un, preUn; //それぞれ、u_n, u_(n-1)

    double e1=exp(1.0); //解析解

    double E; //数値解と解析解との差

    preUn=U0;

    int k; //試行回数
    for(int k=0; k<N; k++){
        Un= preUn + preUn*deltaT;
        preUn=Un; //次の試行のための代入
    }
    Un=preUn;

    E=Un-e1;
    E=fabs(E); //Eの絶対値を返す

    //printf("deltaT=%lf\n", deltaT);
    printf("uN=%lf\n", Un);
    printf("|uN-u1|=%lf\n", E);

    return 0; 
}