#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Link {

	int nValue;
	struct Link *pPrev;
	struct Link *pNext;
} Link, *PLink;

PLink Create() {

	PLink pLink = (PLink)malloc(sizeof(Link));
	pLink->nValue = 0;
	pLink->pPrev = NULL;
	pLink->pNext = NULL;

	return pLink;
}

//按从小到大的顺序插入数据
PLink Insert(PLink pLink, int nValue) {

	if(NULL == pLink) {
      
		printf("链表未创建成功!\n");
        return NULL;
    }

	PLink pTmp = (PLink)malloc(sizeof(Link));
	pTmp->nValue = nValue;
	pTmp->pNext = NULL;
	pTmp->pPrev = NULL;

	PLink pCur = pLink;

	while(pCur->pNext != NULL && nValue >= pCur->pNext->nValue) {
		
		pCur = pCur->pNext;
	}

	if(pCur->pNext == NULL) {
		//插入到最后一个结点后面
		pTmp->pPrev = pCur;
		pCur->pNext = pTmp;
	}

	if(nValue < pCur->pNext->nValue) {

		pTmp->pNext = pCur->pNext;
		pCur->pNext->pPrev = pTmp;
		pTmp->pPrev = pCur;
		pCur->pNext = pTmp;
	}

	return pLink;
}

void Delete(PLink pLink, int nValue) {

	if (NULL == pLink) {

        printf("链表未创建成功!\n");
        return;
    }

	PLink pCur = pLink;
	bool bDel = false;

	while(pCur->pNext != NULL) {

		//将判断放在while里面是为了能删除所有等于nValue的结点
		if(pCur->pNext->nValue == nValue) {

			PLink pTmp = pCur->pNext;
			if(NULL == pTmp->pNext) {
				//删除最后一个结点
				pCur->pNext = NULL;
			} else {

				pCur->pNext = pTmp->pNext;
				pTmp->pNext->pPrev = pCur;
			}

			bDel = true;
			free(pTmp);
		} else {

			pCur = pCur->pNext;
		}
	}

	if(!bDel) {

        printf("链表中没有数据 %d，无法删除!\n", nValue);
    }
}

PLink Find(PLink pLink, int nValue) {

	PLink pCur = pLink->pNext;
	
	while(pCur->pNext != NULL) {
		
		if(pCur->nValue == nValue) {

			return pCur;
		}
		pCur = pCur->pNext;
	}

	return NULL;
}

void Print(PLink pLink) {

    if(pLink->pNext == NULL) {

        printf("链表为空!\n");
        return;
    }

    PLink pCur = pLink->pNext;

    while (pCur != NULL) {

        printf("%d ", pCur->nValue);
        pCur = pCur->pNext;
    }
}

bool IsEmpty(PLink pLink) {

    return pLink->pNext == NULL;
}

void Destroy(PLink pLink) {

	PLink pCur = pLink;
    PLink pDel = NULL;
    PLink pNext = NULL;

	while(pCur->pNext != NULL) {

		pDel = pCur->pNext;
		
		if(NULL == pDel->pNext) {

			pCur->pNext == NULL;
		} else {

			pDel->pNext->pPrev = pCur;
			pCur->pNext = pDel->pNext;
		}

		free(pDel);
		printf("\n");
        Print(pLink);
	}
	free(pLink);
}

int main()
{
    PLink pLink = Create();
    pLink = Insert(pLink, 1);
    pLink = Insert(pLink, 5);
    pLink = Insert(pLink, 8);
    pLink = Insert(pLink, 4);
    pLink = Insert(pLink, 4);
	Print(pLink);
    Delete(pLink, 4);
	puts("");
	Print(pLink);
//
////    if (NULL != Find(pLink, 4))
////    {
////        printf("链表中有该数据!\n");
////    }
////    else
////    {
////        printf("链表中没有该数据!\n");
////    }
//    Print(pLink);
//    
//   // Destroy(pLink);
	system("pause");
    return 0;
}


