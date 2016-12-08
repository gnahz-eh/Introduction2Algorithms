#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//====================队列===========================
struct QueueNode {
	void *key;
	struct QueueNode *next;
};

struct Queue {

	QueueNode *head;
	QueueNode *tail;
};

void queueNodeInit(QueueNode *node, void *key) {
	node->key = key;
	node->next = NULL;
}

Queue *queueCreate() {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

bool isEmpty(Queue *q) {
	return q->head == NULL;
}

void enQueue(Queue *q, void *key) {
	QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
	queueNodeInit(node, key);
	if(q->head == NULL) {
		q->head = node;
		q->tail = node;
	} else {
		q->tail->next = node;
		q->tail = node;
	}
}

void *deQueue(Queue *q) {
	void *key = q->head->key;
	QueueNode *p = q->head;
	q->head = q->head->next;
	free(p);
	return key;
}
//===============================================
enum Color {
	WHITE,
	GRAY,
	BLACK
};

struct Edge { 
	int u; 
	int v; 
};

struct GraphNode {

	int key;
	struct GraphNode *next;
};

void graphNodeInit(GraphNode *g, int key) {
	g->key = key;
	g->next = NULL;
}

struct Vertex {
	Color color;
	int dis;
	int parent;
	char strVertex[256];
};

void vertexInit(Vertex *v) {
	v->color = WHITE;
	v->dis = 0;
	v->parent = -1;
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
	g->adj = (GraphNode **)malloc(sizeof(GraphNode *) * vNum);
	g->vertexArray = (Vertex *)malloc(sizeof(Vertex) * vNum);
	
	for(int i = 0; i < vNum; i++) {
		g->adj[i] = NULL;
		strcpy(g->vertexArray[i].strVertex, strVertex[i]);
	}

	return g;
}

void graphInsertEdge(Graph *g, Edge e) {
	GraphNode *u = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(u, e.u);
	GraphNode *v = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(v, e.v);
	//从表头插入,将v插入到表头u 
	v->next = g->adj[e.u];
	g->adj[e.u] = v;
	//从表头插入,将u插入到表头v  
    u->next = g->adj[e.v];  
    g->adj[e.v] = u;  
	g->eNum++;
}

void graphDisplay(Graph *g) {
	printf("%d vertices, %d edges\n", g->vNum, g->eNum);
	for(int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].strVertex);
		for(GraphNode *x = g->adj[i]; x != NULL; x = x->next) {
			printf("%s ", g->vertexArray[x->key].strVertex);
		}
		printf("\n");
	}
}

void graphDisplayVertex(Graph *g) {
	printf("各个顶点的数据:\n");
	for(int i = 0; i < g->vNum; i++) {
		printf("%s: %d\n", g->vertexArray[i].strVertex, g->vertexArray[i].dis);
	}
}

void graphBFS(Graph *g, int s) {
	for(int i = 0; i < g->vNum; i++) {
		if(i != s) {
			g->vertexArray[i].color = WHITE;
			g->vertexArray[i].dis = INT_MAX;
			g->vertexArray[i].parent = -1;
		}
	}

	g->vertexArray[s].color = GRAY;
	g->vertexArray[s].dis = 0;
	g->vertexArray[s].parent = -1;
	Queue *q = queueCreate();
	int *p = (int *)malloc(sizeof(int));
	*p = s;
	enQueue(q, p);
	while(!isEmpty(q)) {
		p = (int *)deQueue(q);
		int u = *p;
		free(p);
		for(GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
			int v = x->key;
			if(g->vertexArray[v].color == WHITE) {
				g->vertexArray[v].color = GRAY;
				g->vertexArray[v].dis = g->vertexArray[u].dis + 1;
				g->vertexArray[v].parent = u;
				p = (int *)malloc(sizeof(int));
				*p = v;
				enQueue(q, p);
			}
		}
		g->vertexArray[u].color = BLACK;
	}
}

void graphPrintPath(Graph *g, int s, int v) {
	if(s == v) {
		printf("%s ", g->vertexArray[s].strVertex);
	} else {
		if(g->vertexArray[v].parent == -1) {
			printf("no path from %s to %s exist\n", g->vertexArray[s].strVertex, g->vertexArray[v].strVertex);
		} else {
			graphPrintPath(g, s, g->vertexArray[v].parent);
			printf("%s ", g->vertexArray[v].strVertex);
		}
	}
}

void main() {
char *str_vertex[8] = {  
        "r", "s", "t", "u", "v", "w", "x", "y"  
    };  
    Graph *g = graphCreate(8, str_vertex);  
    struct Edge edges[10] = {  
        {0, 1}, {0, 4}, {1, 5}, {2, 3}, {2, 5}, {2, 6}, {3, 6}, {3, 7},  
        {5, 6}, {6, 7}  
    };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        graphInsertEdge(g, edges[i]);  
    }  
    graphDisplay(g);  
    int s = 1;  
    int v = 7;  
    graphBFS(g, s);  
    graphDisplayVertex(g);  
    printf("path from %s to %s\n", str_vertex[s], str_vertex[v]);  
    graphPrintPath(g, s, v);  
    printf("\n");  
}
