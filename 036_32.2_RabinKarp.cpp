#include<iostream>
#include<string>
using namespace std;

//d是采取的进制系统，q是大素数用于求模运算
void RabinKarp(string text, string pattern, int d, int q) {
	int n = text.length();
	int m = pattern.length();
	int h = 1;                   //初始化为m位数字中高位数字的值 
	int p = 0;					 //pattern字符串对应的数字的值
	int t = 0;                   //text中每m个连续字符串对应的数组的值
	int i;

	//m位数字中的最高位的权值，例如10进制5位数，该值为10000 
	for (i = 0; i < m-1; i++) {
		h = (h * d) % q;
	}

	//计算p值，t0值
	for (i = 0; i < m; i++) {
		t = (t * d + (text[i] - 'a')) % q;
		p = (p * d + (pattern[i] - 'a')) % q;
	}

	for (int s = 0; s < n-m+1; s++) {

		string temp = text.substr(s, m);
		if (p == t && pattern == temp) {
			cout << "在位置" << s << "处发现匹配" << endl;
		}
		t = (d * (t - (text[s] - 'a') * h) + (text[s+m] - 'a')) % q;
	}
}

void main() {
	
	string text = "cdfjacdbebfcghdjjcb cdfjacdbebfcghdjjcb cdfjacdbebfcghdjjcb";
	string pattern = "dbebf";
	RabinKarp(text, pattern, 10, 11);
}
