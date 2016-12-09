#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void DFSVisit(Graph *g, int u) {
	g->vertexArray[u].color = GRAY;
	g->vertexArray[u].dTime = ++g->time;
	for(GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
		int v = x->key;
		if(g->vertexArray[v].color == WHITE) {
			g->vertexArray[v].parent = u;
			DFSVisit(g, v);
		}
	}
	g->vertexArray[u].color = BLACK;
	g->vertexArray[u].fTime = ++g->time;
}

void DFS(Graph *g) {
	for(int i = 0; i < g->vNum; i++) {
		g->vertexArray[i].color = WHITE;
		g->vertexArray[i].parent = -1;
	}
	for(int i = 0; i < g->vNum; i++) {
		if(g->vertexArray[i].color == WHITE) {
			DFSVisit(g, i);
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

void main()  
{  
    //数据根据书上的图22-4  
    char *str_vertex[6] = { "u", "v", "w", "x", "y", "z" };  
    Graph* g = graphCreate(6, str_vertex);  
    Edge edges[] =  
        { {0, 3}, {0, 1}, {1, 4}, {2, 4}, {2, 5}, {3, 1}, {4, 3}, {5, 5} };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        insertEdge(g,edges[i]);  
    }  
    graphDisplay(g);  
    DFS(g);  
    graphDisplayVertex(g);  
} 
