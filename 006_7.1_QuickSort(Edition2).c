//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//void swap(int *a, int *b) {
//	/**a = *a ^ *b;
//	*b = *a ^ *b;
//	*a = *a ^ *b;*/
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//int patition(int *p, int lo, int hi) {
//	
//	int key = p[hi];
//	int i = lo - 1;
//	for (int j = lo; j < hi; j++) {
//		if(p[j] <= key) {
//			i++;
//			swap(&p[i], &p[j]);
//		}
//	}
//	swap(&p[i+1], &p[hi]);
//	return i+1;
//}
//
//void quickSort(int *p, int lo, int hi) {
//	if(lo < hi) {
//		int mid = patition(p, lo, hi);
//		quickSort(p, lo, mid-1);
//		quickSort(p, mid+1, hi);
//	}
//}
//
//
//void printA(int *p, int len) {
//	int i;
//	for(i = 0; i < len; i++) {
//		printf("%d ", p[i]);
//		if(p[i+1]!= p[i]) {
//			puts("");
//		}
//		if(i % 10 == 0) {
//			puts("");
//		}
//	}
//}
//
//
//void main() {
//
//	int i;
//	int a[100];
//	srand(time(NULL));
//	
//	for (i = 0; i < 100; i++)
//	{
//		a[i] = rand()%100;
//	}
//
//	printf("before: \n");
//	printA(a, 100);
//	puts("");
//
//	
//	quickSort(a, 0, 99);
//	
//	printf("after:hh\n");
//	printA(a, 100);
//
//	puts("");
//	int m = 2, n = 1;
//	swap(&m, &n);
//	printf("m = %d, n = %d", m, n);
//	
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include <time.h>
//
//void PrintArr(int *pnArr, int nLen)
//{
//    for (int i = 0; i < nLen; i++)
//    {
//        printf("%d ", pnArr[i]);
//    }
//    printf("\n");
//}
//
//void Swap(int *p1, int *p2)
//{
//    int nTmp = *p1;
//    *p1 = *p2;
//    *p2 = nTmp;
//}
//
////实现对子数组[nLeft - nRight]的原址重排，将主元素放到合适位置
////递增排序
//int Patition1(int *pnArr, int nLeft, int nRight)
//{
//    int nKey = pnArr[nRight];
//    int i = nLeft - 1;
//
//    for (int j = nLeft; j < nRight; j++)
//    {
//        if (pnArr[j] <= nKey)
//        {
//            i++;
//            Swap(&pnArr[i], &pnArr[j]);
//        }
//    }
//    
//    //将主元素插入到中间位置
//    Swap(&pnArr[i+1], &pnArr[nRight]);
//
//    return i+1;
//}
//
////递增排序
//int Patition2(int *pnArr, int nLeft, int nRight)
//{
//    int nKey = nRight;
//    int i = nLeft - 1;
//    bool bExchange = false;
//
//    for (int j = nLeft; j < nRight; j++)
//    {
//        if (pnArr[j] < pnArr[nKey])
//        {
//            i++;
//            Swap(&pnArr[i], &pnArr[j]);
//            bExchange = true;
//        }
//    }
//    Swap(&pnArr[i+1],&pnArr[nRight]);
//    if (bExchange)
//    {
//        return i+1;
//    }
//    else
//    {
//        return (nLeft + nRight) / 2;
//    }
//}
//
////递减排序
//int Patition3(int *pnArr, int nLeft, int nRight)
//{
//    int nKey = nRight;
//    int i = nLeft - 1;
//    for (int j = nLeft; j < nRight; j++)
//    {
//        if (pnArr[j] > pnArr[nKey])
//        {
//            i++;
//            Swap(&pnArr[i],&pnArr[j]);
//        }
//    }
//    Swap(&pnArr[i+1], &pnArr[nRight]);
//    return i + 1;
//}
//
////寻找一个nTmpPos下标，nTmpPos左边的值都小于它，右边的值都大于它
//void QuickSort(int *pnArr, int nLeft, int nRight)
//{
//    if (nLeft < nRight)
//    {
//        //分解
//        int nTmpPos = Patition1(pnArr, nLeft, nRight);
//
//        //解决/合并
//        QuickSort(pnArr, nLeft, nTmpPos - 1);
//        QuickSort(pnArr, nTmpPos + 1, nRight);
//    }
//}
//
//int main()
//{
//    int nArr[10] = {42,1,3,2,16,9,10,14,8,17}; 
//    
//    PrintArr(nArr, 10);
//    QuickSort(nArr, 0,9);
//
//    PrintArr(nArr, 10);
//    system("pause");
//    return 0;
//}


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *a, int *b) {
	/**a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;*/
	int temp = *a;
	*a = *b;
	*b = temp;
}

int patition(int *p, int lo, int hi) {
	
	int i = lo;
	int j = hi+1;
	int key = p[lo];

	while (true) {
		while(p[++i] < key) if(i == hi) break;
		while(p[--j] > key) if(lo == j) break;
		if(i >= j) break;
		swap(&p[i], &p[j]);
	}
	swap(&p[lo], &p[j]);
	return j;
}

void quickSort(int *p, int lo, int hi) {
	if(lo < hi) {
		int mid = patition(p, lo, hi);
		quickSort(p, lo, mid-1);
		quickSort(p, mid+1, hi);
	}
}


void printA(int *p, int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d ", p[i]);
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
	int a[100];
	srand(time(NULL));
	
	for (i = 0; i < 100; i++)
	{
		a[i] = rand()%50;
	}

	printf("before: \n");
	printA(a, 100);
	puts("");

	
	quickSort(a, 0, 99);
	
	printf("after:hh\n");
	printA(a, 100);

	puts("");
	int m = 2, n = 1;
	swap(&m, &n);
	printf("m = %d, n = %d", m, n);
	
}
