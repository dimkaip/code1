#include <stdio.h>
int printstars(int h);
int paules(int j);
int Or8ogoniotriangle(int h){
	int i,k;
	printf("Give Or8ogoniotriangle height:");
	scanf("%d", &h);
	printf("*\n");
	for(i=1;i<h;i++){
	printf("*");
	paules(i);
	printf("*");
	printf("\n");
	}
	printhstars(h);

	return 0;
}

int printhstars(int h){
	int i;
	for(i=0;i<h+1;i++){
	printf("*");}
    return 0;

}

int paules(int j){
    int i;
    for(i=0;i<j-1;i++){
    printf("-");
    }

}
