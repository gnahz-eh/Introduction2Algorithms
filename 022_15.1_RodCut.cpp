#include<iostream>
#include<stdlib.h>
#include<limits.h>
#define N 10

struct r_s
{
	int *r;
	int *s;
};

int  max(int a, int b) {
	return a >= b ? a : b;
}

int memoized_cut_rod_aux(int *p, int n, int *r) 
{
	int q;

	if (r[n] >= 0)
	{
		return r[n];
	}
	if (n == 0)
	{
		q = 0;	
	} 
	else 
	{
		q = INT_MIN;
		for (int i = 1; i < n; i++)
		{
			q = max(q, p[i]+memoized_cut_rod_aux(p, n-i, r));
		}
	}

	r[n] = q;
	return q;
}

int memoized_cut_rod(int *p, int n) 
{
	
	int *r = new int[N+1];
	for (int i = 0; i <= N; i++)
	{
		r[i] = INT_MIN;
	}
	return memoized_cut_rod_aux(p, n, r);
}

r_s extended_buttom_up_cut_rod(int *p, int n) {
	int *r = new int[N+1];
	int *s = new int[N+1];
	int q;
	r[0] = 0;
	s[0] = 0;
	for (int j = 1; j <= n; j++)
	{
		q = INT_MIN;
		for (int i = 1; i <= j; i++)
		{
			if (q < p[i] + r[j-i])
			{
				q = p[i] + r[j-i];
				s[j] = i;
			}
		}

		r[j] = q;
	}
	r_s rs = {r, s};
	return rs;
}

void print(int *p, int n) {
	r_s rs = extended_buttom_up_cut_rod(p, n);
	while (n > 0)
	{
		printf("%d ", rs.s[n]);
		n -= rs.s[n];
	}
}

void main() {

	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	
	printf("length = %d\n", N);
	r_s rs = extended_buttom_up_cut_rod(p, N);
	for (int i = 0; i <= N; i++)
	{
		printf("r[%d]=%d	", i, rs.r[i]);
	}
	puts("");

	for (int i = 0; i <= N; i++)
	{
		printf("s[%d]=%d	", i, rs.s[i]);
	}
	puts("");
	print(p, 7);
}
