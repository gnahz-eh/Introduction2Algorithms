#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits>
int len;

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

int heapMaxmum(int *p, int len) {

	if(NULL == p || 0 == len) {
		return -1;
	}
	return p[0];
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

int heapExtractMax(int *p, int len) {
	if (len < 1) {
		return -1;
	}
	int max = p[0];
	p[0] = p[len-1];
	//printf("p0 = %d ", &p[0]);
	len--;
	//printf("len =%d		", len);
	maxHeap(p, len, 0);
	return max;
}

void heapIncreaseKey(int *p, int i, int key) {
	if (key <= p[i]) {
		puts("error");
		return;
	}
	
	p[i] = key;

	while (i > 0 && p[parent(i)] < p[i]) {
		swap(&p[parent(i)], &p[i]);
		i = parent(i);
	}
}

void heapInsertKey(int *p, int key, int len) {
	
	len++;
	p[len-1] = INT_MIN;
	heapIncreaseKey(p, len-1, key);
}


void buildMaxHeap(int *p, int len) {

	for (int i = parent(len-1); i >= 0; i--) {
		maxHeap(p, len, i);
	}
}


void printA(int *p, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ", p[i]);
		/*if(i % 10 == 0) {
			puts("");
		}*/
	}
}


void main() {

	/*int i;
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
	printA(a, 100);*/

	int a[11];
	len = 9;
	int i;
	a[0] = 16;
	a[1] = 14;
	a[2] = 10;
	a[3] = 8;
	a[4] = 7;
	a[5] = 9;
	a[6] = 3;
	a[7] = 2;
	a[8] = 4;
	
	printA(a, len);
	puts("");
	puts("");
	printf("%d\n", heapMaxmum(a, len));
	printA(a, len);
	puts("");
	puts("");
	printf("%d\n", heapExtractMax(a, len));
	//printf("len = %d     ", len);
	len--;
	printA(a, len);
	puts("");
	puts("");
	heapIncreaseKey(a, 4, 99);
	printA(a, len);
	puts("");
	puts("");
	heapInsertKey(a, 100, len);
	len++;
	printA(a, len);
}
