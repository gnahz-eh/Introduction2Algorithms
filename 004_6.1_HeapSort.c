#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int parent(int i) {
	return (i-1)/2;
}

int leftChild(int i) {
	return i*2+1;
}

int rightChild(int i) {
	return i*2+2;
}

void swap(int *a, int *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void maxHeap(int *p, int len, int i) {

	int lChild = leftChild(i);
	int rChild = rightChild(i);
	int nMaxPos;

	if (lChild < len && p[lChild] > p[i]) {
		
		nMaxPos = lChild;
	} else {
		nMaxPos = i;
	}

	if (rChild < len && p[rChild] > p[nMaxPos]) {

		nMaxPos = rChild;
	}

	if (nMaxPos != i) {
		swap(&p[nMaxPos], &p[i]);
		maxHeap(p, len, nMaxPos);
	}
}

void buildMaxHeap(int *p, int len) {

	for (int i = parent(len-1); i >= 0; i--) {
		maxHeap(p, len, i);
	}
}

void heapSort(int *p, int len) {

	buildMaxHeap(p, len);
	for (int i = len-1; i > 0; i--) {
		swap(&p[i], &p[0]);
		len--;
		maxHeap(p, len, 0);
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

	
	heapSort(a, 100);
	
	printf("after:");
	printA(a, 100);
	
}
