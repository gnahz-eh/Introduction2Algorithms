#include<iostream>
#include<stdlib.h>
#include<string.h>

enum direction
{ up, left, leftUp };

void lcs_length(char *x, char *y, int m, int n, int c[][7], int b[][7]) {

	for(int i = 0; i < m; i++) {
		c[i][0] = 0;
	}

	for(int j = 0; j < n; j++) {
		c[0][j] = 0;
	}

	for(int i = 1; i < m; i++) {

		for(int j = 1; j < n; j++) {

			if(x[i] == y[j]) {
				c[i][j] = 1 + c[i-1][j-1];
				b[i][j] = leftUp;

			} else if(c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j] = up;
			} else {
				c[i][j] = c[i][j-1];
				b[i][j] = left;
			}
		}
	}
}

void print_lcs(int b[][7], char *x, int i, int j) {

	if(i == 0 || j == 0){
		return;
	}

	if(b[i][j] == leftUp) {
		print_lcs(b, x, i-1, j-1);
		printf("%c", x[i]);
	} else if(b[i][j] = up) {
		print_lcs(b, x, i-1, j);
	} else {
		print_lcs(b, x, i, j-1);
	}
}

void main() {
	
	char *x = "0abcdefg";
	char *y = "0bcdell";
	int m = strlen(x);
	int n = strlen(y);
	std::cout << m << n << std::endl;
	/*int **c = (int **)malloc(sizeof(int) * m * n);
	int **b = (int **)malloc(sizeof(int) * m * n);*/

	int c[8][7];
	int b[8][7];
	lcs_length(x, y, m, n, c, b);

	print_lcs(b, x, m-1, n-1);
	
	puts("");
	std::cout << "cshuzuwei" << std::endl;
	
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d", c[i][j]);
		}
		puts("");
	}

	system("pause");
}
