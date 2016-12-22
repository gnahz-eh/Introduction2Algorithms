#include<iostream>
#include<string>
using namespace std;

void computePrefixFunction(string pattern, int *pi) {
	
	int m = pattern.length();
	pi[0] = 0;
	int k = 0;
	
	for (int q = 1; q < m; q++) {
		while (k > 0 && pattern[k] != pattern[q])
			k = pattern[k-1];
		if (pattern[k] == pattern[q]) 
			k++;
		pi[q] = k;
	}

	cout << "计算的前缀数组为： " << endl;
	for (int i = 0; i < m; i++)
		cout << pi[i] << " ";
	cout << endl;
}

void KMP(string text, string pattern) {
	
	int n = text.length();
	int m = pattern.length();

	int *pi = new int[m];
	computePrefixFunction(pattern, pi);

	int q = 0;
	for (int i = 0; i < n; i++) {

		while (q > 0 && pattern[q] != text[i])
			q = pi[q-1];
		if (pattern[q] == text[i])
			q++;
		if (q == m-1) {
			cout << "pattern occurs with shift" << i-m+1 << endl;
			q = pi[q];
		}
	}
}

void main() {
	
	string text = "cdfjacdbebfcghdjjcbasdfajhfrafaodbebfcdfjacdbebfcghdjjcbadjlkacaoidbebfnqlknrlkndsadanflkjajuaqdbebfdqlihrwfdankjsafdbebfcdfjacdbebfcghdjjcb";
	string pattern = "dbebf";

	KMP(text, pattern);
	
}
