#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

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
	bool inQueue;
	char strVertex[256];
};

void vertexInit(Vertex *v) {
	v->dis = INT_MAX;
	v->parent = -1;
	v->inQueue = false;
	strcpy(v->strVertex, "");
}

struct Graph {
	GraphNode **adj;
	Vertex *vertexArray;
	int vNum;
	int eNum;
};

Graph *graphCreate(int vNum, char *strVertex[]) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->vNum = vNum;
	g->eNum = 0;
	g->adj = (GraphNode **)malloc(sizeof(GraphNode*) * vNum);
	g->vertexArray = (Vertex *)malloc(sizeof(Vertex) * vNum);
	for(int i = 0; i < vNum; i++) {
		g->adj[i] = NULL;
		strcpy(g->vertexArray[i].strVertex, strVertex[i]);
	}
	return g;
}

void insertEdge(Graph *g, Edge e) {
	GraphNode *u = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(u, e.u, e.w);
	GraphNode *v = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(v, e.v, e.w);
	//从表头插入,将v插入到表头u  
    v->next = g->adj[e.u];  
    g->adj[e.u] = v; 
	//从表头插入,将u插入到表头v  
	u->next = g->adj[e.v];  
    g->adj[e.v] = u;  
    ++g->eNum;
}

void graphDisplay(Graph *g) {
	printf("%d vertices,%d edges\n", g->vNum, g->vNum);
	for(int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].strVertex);
	    for (GraphNode *x = g->adj[i]; x != NULL; x = x->next) {  
            printf("%s,%d ", g->vertexArray[x->key].strVertex, x->w);  
        }  
        printf("\n"); 
	}
}

void swap(void *a, void *b, size_t elem_size)  
{  
    if (a == NULL || b == NULL || a == b)  
        return;  
    char *temp = (char *)malloc(sizeof(elem_size));   /*变长数组 */  
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
	size_t elem_size;  
    int (*comp) (const void *, const void *);
};

int parent(int i) {  
    return (i - 1) / 2;  
}  
  
int leftChild(int i) {  
    return i * 2 + 1;  
}  
  
int rightChild(int i) {  
    return i * 2 + 2;  
} 

void swapIndex(PriorityQueue *pq, int i, int j) {  
	swap(&pq->indexPosArray[i], &pq->indexPosArray[j], sizeof(int));  
    pq->indexArray[pq->indexPosArray[i]] = i;  
    pq->indexArray[pq->indexPosArray[j]] = j;  
}

/*最小堆用的比较函数*/  
bool compare(PriorityQueue *pq, int left, int right) {  
    if (pq->dataArray == NULL)  
        return false;  
    char *pc_array = (char *)pq->dataArray;  
    return pq->comp(&pc_array[left * pq->elem_size],  
            &pc_array[right * pq->elem_size]) > 0;  
}

void heapify(PriorityQueue *pq, int i) {
	int left = leftChild(i);
	int right = rightChild(i);
	int largest = i;
	if (left < pq->heapSize  
        && compare(pq, pq->indexArray[largest], pq->indexArray[left])) {  
        largest = left;  
    }  
    if (right < pq->heapSize  
        && compare(pq, pq->indexArray[largest], pq->indexArray[right])) {  
        largest = right;  
    }
	if (largest != i) {  
        swapIndex(pq, pq->indexArray[i], pq->indexArray[largest]);  
        heapify(pq, largest);  
    }  
}

void fixUp(PriorityQueue *pq, int i) {  
    while (i > 0  
           && compare(pq, pq->indexArray[parent(i)], pq->indexArray[i])) {  
        swapIndex(pq, pq->indexArray[parent(i)], pq->indexArray[i]);  
        i = parent(i);  
    }  
}

