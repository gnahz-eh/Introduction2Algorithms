#include<iostream>
#include<string>

using std::string;

void nativeStringMatcher(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();

	for (int s = 0; s <= n-m+1; s++) {
		string temp = text.substr(s, m);
		if (pattern == temp) {
			std::cout << "在位置" << s << "处发现匹配" << std::endl; 
		}
	}
}


void main() {

	string text("acaabcsdfgaabasd");
	string pattern("aab");
	nativeStringMatcher(text, pattern);


}
