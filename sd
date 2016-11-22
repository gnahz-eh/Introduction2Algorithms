#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Stack {

	int nTop;
	int nLen;
	int *pnArr;
} Stack, *PStack;


//初始化栈 nLen为栈的大小
PStack Create(int nLen) {
	
	if (nLen <= 0) {

		return NULL;
	}

	PStack pStack = (PStack)malloc(sizeof(Stack));
	pStack->nTop = 0;
	pStack->nLen = nLen;
	pStack->pnArr = (int *)malloc(sizeof(int) * nLen);

	return pStack;
}

bool IsEmpty(PStack pStack) {

	return pStack->nTop == 0;
}

bool IsFull(PStack pStack) {

	return pStack->nTop == pStack->nLen;
}

void Push(PStack pStack, int nValue) {

	if (IsFull(pStack)) {

		printf("栈已满!\n");
		return;
	}
	pStack->pnArr[pStack->nTop] = nValue;
	pStack->nTop++;
}

int Pop(PStack pStack) {

	if (IsEmpty(pStack))
	{
		printf("栈为空!\n\n");
		exit(0);
	} else {

		pStack->nTop--;
		return pStack->pnArr[pStack->nTop];
	}
}

void Destroy(PStack pStack) {

	free(pStack->pnArr);
	pStack->pnArr = NULL;
	free(pStack);
	pStack = NULL;
}

void main()
{
    PStack pStack = Create(10);
    int i;
    for (i = 0; i < 12; i++)
    {
        Push(pStack, i);
    }

    for (i = 0; i < 12; i++)
    {

        printf("%d ", Pop(pStack));
    }

    
    Destroy(pStack);
}