PriorityQueue *priorityQueueCreate(void *pDataArray, 
								   size_t elem_size, 
								   int length, 
								   int (*comp) (const void *, const void *)) {  
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));  
    pq->indexArray = (int *)malloc(sizeof(int) * length);  
    pq->indexPosArray = (int *)malloc(sizeof(int) * length);  
    pq->dataArray = pDataArray;  
    pq->elem_size = elem_size;  
    pq->heapSize = 0;  
    pq->comp = comp;  
    return pq;  
} 

int priorityQueueTop(PriorityQueue *pq) {  
    return pq->indexArray[0];  
}

/*去掉并返回堆的第一个元素 */  
int priorityQueueExtractTop(PriorityQueue *pq) {  
    swapIndex(pq, pq->indexArray[0], pq->indexArray[pq->heapSize - 1]);  
    --pq->heapSize;  
    heapify(pq, 0);  
    return pq->indexArray[pq->heapSize];  
}

/*把元素的索引插入队列 */  
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

/*下标为index的数据修改了，调用这个函数来修复索引堆*/  
void priorityQueueChangeIndex(PriorityQueue *pq, int index)  
{  
    fixUp(pq, pq->indexPosArray[index]);  
    heapify(pq, pq->indexPosArray[index]);  
}  
  
int cmpVertex(const void *p1, const void *p2)  
{  
    const Vertex *pa = (Vertex *)p1;  
    const Vertex *pb = (Vertex *)p2;  
    if (pa->dis < pb->dis)  
        return -1;  
    if (pa->dis == pb->dis)  
        return 0;  
    return 1;  
} 

void Prim(Graph *g, int r, Edge treeEdges[], int *treeEdgeNum) {
	PriorityQueue *pq = priorityQueueCreate(g->vertexArray, sizeof(Vertex), g->vNum, cmpVertex);
	for(int i = 0; i < g->vNum; i++) {
		g->vertexArray[i].dis = INT_MAX;
		g->vertexArray[i].parent = -1;
		g->vertexArray[i].inQueue = true;
		priorityQueueInsert(pq, i);
	}
	g->vertexArray[r].dis = 0;
	priorityQueueChangeIndex(pq, r);
	*treeEdgeNum = 0;

	while(!priorityQueueIsEmpty(pq)) {
		int u = priorityQueueExtractTop(pq);
		if(u != r) {
			Edge edge= {g->vertexArray[u].parent, u, g->vertexArray[u].dis};
			treeEdges[(*treeEdgeNum)++] = edge;
		}
		g->vertexArray[u].inQueue = false;//表示已经出队
		for(GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
			int v = x->key;
			if(g->vertexArray[v].inQueue && x->w < g->vertexArray[v].dis) {
				g->vertexArray[v].parent = u;
				g->vertexArray[v].dis = x->w;
				priorityQueueChangeIndex(pq, v);
			}
		}
	}
}

void main()  
{  
    //数据根据书上的图23-1  
    char *str_vertex[9] = { "a", "b", "c", "d", "e", "f", "g", "h", "i" };  
    Graph *g = graphCreate(9, str_vertex);  
    Edge edges[] = {  
        {0, 1, 4}, {0, 7, 8}, {1, 7, 11},  
        {1, 2, 8}, {2, 8, 2}, {2, 5, 4}, {2, 3, 7},  
        {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2},  
        {6, 7, 1}, {6, 8, 6}, {7, 8, 7}  
    };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        insertEdge(g, edges[i]);  
    }  
    printf("图信息:\n");  
    graphDisplay(g);  
    Edge tree_edges[sizeof(edges) / sizeof(edges[0])];  
    int edge_tree_num;  
    printf("最小生成树的边集是:\n");  
    Prim(g, 0, tree_edges, &edge_tree_num);  
    int weight_sum = 0;  
    for (int i = 0; i < edge_tree_num; i++) {  
        Edge e = tree_edges[i];  
        weight_sum += e.w;  
        printf("%s %s %d\n", str_vertex[e.u], str_vertex[e.v], e.w);  
    }  
    printf("最小生成树的权值之和是:%d\n", weight_sum);   
}  
