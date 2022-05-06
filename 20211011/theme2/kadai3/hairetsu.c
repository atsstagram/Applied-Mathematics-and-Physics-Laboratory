#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{

    int a[3];
    int i;

    a[0]=8;
    a[1]=2;
    a[2]=9;

    char b[3];
    b[1]='a';
    b[2]='c';
    b[3]='e';



    for(int i=0; i<3; i++){
        printf("%d, ", a[i]);
        printf("%s, ", b[i]);
    }

    return 0;


}