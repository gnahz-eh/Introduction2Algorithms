#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void merge(int *p, int lo, int mid, int hi, int *aux) {
	
	int i = lo;
	int j = mid + 1;
	int k;
	for (k = lo,0; k <= hi; k++)
	{
		aux[k] = p[k];
	}
	for (k = lo; k <= hi; k++)
	{
		if (i > mid) p[k] = aux[j++];
		else if(j > hi) p[k] = aux[i++];
		else if(aux[j] < aux[i]) p[k] = aux[j++];
		else p[k] = aux[i++];
	}

}

void mergeSort(int *p, int lo, int hi, int *aux) {
	
	int mid;
	if(lo >= hi) {
		return;
	}

	mid = (lo + hi)/2;
	mergeSort(p, lo, mid, aux);
	mergeSort(p, mid+1, hi, aux);
	merge(p, lo, mid, hi, aux);	
}

void printA(int *p, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ", p[i]);
		if(i % 10 == 0) {
			puts("");puts("");
		}
	}
}


void main() {

	int i;
	int a[100];
	int aux[100];
	srand(time(NULL));
	
	for (i = 0; i < 100; i++)
	{
		a[i] = rand()%100;
	}

	printf("before: \n");
	printA(a, 100);
	puts("");

	
	mergeSort(a, 0, 99, aux);
	
	printf("after:");
	printA(a, 100);
	
}
