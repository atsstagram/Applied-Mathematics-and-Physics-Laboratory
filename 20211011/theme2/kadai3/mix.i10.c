//数理工学実験テーマ２ //課題３ //i=10のとき
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv){
    int i=10; 
    int N=pow(2,i); //ステップ数
    double deltaT=1.0/N; //ステップ幅

    double U0=exp(0); //u0の値
    double U1=exp(deltaT); //u1の値
    double U2=exp(2*deltaT); //u2の値
    double Un, preUn, prepreUn, preprepreUn; //それぞれ、u_n ~ u_(n-3)

    double e1=exp(1.0); //u(1)の解析解

    double E; //数値解と解析解との差の絶対値



    //前進オイラー法ここから
    preUn=U0;

    int k; //試行回数
    for(int k=0; k<N; k++){
        Un= preUn + preUn*deltaT;
        preUn=Un; //次の試行のための代入
    }
    Un=preUn; //UNにu_Nの値を代入

    E=fabs(Un-e1); //Eの絶対値を返す

    //printf("deltaT=%lf\n", deltaT);
    printf("FE: uN=%.15lf\n", Un);
    printf("FE: |uN-u1|=%.15lf\n", E);
    printf("\n");

    //前進オイラー法ここまで



    //2次のアダムス・バッシュフォース法ここから
    prepreUn=U0; 
    preUn=U1;

    int l; //試行回数
    for(int l=0; l<N-1; l++){
        Un= preUn + deltaT/2*(3*preUn-prepreUn);
        prepreUn=preUn; //次の試行のための代入。順番に注意。
        preUn=Un;
    }
    Un=preUn; //UNにu_Nの値を代入

    E=fabs(Un-e1); //Eの絶対値を返す

    printf("AB2: uN=%.15lf\n", Un);
    printf("AB2: |uN-u1|=%.15lf\n", E);
    printf("\n");
    //2次のアダムス・バッシュフォース法ここまで



    //3次のアダムス・バッシュフォース法ここから
    preprepreUn=U0; 
    prepreUn=U1;
    preUn=U2;

    int m; //試行回数
    for(int m=0; m<N-2; m++){
        Un= preUn + deltaT/12*(23*preUn-16*prepreUn+5*preprepreUn);
        preprepreUn=prepreUn; //次の試行のための代入。順番に注意。
        prepreUn=preUn;
        preUn=Un;
    }
    Un=preUn; //UNにu_Nの値を代入

    E=fabs(Un-e1); //数値解と解析解との差の絶対値

    printf("AB3: uN=%.15lf\n", Un);
    printf("AB3: |uN-u1|=%.15lf\n", E);
    printf("\n");
    //3次のアダムス・バッシュフォース法ここまで



    //ホイン法（2次のルンゲ・クッタ法）ここから
    preUn=U0; 
    double temporaryUn; //un*

    int p; //試行回数
    for(int p=0; p<N; p++){
        temporaryUn= preUn + preUn*deltaT;
        Un= preUn + deltaT/2*(preUn+temporaryUn);
        preUn=Un; //次の試行のための代入
    }
    Un=preUn; //UNにu_Nの値を代入

    E=fabs(Un-e1); //数値解と解析解との差の絶対値

    printf("H: uN=%.15lf\n", Un);
    printf("H: |uN-u1|=%.15lf\n", E);
    printf("\n");
    //ホイン法（2次のルンゲ・クッタ法）ここまで



    //（4次の）ルンゲ・クッタ法ここから
    preUn=U0; 
    double F1, F2, F3, F4; //4次のルンゲ・クッタ法で用いられているF1~F4

    int q; //試行回数
    for(int q=0; q<N; q++){
        F1= preUn;
        F2= preUn + F1*deltaT/2;
        F3= preUn + F2*deltaT/2;
        F4= preUn + F3*deltaT;
        Un= preUn + deltaT/6*(F1+2*F2+2*F3+F4);
        preUn=Un; //次の試行のための代入
    }
    Un=preUn; //UNにu_Nの値を代入

    E=fabs(Un-e1); //数値解と解析解との差の絶対値

    printf("RK: uN=%.15lf\n", Un);
    printf("RK: |uN-u1|=%.15lf\n", E);
    printf("\n");
    //（4次の）ルンゲ・クッタ法ここまで


    return 0; 
}