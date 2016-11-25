//#include<iostream>
//#include<time.h>
//
//using namespace std;
//
//template <class T>
//class HashTable {
//
//private:
//	T *pArr;
//	int nSize;
//	T EMPTY;									//为空
//	T TOMB;										//墓碑
//	int nCount;
//	int hFun(T key) { return key % nSize; }		//散列函数
//	int hDoubel(T key) {						//双散列函数
//		int h1 = key % nSize;
//		int h2 = key % nSize + 1;
//		return (h1 + h2) % nSize;
//	}
//	int p(T key, int i) { return i; }				//探查函数
//
//public:
//	HashTable(int count, T empty, T tomb);
//	~HashTable() { delete pArr; }
//	bool HashInsert(T value);
//	bool HashSearch(T value);
//	T HashDelete(const T value);
//	int Count() { return nCount; }
//};
//
//template<class T>
//HashTable<T>::HashTable(int size, T empty, T tomb) {
//
//	nSize = size;
//	pArr = new T[nSize];
//	nCount = 0;
//	EMPTY = empty;
//	TOMB = tomb;
//
//	for(int i = 0; i < nSize; i++) {
//
//		pArr[i] = EMPTY;
//	}
//}
//
//template<class T>
//bool HashTable<T>::HashInsert(T value) {
//
//	int key = hFun(value);
//	int nPos = key;
//	int FirstTombPos;
//	bool tombPos = false;
//	int i = 0;
//
//	while(pArr[nPos] != EMPTY) {
//
//		if(pArr[nPos] == value){
//
//			return false;
//		}
//
//		if(pArr[nPos] == TOMB && tombPos == false) {
//
//			FirstTombPos = nPos;
//			tombPos = true;
//		}
//		i++;
//		nPos = (key + p(key, i)) % nSize;
//	}
//
//	if(tombPos == false) {
//
//		pArr[nPos] = value;
//	} else {
//
//		pArr[FirstTombPos] = value;
//	}
//
//	return true;
//}


#include<iostream>
using namespace std;

class HashTable {

private:
	int nSize;
	int *pArr;

public:
	HashTable(int n);
	~HashTable();
	int HashFun(int nValue);
	void Insert(int nValue);
	int Search(int nValue);
	void Delete(int nValue);
	void Change(int nValue, int nToValue);
	void Print();
};


HashTable::HashTable(int n) {

	nSize = n;
	pArr = new int[nSize];

	for (int i = 0; i < nSize; i++) {
		pArr[i] = -1;
	}
}

HashTable::~HashTable() {

	delete[] pArr;
	pArr = NULL;
	nSize = 0;
}

int HashTable::HashFun(int nValue) {

	return nValue % 10;
}

void HashTable::Insert(int nValue) {

	int nPos = HashFun(nValue);

	while(pArr[nPos] != -1) {
		nPos = (nPos + 1) % nSize;
	}

	pArr[nPos] = nValue;
}

int HashTable::Search(int nValue) {

	int nPos = HashFun(nValue);
	
	for (int i = nPos; pArr[i] != -1; i = (i+1) % nSize) {
		
		if(pArr[i] == nValue) {

			return i;
		}
	}
	return -1;
}

void HashTable::Delete(int nValue) {

	if(Search(nValue) == -1) {
		cout << "表中不存在该数据" << endl;
	}

	int nPos = Search(nValue);
	pArr[nPos] = -1;

	int nextPos = (nPos + 1) % nSize;

	while (pArr[nextPos] != -1) {
		
		int reInsert = pArr[nextPos];
		pArr[nextPos] = -1;
		Insert(reInsert);
		nextPos = (nextPos+1) % nSize;
	}
}

void HashTable::Change(int nValue, int nToValue) {

	int nPos = Search(nValue);
	
	if(pArr[nPos] == -1) {
		cout << "未找到该数据， 无法修改" << endl;
		return;
	}

	pArr[nPos] = nToValue;
}

void HashTable::Print() {

	for(int i = 0; i < nSize; i++) {	
		cout << pArr[i] << "	";  
	}
} 

int main() {


	HashTable h(10);
	int data[] = {3, 13, 23, 1, 11, 21};
	for (int i = 0; i < 6; i++) {
		h.Insert(data[i]);
		//h.Print();
		//puts("");
	}

	/*h.Delete(3);
	h.Print();
	puts("");

	h.Delete(13);
	h.Print();
	puts("");

	h.Delete(23);
	h.Print();
	puts("");

	h.Delete(21);
	h.Print();
	puts("");

	h.Delete(1);
	h.Print();
	puts("");*/
	h.Print();
	puts("");
	puts("");


	cout << h.Search(21);
	puts("");
	h.Delete(23);
	h.Print();
	h.Change(21, 22);
	h.Print();
	puts("");
	cout << h.Search(22);
	return 0;
}
