#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct StackNode {
	void *key;
	StackNode *next;
};

struct Stack {
	StackNode *head;
};

void stackNodeInit(StackNode *n, void *key) {
	n->key = key;
	n->next = NULL;
}

Stack *stackCreate() {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->head = NULL;
	return s;	
}

bool isStackEmpty(Stack *s) {
	return s->head == NULL;
}

void stackPush(Stack *s, void *x) {
	StackNode *node = (StackNode *)malloc(sizeof(StackNode));
	stackNodeInit(node, x);
	node->next = s->head;
	s->head = node;
}

void *stackPop(Stack *s) {

	StackNode *p = s->head;
	s->head = s->head->next;
	void *key = p->key;
	free(p);
	return key;
}

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
	GraphNode *next;
};

void graphNodeInit(GraphNode *x, int key) {
	x->key = key;
	x->next = NULL;
}

struct Vertex {
	Color color;
	int parent;
	int dTime;
	int fTime;
	char strVertex[256];
};

void vertexInit(Vertex *v) {
	v->color = WHITE;
	v->parent = -1;
	v->dTime = 0;
	v->fTime = 0;
	strcpy(v->strVertex, "");
}

struct Graph {
	GraphNode **adj;
	int time;
	Vertex *vertexArray;
	int vNum;
	int eNum;
};

Graph *graphCreate(int vNum, char *strVertex[]) {
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->vNum = vNum;
	g->eNum = 0;
	g->time = 0;
	g->adj = (GraphNode **)malloc(sizeof(GraphNode *) * vNum);
	g->vertexArray = (Vertex *)malloc(sizeof(Vertex) * vNum);
	for(int i = 0; i < vNum; i++) {
		g->adj[i] = NULL;
		strcpy(g->vertexArray[i].strVertex, strVertex[i]);
	}
	return g;
}

void insertEdge(Graph *g, Edge e) {
	GraphNode *v = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(v, e.v);
	//从表头插入,将v插入到表头u
	v->next = g->adj[e.u];
	g->adj[e.u] = v;
	g->eNum++;
}

void graphDisplay(Graph *g) {
	printf("%d vertices,%d edges\n", g->vNum, g->eNum);
	for(int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].strVertex);
		for(GraphNode *x = g->adj[i]; x != NULL; x = x->next) {
			printf("%s ", g->vertexArray[x->key].strVertex);
		}
		printf("\n");
	}
}

void DFSVisit(Graph *g, int u, Stack *s) {
	g->vertexArray[u].color = GRAY;
	g->vertexArray[u].dTime = ++g->time;
	for(GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
		int v = x->key;
		if(g->vertexArray[v].color == WHITE) {
			g->vertexArray[v].parent = u;
			DFSVisit(g, v, s);
		}
	}
	g->vertexArray[u].color = BLACK;
	g->vertexArray[u].fTime = ++g->time;
	int *p = (int *)malloc(sizeof(int));
	*p = u;
	stackPush(s, p);
;}

void TopLogicalSort(Graph *g, Stack *s) {
	for(int i = 0; i < g->vNum; i++) {
		g->vertexArray[i].color = WHITE;
		g->vertexArray[i].parent = -1;
	}
	for(int i = 0; i < g->vNum; i++) {
		if(g->vertexArray[i].color == WHITE) {
			DFSVisit(g, i, s);
		}
	}
}


void graphDisplayVertex(Graph *g) {

	printf("各个顶点的数据:\n");
	for (int i = 0; i < g->vNum; i++) {  
        printf("%s: %d/%d\n", g->vertexArray[i].strVertex,  
               g->vertexArray[i].dTime,  
               g->vertexArray[i].fTime);  
    }  
}

int main()  
{  
    //数据根据书上的图22-7  
    char *str_vertex[9] =  
        { "shirt", "tie", "jacket", "belt", "watch", "undershorts", "pants",  
        "shoes", "socks"  
    };  
    Graph *g=graphCreate(9, str_vertex);  
    struct Edge edges[] =  
        { {0, 3}, {0, 1}, {1, 2}, {3, 2}, {5, 7}, {5, 6}, {6, 7}, {6, 3},  
    {8, 7}  
    };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        insertEdge(g,edges[i]);  
    }  
    graphDisplay(g);  
    Stack *s=stackCreate();  
    TopLogicalSort(g,s);  
    graphDisplayVertex(g);  
    while (!isStackEmpty(s)) {  
        int *p=(int *)stackPop(s);          
        printf("%s ",str_vertex[*p]);  
    }  
    printf("\n");  
}  
