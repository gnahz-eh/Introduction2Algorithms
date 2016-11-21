#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<time.h>
void countingSort(int *p, int *q, int k, int len) {
	int *aux = (int *)malloc(sizeof(int)*(1+k)); //0 ~ k
	
	for (int i = 0; i <= k; i++)
	{
		aux[i] = 0;
	}

	for (int i = 0; i < len; i++)
	{
		aux[p[i]] = aux[p[i]] + 1;
	}

	for (int i = 1; i <= k; i++)
	{
		aux[i] = aux[i] + aux[i-1];
	}

	for (int i = len - 1; i >= 0 ; i--)
	{
		q[aux[p[i]]-1] = p[i];

		aux[p[i]] = aux[p[i]]-1;
	}
}

void printA(int *p, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%2d ", p[i]);
		/*if(p[i+1]!= p[i]) {
			puts("");
		}*/
		for(int j = 0; j < p[i]; j++) {
			printf("*");
		}
		printf("\n");
		/*if(i % 10 == 0) {
			puts("");
		}*/
	}
}


void main() {

	int i;
	int a[50];
	int q[50];
	srand(time(NULL));
	
	for (i = 0; i < 50; i++)
	{
		a[i] = rand()%50;
	}

	printf("before: \n");
	printA(a, 50);
	puts("");

	
	countingSort(a, q, 49, 50);
	
	printf("after:hh\n");
	printA(q, 50);

	system("pause");
	
}
