#include <stdio.h>

int Romvos(int h){
    int i, k,j,l;
    printf("Give Romvos height \n");
    scanf("%d", &h);
    //checkodd(h);
    for(k=1; k<=(h+1)/2; k++)
    {
        for(i=1;i<=(h+1)/2-k;i++){
            printf("-");}
        printf("*");
        for(j=1;j<=2*k-2;j++){
            printf("-");
        }
        if(k!=1){printf("*");}
        printf("\n");
    }

    for(k=(h+1)/2+1; k<=h; k++)
    {
        for(i=1;i<=k-(h+1)/2;i++){
            printf("-");}
        printf("*");
        for(j=1;j<=2*h-2*k;j++){
            printf("-");
        }
        if(k!=h){printf("*");}
        printf("\n");

    }


    return(0);

}
//int checkodd(int h){
//    while (h%2==0){
//        printf("This number isn't odd. Give another one:");
//        scanf("%d", &h);}
//    return 0;
//
//}
