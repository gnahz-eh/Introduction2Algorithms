#include<iostream>

using namespace std;

struct Node {
		
	int nValue;
	Node *pNext;
};

class HashTable {

private:
	Node **pArr;		//指针数组
	int nSize;


public:
	HashTable(int n);
	~HashTable();
	void Insert(int nValue);
	void InsertList(Node *pHead, int nValue);
	void Delete(int nValue);
	void DeleteList(Node *pHead, int nValue);
	int Search(int nValue);
	int HashFun(int nValue);
	void Print();
	void DestroyList(Node *pHead);
};


HashTable::HashTable(int n) {

	nSize = n;
	pArr = new Node*[nSize];	//每个元素的类型都是Node*
	for(int i = 0; i < nSize; i++)
	{
		pArr[i] = new Node;
		pArr[i]->pNext = NULL;
	}
}

void HashTable::DestroyList(Node *pHead) {

	Node *pDel = NULL;
	while(pHead->pNext) {
		
		pDel = pHead->pNext;
		pHead->pNext = pDel->pNext;
		delete pDel;
	}
	
	delete pHead;
	pHead = NULL;
}

HashTable::~HashTable() {

	for(int i = 0; i < nSize; i++) {

		DestroyList(pArr[i]);
	}

	pArr = NULL;
}

int HashTable::HashFun(int nValue) {

	return nValue % 10;
}

void HashTable::InsertList(Node *pHead, int nValue) {

	Node *pCur = pHead;
	Node *pTmp = new Node;
	pTmp->nValue = nValue;
	pTmp->pNext = NULL;

	while(pCur->pNext) {

		if(nValue < pCur->pNext->nValue)
		{
			pTmp->pNext = pCur->pNext;
			pCur->pNext = pTmp;
			return;
		} else if(nValue == pCur->pNext->nValue) {
			
			return;
		} else {

			pCur = pCur->pNext;
		}
	}

	pCur->pNext = pTmp;
}

void HashTable::Insert(int nValue) {

	int nPos = HashFun(nValue);
	Node *pTmp = new Node;
	pTmp->nValue = nValue;
	pTmp->pNext = NULL;

	if(pArr[nPos]->pNext == NULL) {
		
		pArr[nPos]->pNext = pTmp;
	} else {

		InsertList(pArr[nPos], nValue);
	} 
}

void HashTable::DeleteList(Node *pHead, int nValue) {

	Node *pCur = pHead;
	while(pCur->pNext) {

		if(pCur->pNext->nValue == nValue) {

			Node *pDel = pCur->pNext;
			pCur->pNext = pDel->pNext;
			delete pDel;
			return;
		} else {

			pCur = pCur->pNext;	
		}
	}
}

void HashTable::Delete(int nValue) {

	if( -1 == Search(nValue)) {

		cout << "哈希表中没有该数据" << endl;
		return;
	}

	int nPos = HashFun(nValue);
	DeleteList(pArr[nPos], nValue);
}

int HashTable::Search(int nValue) {

	int nPos = HashFun(nValue);

	if(pArr[nPos]->pNext == NULL) {
		
		return -1;
	} else {
		
		Node *pCur = pArr[nPos]->pNext;
		
		while(pCur) {

			if(pCur->nValue == nValue) {
					
				return pCur->nValue;
			} else {
				
				pCur = pCur->pNext;
			}
		}

		return -1;
	}
}

void HashTable::Print() {
	
	for(int i = 0; i < nSize; i++) {

		Node *pCur = pArr[i]->pNext;
		
		while(pCur) {

			cout << pCur->nValue << "	";
			pCur = pCur->pNext;
		}

		cout << endl;
	}
}


int main()
{
	int nArr[] = {1,23,4,6,7,8,0,23,12,4556,34,2,23,5456,783,23,12,556,784,24,12};
	int nLen = sizeof(nArr) / sizeof(int);
	HashTable hTable(10);
	for (int i = 0; i < nLen; i++)
	{
		hTable.Insert(nArr[i]);
	}
	//cout<<hTable.Search(122)<<endl;

	
	hTable.Print();

	hTable.Delete(4);
	puts("");

	hTable.Print();
	system("pause");
	return 0;
}
