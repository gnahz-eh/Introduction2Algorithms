#include <limits.h>  
#include <stdlib.h>  
#include <string.h> 
#include <stdio.h>  

struct Edge {
	int u;
	int v; 
	int w;
};

struct GraphNode {
	int key;
	int w;
	GraphNode *next;
};

void graphNodeInit(GraphNode *x, int key, int w) {
	x->key = key;
	x->w = w;
	x->next = NULL;
}

struct Vertex {
	int dis;
	int parent;
	char strVertex[256];
};

void vertexInit(Vertex *v) {
	v->dis = INT_MAX;
	v->parent = -1;
	strcpy(v->strVertex, "");
}

struct Graph {
	GraphNode **adj;
	Vertex *vertexArray;
	int vNum;
	int eNum;
};

Graph *graphCreate(int vNum, char*strVertex[]) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->vNum = vNum;
	g->eNum = 0;
	g->adj = (GraphNode **)malloc(sizeof(GraphNode *) * vNum);
	g->vertexArray = (Vertex *)malloc(sizeof(Vertex) * vNum);
	for (int i = 0; i < vNum; i++) {
		g->adj[i] = NULL;
		strcpy(g->vertexArray[i].strVertex, strVertex[i]);
	}
	return g;
}

void graphInsertEdge(Graph *g, Edge e) {
	GraphNode *v = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(v, e.v, e.w);
	//从表头插入,将v插入到表头u  
    v->next = g->adj[e.u];  
    g->adj[e.u] = v;  
    ++g->eNum;
}

void graphDisplay(Graph *g) {
	printf("%d vertices,%d edges\n", g->vNum, g->eNum);
	for (int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].strVertex);
		for (GraphNode *x = g->adj[i]; x != NULL; x = x->next) {  
            printf("%s,%d ", g->vertexArray[x->key].strVertex, x->w);  
        }  
        printf("\n"); 
	}
}

void graphDisplayVertex(Graph *g) {  
    printf("各个顶点的数据:\n");  
    for (int i = 0; i < g->vNum; i++) {  
        printf("%s:%d\n", g->vertexArray[i].strVertex,  
               g->vertexArray[i].dis);  
    }  
} 

void swap(void *a, void *b, size_t elem_size) {
	if (a == NULL || b == NULL || a == b) {
		return; 
	}
	char *temp = (char *)malloc(sizeof(char) * elem_size);
	memcpy(temp, a, elem_size);
	memcpy(a, b, elem_size);  
    memcpy(b, temp, elem_size);
}


/*基于索引堆的优先队列*/ 
struct PriorityQueue {
	int heapSize;
	int *indexArray;
	int *indexPosArray;   /*这个数组记录了索引在堆中位置 */
	void *dataArray;
	size_t elemSize;
	int (*comp) (const void *, const void *);
};

int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return i * 2 + 1;
}

int right(int i) {
	return i * 2 + 2;
}

void swapIndex(PriorityQueue *pq, int i, int j) {
	swap(&pq->indexPosArray[i], &pq->indexPosArray[j], sizeof(int));
	pq->indexArray[pq->indexPosArray[i]] = i;
	pq->indexArray[pq->indexPosArray[j]] = j;
}

bool compare(PriorityQueue *pq, int left, int right) {
	if (pq->dataArray == NULL) {
		return false;
	}
	char *pcArray = (char *)pq->dataArray;
	return pq->comp(&pcArray[left * pq->elemSize], &pcArray[right * pq->elemSize]) > 0;
}

void heapify(PriorityQueue *pq, int i) {
	int l = left(i);
	int r = right(i);
	int largest = i;
	if (l < pq->heapSize && compare(pq, pq->indexArray[largest], pq->indexArray[l])) {
		largest = l;
	}
	if (r < pq->heapSize && compare(pq, pq->indexArray[largest], pq->indexArray[r])) {
		largest = r;
	}
	if (largest != i) {
		swapIndex(pq, pq->indexArray[i], pq->indexArray[largest]);
		heapify(pq, largest);
	}
}

