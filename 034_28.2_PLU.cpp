#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4

template<class T>
struct ThreeM
{
	T P[N][N];
	T L[N][N];
	T U[N][N];
};

template<typename T>
void printA(T a[][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%4.1f ", a[i][j]);
		}
		printf("\n");
	}
}

template<typename T>
void exchange(T *a, T *b) {
	T temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

template<typename T>
ThreeM<T> *PLU(T a[][N]) {
	double p = 0;
	int kStar;

	int *pi = (int *)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++)
	{
		pi[i] = i;
	}

	for (int k = 0; k < N; k++)
	{
		p = 0.0;
		for (int i = k; i < N; i++)
		{
			if (abs(a[i][k]) > p)
			{
				p = abs(a[i][k]);
				kStar = i;
			}
		}
		exchange(&pi[k], &pi[kStar]);
		for (int i = 0; i < N; i++)
		{
			exchange(&a[k][i], &a[kStar][i]);
		}
		for (int i = k+1; i < N; i++)
		{
			a[i][k] = a[i][k]/a[k][k];
			for (int j = k+1; j < N; j++)
			{
				a[i][j] = a[i][j] - a[i][k]*a[k][j];
			}
		}
	}

	ThreeM<T> *result = (ThreeM<T> *)malloc(sizeof(ThreeM<T>));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result->L[i][j] = 0;
			result->U[i][j] = 0;
			result->P[i][j] = 0;
		}
	}

	//求P
	for (int i = 0; i < N; i++)
	{
		result->P[i][pi[i]] = 1;
	}
	//求U
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			result->U[i][j] = a[i][j];
		}
	}
	//求L
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				result->L[i][j] = 1;
			} else {
				result->L[i][j] = a[i][j]-result->U[i][j];
			}
		}
	}

	return result;
}

void main() {
	
	double a[N][N] = {{2,0,2,0.6},
				   {3,3,4,-2},
				   {5,5,4,2},
				   {-1,-2,3.4,-1}};
	printf("A:\n");
	printA(a);
	puts("");
	ThreeM<double> *result = PLU(a);

	printf("P:\n");
	printA<double>(result->P);
	puts("");

	printf("L:\n");
	printA<double>(result->L);
	puts("");

	printf("U:\n");
	printA<double>(result->U);
	puts("");
}
