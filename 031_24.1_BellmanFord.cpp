#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

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

void insertEdge(Graph *g, Edge e) {
	GraphNode *v = (GraphNode *)malloc(sizeof(GraphNode));
	graphNodeInit(v, e.v, e.w);
	v->next = g->adj[e.u];
	g->adj[e.u] = v;
	++g->eNum;
}

void graphDisplay(Graph *g) {
	printf("%d vertices, %d edges\n", g->vNum, g->eNum);
	for (int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].strVertex);
		for (GraphNode *x = g->adj[i]; x != NULL; x = x->next) {
			printf("%s,%d	", g->vertexArray[x->key].strVertex, x->w);
		}
		printf("\n");
	}
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

bool BellmanFord(Graph *g, int s) {

	initializeSingleSource(g, s);

	for (int i = 0; i < g->vNum - 1; i++) {
		for (int u = 0; u < g->vNum; u++) {
			for (GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
				relax(g, u, x->key, x->w);
			}
		}
	}
	for (int u = 0; u < g->vNum; u++) {
		for (GraphNode *x = g->adj[u]; x != NULL; x = x->next) {
			if (g->vertexArray[x->key].dis > g->vertexArray[u].dis + x->w) {
				return false;
			}
		}
	}
	return true;
}

void graphDisplayVertex(Graph *g) {
	printf("各个顶点数据： \n");
	for (int i = 0; i < g->vNum; i++) {
		printf("%s:%d\n", g->vertexArray[i].strVertex, g->vertexArray[i].dis);
	}
}

int main()  
{  
    //数据根据书上的图24-4  
    char *str_vertex[5] = { "s", "t", "x", "y", "z" };  
    Graph *g = graphCreate(5, str_vertex);  
    Edge edges[] = { {0, 1, 6}, {0, 3, 7}, {1, 2, 5},  
    {1, 3, 8}, {1, 4, -4}, {2, 1, -2}, {3, 2, -3},  
    {3, 4, 9}, {4, 0, 2}, {4, 2, 7}  
    };  
    for (unsigned i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {  
        insertEdge(g, edges[i]);  
    }  
    graphDisplay(g);  
    BellmanFord(g, 0);  
    graphDisplayVertex(g);  
} 
