#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void printArr(int *p, int len) {
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

void Swap(int *p1, int *p2)
{
    int nTmp = *p1;
    *p1 = *p2;
    *p2 = nTmp;
}


int partition(int *p, int lo, int hi) {

	int key = p[hi];
	int i = lo - 1;
	for (int j = lo; j < hi; j++)
	{
		if (p[j] < key) {
			i++;
			Swap(&p[i], &p[j]);
		}
	}

	Swap(&p[i+1], &p[hi]);
	return i+1;
}

int randomPartition(int *p, int lo, int hi) {
	
	srand(time(NULL));
	int i = rand() % (hi - lo + 1) + lo;
	Swap(&p[i], &p[hi]);
	return partition(p, lo, hi);
}

int randomSelect(int *p, int lo, int hi, int rank) {//数组中第rank小的数，即有rank-1个数小于他

	if(lo == hi) {
		return p[lo];
	}

	int mid = randomPartition(p, lo, hi);
	int leftCount = mid - lo + 1;
	if (leftCount == rank) {
			return p[mid];
	} else if(leftCount > rank) {
		return randomSelect(p, lo, mid-1, rank);
	} else {
		return randomSelect(p, mid+1, hi, rank-leftCount);
	}
}
void quickSort(int *p, int lo, int hi) {
	if(hi <= lo) return;
	int lt = lo, i = lo + 1, gt = hi;
	int key = p[lo];
	while (i <= gt) {
		if(p[i] < key) Swap(&p[lt++], &p[i++]);
		else if(p[i] > key) Swap(&p[gt--], &p[i]);
		else i++;
	}

	quickSort(p, lo, lt-1);
	quickSort(p, gt+1, hi);
}

void main()
{
    int nArr[10] = {0,2,1,2,2,6,9,7,4,12};//	0 ~ 9 

    printArr(nArr, 10);
    printf("第5最小元素的值为%d\n", 
		randomSelect(nArr, 0, 9, 5));

	quickSort(nArr, 0, 9);
	printArr(nArr, 10);
    system("pause");
}
