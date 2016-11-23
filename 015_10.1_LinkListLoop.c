#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct LoopLink {
	
	int nValue;
	struct LoopLink *pNext;
} LoopLink, *PLoopLink;

PLoopLink Create() {

	PLoopLink pHead = (PLoopLink)malloc(sizeof(LoopLink));
	
	if(NULL == pHead) {
    
		printf("分配内存失败!\n");
    }

	pHead->nValue = INT_MIN;
	pHead->pNext = pHead;

	return pHead;
}

void Insert(PLoopLink pHead, int nValue) {

	if(NULL == pHead) {
      
		printf("链表未创建成功!\n");
        return ;
    }

	PLoopLink pCur = pHead;
	PLoopLink pTmp = (PLoopLink)malloc(sizeof(LoopLink));
	pTmp->nValue = nValue;
	pTmp->pNext = NULL;

	while(pCur->pNext != pHead) {
		
		if(pCur->pNext->nValue > nValue) {

			break;
		}
		pCur = pCur->pNext;
	}

	pTmp->pNext = pCur->pNext;
	pCur->pNext = pTmp;
}

void Delete(PLoopLink pHead, int nValue) {

	if(pHead == NULL) {
        
		printf("链表未创建成功!\n");
        return;
    }

	PLoopLink pCur = pHead;
	
	while(pCur->pNext != pHead) {

		if(pCur->pNext->nValue == nValue) {

			PLoopLink pTmp = pCur->pNext;
			pCur->pNext = pTmp->pNext;
			free(pTmp);
			pTmp = NULL;
		}

		pCur = pCur->pNext;
	}
}

PLoopLink Find(PLoopLink pHead, int nValue) {

	if(pHead == NULL) {
        printf("链表未创建成功!\n");
        return NULL;
    }
	PLoopLink pCur = pHead;

	while(pCur->pNext != pHead) {
		
		if(pCur->pNext->nValue == nValue) {
			return pCur->pNext;
		}
		pCur = pCur->pNext;
	}

	return NULL;
}

bool IsEmpty(PLoopLink pHead) {

	if(NULL == pHead) {

		printf("链表未创建成功!\n");
	}

	return pHead == pHead->pNext;
}

void Print(PLoopLink pHead) {

	if (pHead == NULL) {

        printf("链表未创建成功!\n");
        return;
    }

    if (pHead->pNext == pHead) {

        printf("链表为空!\n");
        return;
    }

	PLoopLink pCur = pHead->pNext;
	
	while (pCur != pHead) {

		printf("%d ", pCur->nValue);
        pCur = pCur->pNext;
	}

	printf("\n");
}

int main()
{
    PLoopLink pHead = Create();
   // printf("%d\n", IsEmpty(pHead));
    Insert(pHead, 1);
    Insert(pHead, 5); 
    Insert(pHead, 8);
    Insert(pHead, 4);
    Insert(pHead, 0);
	Print(pHead);

    if (NULL != Find(pHead, 2))
    {
        printf("链表中有该数据!\n");
    }
    else
    {
         printf("链表中没有该数据!\n");
    }
    
    Delete(pHead, 4);
    Print(pHead);
    system("pause");

    return 0;
}
