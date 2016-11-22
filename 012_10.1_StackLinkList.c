#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {

	int nValue;
	struct Stack *pNext;

}Stack, *PStack;

PStack CreateStack() {

	PStack pStack = (PStack)malloc(sizeof(Stack));
	pStack->nValue = 0;
	pStack->pNext = NULL;

	return pStack;
}

bool IsEmpty(PStack pStack) {

	if (NULL == pStack) {

		printf("栈未创建成功!\n");
	}

	return pStack->pNext == NULL;
}

PStack Push(PStack pStack, int nValue) {

	if(NULL == pStack) {

		printf("栈未创建成功!\n");
		return NULL;
	}

	PStack pTmp = (PStack)malloc(sizeof(Stack));
	pTmp->nValue = nValue;
	pTmp->pNext = pStack->pNext;
	pStack->pNext = pTmp;

	return pStack;
}

int Pop(PStack pStack) {

	if(NULL == pStack) {
		printf("栈未创建成功!\n");
	}

	PStack pTmp = pStack->pNext;
	pStack->pNext = pTmp->pNext;

	int nValue = pTmp->nValue;
	free(pTmp);
	pTmp = NULL;

	return nValue;
}

void Destroy(PStack pStack) {

	while (!IsEmpty(pStack)) {
		
		Pop(pStack);
	}

	free(pStack);
	pStack = NULL;
}

void main()
{
    PStack pStack = CreateStack();
    
    for (int i = 0; i < 15; i++)
    {
        pStack = Push(pStack, i);
    }

    while (!IsEmpty(pStack))
    {
        printf("%d ", Pop(pStack));
    }
    
    Destroy(pStack);
}
