#include<iostream>
using namespace std;

class LinkNode {

private:
	friend class LinkList;
	int nValue;
	LinkNode *pNext;

public:
	LinkNode(int value = 0) : nValue(value) { pNext = NULL; }
	~LinkNode() { pNext = NULL; }
};

class LinkList {

private:
	LinkNode *pHead;

public:
	LinkList();
	~LinkList();
	void Insert(int nData);
	void Delete(int nData);
	bool IsEmpty();
	void Reverse();
	void Destroy();
	int Length();
	LinkNode* Find(int nData);
	void Print();
};

LinkList::LinkList() {

	pHead = new LinkNode();
}

LinkList::~LinkList() {

	Destroy();
}

void LinkList::Insert(int nData) {

	if(pHead == NULL) {

		cout << "链表未创建" << endl;
		return;
	}

	LinkNode *pCur = pHead;
	
	while(pCur->pNext != NULL) {
		
		if(pCur->pNext->nValue < nData) {

			break;
		}
		pCur = pCur->pNext;
	}
	LinkNode *pTmp = new LinkNode(nData);
	pTmp->pNext = pCur->pNext;
	pCur->pNext = pTmp;
}

void LinkList::Delete(int nData) {

	if(pHead == NULL) {

		cout<<"链表未创建!"<<endl;
        return;
	}

	if(pHead->pNext == NULL) {

		cout<<"链表为空!"<<endl;
        return;
	}

	LinkNode *pCur = pHead;
	
	while(pCur->pNext) {

		if(pCur->pNext->nValue == nData) {

			LinkNode *pDel = pCur->pNext;
			pCur->pNext = pCur->pNext->pNext;
			pDel->pNext = NULL;
			delete(pDel);
		}
		pCur = pCur->pNext;
	}
}


bool LinkList::IsEmpty() {

	if(pHead == NULL) {
      
		cout<<"链表未创建!"<<endl;
        return false;
    }

	return pHead->pNext == NULL;
}

int LinkList::Length() {

	if (pHead == NULL) {
        
		cout<<"链表未创建!"<<endl;
        return 0;
    }

	int nLength = 0;
	LinkNode *pCur = pHead->pNext;

	while(pCur) {

		nLength++;
		pCur = pCur->pNext;
	}

	return nLength;
}

void LinkList::Reverse() {

	if(pHead == NULL) {
     
		cout<<"链表未创建!"<<endl;
    }

    if(pHead->pNext == NULL) {

        cout<<"链表为空!"<<endl;
	} else {

		LinkNode *pCur = pHead->pNext->pNext;
		LinkNode *pPre = pHead->pNext;
		LinkNode *pNext = NULL;

		while(pCur) {

			pNext = pCur->pNext;
			pCur->pNext = pPre;
			pPre = pCur;
			pCur = pNext;
		}

		pHead->pNext->pNext = NULL;
		pHead->pNext = pPre;
	}
}

void LinkList::Destroy() {

	if(pHead == NULL) {
      
		cout<<"链表未创建!"<<endl;
        return;
    }

	while(pHead->pNext) {

		LinkNode *pDel = pHead->pNext;
		pHead->pNext = pDel->pNext;
		delete pDel;
	}

	delete pHead;
	pHead = NULL;
}

LinkNode* LinkList::Find(int nData) {

	if(pHead == NULL) {
        
		cout<<"链表未创建!"<<endl;
        return NULL;
    }

    if(pHead->pNext == NULL) {
       
		cout<<"链表为空!"<<endl;
        return NULL;
    }

	LinkNode *pCur = pHead->pNext;
	
	while(pCur != NULL)	{

		if(pCur->nValue == nData) {

			return pCur;
		}

		pCur = pCur->pNext;
	}

	return NULL;
}

void LinkList::Print() {

	if(pHead == NULL) {

        cout<<"链表未创建!"<<endl;
        return;
    }

    if(pHead->pNext == NULL) {

        cout<<"链表为空!"<<endl;
        return;
	} else {

		LinkNode *pCur = pHead->pNext;
		
		while(pCur) {

			cout << pCur->nValue << " ";
			pCur = pCur->pNext;
		}
		cout << endl;
	}
}


int main()
{
    LinkList list;
    list.Insert(12);
    list.Insert(14);
    list.Insert(2);
    list.Insert(4);
    list.Insert(5);
    list.Insert(4);
    list.Insert(7);
    list.Print();
    list.Delete(5);
    list.Print();
    list.Destroy();
    list.Print();
    
	system("pause");
    return 0;
}
