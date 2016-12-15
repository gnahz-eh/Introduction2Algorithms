#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct TwoM {
	int l[4][4];
	int u[4][4];
};

struct OneM 
{
	int c[4][4];
};

void printA(int a[][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}
}

OneM *multipal(int a[][4], int b[][4]) {
	OneM *temp = (OneM *)malloc(sizeof(OneM));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				temp->c[i][j] += a[i][k]*b[k][j]; 
			}
		}
	}
	return temp;
}

TwoM *LU(int a[][4]) {
	TwoM *lu = (TwoM *)malloc(sizeof(TwoM));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			lu->u[i][j] = 0;
			if(i == j) lu->l[i][j] = 1;
			else lu->l[i][j] = 0;
		}
	}

	for (int k = 0; k < 4; k++)
	{
		lu->u[k][k] = a[k][k];
		for (int i = k+1; i < 4; i++)
		{
			lu->l[i][k] = a[i][k]/lu->u[k][k];
			lu->u[k][i] = a[k][i];
		}

		for (int i = k+1; i < 4; i++)
		{
			for (int j = k+1; j < 4; j++)
			{
				a[i][j] = a[i][j]-lu->l[i][k]*lu->u[k][j];
			}
		}
	}

	return lu;
}


void main() {
	
	int a[4][4] = {{2,3,1,5},
				   {6,13,5,19},
				   {2,19,10,23},
				   {4,10,11,31}};
	printf("A:\n");
	printA(a);
	puts("");
	TwoM *result = LU(a);
	printf("L:\n");
	printA(result->l);
	puts("");
	printf("U:\n");
	printA(result->u);
	puts("");
}
