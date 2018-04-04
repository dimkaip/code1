#include <stdio.h>
#include <stdlib.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int diabase(int *num)
{
    printf(" Choose shape.\n Square:1, Romvos:2, Or8ogonio triangle:3, Isoskeles triangle:4 \n");
    scanf("%d",num);
    return 0;

}

int shape(int num)
{
    if (num==1)
    {
        Square();
    }
    if (num==2)
    {
        Romvos();
    }
    if (num==3)
    {
        Or8ogoniotriangle();
    }
    if (num==4)
    {
        Isoskelestriangle();
    }
    return 0;
}

int check(int num)
{
    if (num==0)exit(0);
    return 0;
}


int main()
{
    int num=1;
    while (num!=0)
    {
        diabase(&num);
        check(num);
        shape(num);
    }
    return 0;
}