void fixUp(PriorityQueue *pq, int i) {
	while (i > 0 && compare(pq, pq->indexArray[parent(i)], pq->indexArray[i])) {
		swapIndex(pq, pq->indexArray[parent(i)], pq->indexArray[i]);  
        i = parent(i);
	}
}

PriorityQueue *priorityQueueCreate(void *pDataArray, size_t elem_size, int length, int (*comp)(const void *, const void *)) {
	PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	pq->indexArray = (int *)malloc(sizeof(int) * length);
	pq->indexPosArray = (int *)malloc(sizeof(int) * length);
	pq->dataArray = pDataArray;
	pq->elemSize = elem_size;
	pq->heapSize = 0;
	pq->comp = comp;
	return pq;
}

int priorityQueueExtractTop(PriorityQueue *pq) {
	swapIndex(pq, pq->indexArray[0], pq->indexArray[pq->heapSize - 1]);
	--pq->heapSize;
	heapify(pq, 0);
	return pq->indexArray[pq->heapSize];
}

void priorityQueueInsert(PriorityQueue *pq, int index) {
	++pq->heapSize;
	int i = pq->heapSize - 1;
	pq->indexArray[i] = index;
	pq->indexPosArray[index] = i;
	fixUp(pq, i);
}

bool priorityQueueIsEmpty(PriorityQueue *pq) {
	return pq->heapSize == 0;
}
/*?*/
void priorityQueueChangeIndex(PriorityQueue *pq, int index) {
	fixUp(pq, pq->indexPosArray[index]);
	//heapify(pq, pq->indexPosArray[index]);
}

int cmpVertex(const void *p1, const void *p2) {
	const Vertex *pa = (Vertex *)p1;
	const Vertex *pb = (Vertex *)p2;
	if(pa->dis < pb->dis) {
		return -1;
	}
	if (pa->dis == pb->dis) {
		return 0;
	}
	return 1;
}

void initializeSingleSource(Graph *g, int s) {
	for (int i = 0; i < g->vNum; i++) {
		g->vertexArray[i].dis = INT_MAX;
		g->vertexArray[i].parent = -1;
	}
	g->vertexArray[s].dis = 0;
}

void relax(Graph *g, int u, int v, int w) {
	int dis = g->vertexArray[u].dis == INT_MAX ? INT_MAX : g->vertexArray[u].dis + w;
	if (g->vertexArray[v].dis > dis) {
		g->vertexArray[v].dis = dis;
		g->vertexArray[v].parent = u;
	}
}

void Dijkstra(Graph *g, int s) {
	initializeSingleSource(g, s);
	PriorityQueue *pq = priorityQueueCreate(g->vertexArray, sizeof(Vertex), g->vNum, cmpVertex);
	
	for (int i = 0; i < g->vNum; i++) {
		priorityQueueInsert(pq, i);
	}
	priorityQueueChangeIndex(pq, s);
	while (!priorityQueueIsEmpty(pq)) {
		int u = priorityQueueExtractTop(pq);
		for (GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
			int v = x->key;
			relax(g, u, v, x->w);
			priorityQueueChangeIndex(pq, v);
		}
	}
}

void main()  
{  
    //数据根据书上的图24-6  
    char *str_vertex[5] = { "s", "t", "x", "y", "z" };  
    Graph *g = graphCreate(5, str_vertex);  
    Edge edges[] =  
        { {0, 1, 10}, {0, 3, 5}, {1, 2, 1}, {1, 3, 2}, {2, 4, 4}, {3, 1, 3},  
    {3, 4, 2}, {3, 2, 9}, {4, 0, 7}, {4, 2, 6}  
    };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        graphInsertEdge(g, edges[i]);  
    }  
    graphDisplay(g);  
    Dijkstra(g, 0);  
    graphDisplayVertex(g);  
}  
