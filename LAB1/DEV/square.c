#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int printhstars(int h);
int printlines(int h);
int Square() {
	int i,h;
	printf("Give Square height:");
	scanf("%d", &h);
	printstars(h);
	for (i=0;i<h-2;i++){
		printlines(h);
	}

	printhstars(h);

	return 0;
}
int printstars(int h){
	int i;
	for(i=0;i<h;i++){
	printf("*");}
	printf("\n");
	return 0;
}

int printlines(int h){
	int j;
	printf("*");
	for(j=0;j<h-2;j++){
	printf("-");}
	printf("*");
	printf("\n");
	return 0;
}
