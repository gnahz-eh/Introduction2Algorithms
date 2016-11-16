#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void insertSort(int *p, int len) {
	
	int i, j;
	
	if(p == NULL || len == 0) {
		return;
	}

	for (i = 1; i < len; i++)
	{
		int key = p[i];
		for(j = i; j > 0 && key < p[j-1]; j--) {
			p[j] = p[j-1];
		}
		p[j] = key;
	}
}

void printA(int *p, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ", p[i]);
		if(i % 10 == 0) {
			puts("");
		}
	}
}


void main() {

	int i;
	int a[100];
	srand(time(NULL));
	
	for (i = 0; i < 100; i++)
	{
		a[i] = rand()%100;
	}

	printf("before: \n");
	printA(a, 100);
	puts("");

	
	insertSort(a, 100);
	
	printf("after:");
	printA(a, 100);
	
}
