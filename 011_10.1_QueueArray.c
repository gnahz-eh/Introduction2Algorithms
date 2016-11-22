#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct Queue
{
	
	int nHead;
	int nTail;
	int nLen;
	int *pnArr;
}Queue, *PQueue;

PQueue Create(int nLen) {

	if (nLen <= 0) {

		return NULL;
	}

	PQueue pQueue = (PQueue)malloc(sizeof(Queue));
	pQueue->nLen = nLen;
	pQueue->nHead = 0;
	pQueue->nTail = 0;
	pQueue->pnArr = (int *)malloc(sizeof(int) * nLen);

	return pQueue;
}

bool IsEmpty(PQueue pQueue)
{
    return pQueue->nHead == pQueue->nTail;
}

bool IsFull(PQueue pQueue)
{
    return pQueue->nTail == pQueue->nLen;
}

void EnQueue(PQueue pQueue, int nValue) {

	if (NULL == pQueue || pQueue->pnArr == NULL) {

		printf("队列未创建成功!\n");
		return;
	}

	if (IsFull(pQueue)) {

		printf("队列已满!\n");
        return;
	}

	pQueue->pnArr[pQueue->nTail] = nValue;
	pQueue->nTail++;
}

int DeQueue(PQueue pQueue) {

	if (NULL == pQueue || pQueue->pnArr == NULL) {

        printf("队列未创建成功!\n");
		exit(0);
    }

    if (pQueue->nHead == pQueue->nTail) {

        printf("队列已空!\n");
        exit(0);
    }

	int nValue = pQueue->pnArr[pQueue->nHead];
	pQueue->nHead++;

	return nValue;
}

void Destroy(PQueue pQueue)
{
    free(pQueue->pnArr);
    pQueue->pnArr = NULL;

    free(pQueue);
    pQueue = NULL;
}

void main()
{
    PQueue pQueue = Create(10);
    for (int i = 0; i < 12; i++)
    {
        EnQueue(pQueue, i);
    }

    //printf("%d \n", IsFull(pQueue));
    while (!IsEmpty(pQueue))
    {
        printf("%d ", DeQueue(pQueue));
    }
}
