#include<stdio.h>
#include<stdlib.h>
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
	char vertexStr[256];
};

void vertexInit(Vertex *v) {
	strcpy(v->vertexStr, "");
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
		strcpy(g->vertexArray[i].vertexStr, strVertex[i]);
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

void graphDisPlay(Graph *g) {
	printf("%d vertices,%d edges\n", g->vNum, g->eNum);
	for(int i = 0; i < g->vNum; i++) {
		printf("%s: ", g->vertexArray[i].vertexStr);
		for(GraphNode *x = g->adj[i]; x != NULL; x = x->next) {
			printf("%s/%d ", g->vertexArray[x->key].vertexStr, x->w);
		}
		printf("\n");
	}
}

void swap(void *a, void *b, size_t elem_size)  
{  
    if (a == NULL || b == NULL || a == b)  
        return;  
    char *temp = (char *)malloc(sizeof(char) * elem_size);   /*变长数组 */  
    memcpy(temp, a, elem_size);  
    memcpy(a, b, elem_size);  
    memcpy(b, temp, elem_size);  
}  

int partition(void *base, size_t elem_size, int p, int r,  
          int (*comp) (const void *, const void *))  
{  
    char *cbase = (char *)base;  
    void *key = &cbase[r * elem_size];  
    int i = p - 1;  
    for (int j = p; j < r; j++) {  
        if (comp(&cbase[j * elem_size], key) <= 0) {  
            ++i;  
            swap(&cbase[i * elem_size], &cbase[j * elem_size],  
                 elem_size);  
        }  
    }  
    swap(&cbase[(i + 1) * elem_size], key, elem_size);  
    return i + 1;  
}  
  
void quick_sort(void *base, size_t elem_size, int p, int r,  
        int (*comp) (const void *, const void *))  
{  
    if (p < r) {  
        int q = partition(base, elem_size, p, r, comp);  
        quick_sort(base, elem_size, p, q - 1, comp);  
        quick_sort(base, elem_size, q + 1, r, comp);  
    }  
}  

struct SetNode {
	void *key;
	int rank;
	SetNode *parent;
};

void setNodeInit(SetNode *x, void *key) {
	x->key = key;
	x->rank = 0;
	x->parent = NULL;
}

struct Set {
	SetNode *root;
};

Set *setCreate(void *key) {
	Set *s = (Set *)malloc(sizeof(Set));
	s->root = (SetNode *)malloc(sizeof(SetNode));
	setNodeInit(s->root, key);
	s->root->parent = s->root;
	s->root->rank = 0;
	return s;
}

void link(SetNode *x, SetNode *y) {
	if(x->rank > y->rank) {
		y->parent = x;
	} else {
		x->parent = y;
		if(x->rank == y->rank) {
			++y->rank;
		}
	}
}

SetNode *findSetPathCompression(SetNode *x) {
	if(x != x->parent) {
		x->parent = findSetPathCompression(x->parent);
	}
	return x->parent;
}

SetNode *findSet(Set *s) {
	return findSetPathCompression(s->root);
}

void setUnion(Set *sa, Set *sb) {
	link(findSet(sa), findSet(sb));
}

void graphGetEdges(Graph *g, Edge edges[], int *edgeNum) {
	*edgeNum = 0;
	for(int i = 0; i < g->vNum; i++) {
		int u = i;
		for (GraphNode *x = g->adj[i]; x != NULL; x = x->next) {
			int v = x->key;
			if(u <= v) {
				Edge edge = {u, v, x->w};
				edges[(*edgeNum)++] = edge;
			}
		}
	}
}

int cmpEdge(const void *p1, const void *p2) {
	const Edge *pa = (Edge *)p1;
	const Edge *pb = (Edge *)p2;
	if(pa->w < pb->w) {
		return -1;
	}
	if(pa->w == pb->w) {
		return 0;
	}
	return 1;
}

void Kruskal(Graph *g, Edge treeEdges[], int *treeEdgeNum) {
	Set *setArray = (Set *)malloc(sizeof(Set) * g->vNum);
	for(int i = 0; i < g->vNum; i++) {
		int *p = (int *)malloc(sizeof(int));
		*p = i;
		setArray[i] = *setCreate(p);
	}
	Edge *edges = (Edge *)malloc(sizeof(Edge)*g->eNum);
	int edgeNum = 0;
	graphGetEdges(g, edges, &edgeNum);
	quick_sort(edges, sizeof(Edge), 0, edgeNum - 1, cmpEdge);
	*treeEdgeNum = 0;
	for(int i = 0; i < edgeNum; i++) {
		Edge edge = edges[i];
		if(findSet(&setArray[edge.u]) != findSet(&setArray[edge.v])) {
			treeEdges[(*treeEdgeNum)++] = edge;
			setUnion(&setArray[edge.u], &setArray[edge.v]);
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
        insertEdge(g,edges[i]);  
    }  
    printf("图信息:\n");  
    graphDisPlay(g);  
    Edge tree_edges[sizeof(edges) / sizeof(edges[0])];  
    int edge_tree_num;  
    printf("最小生成树的边集是:\n");  
    Kruskal(g,tree_edges, &edge_tree_num);  
    int weight_sum = 0;  
    for (int i = 0; i < edge_tree_num; i++) {  
        Edge e = tree_edges[i];  
        weight_sum += e.w;  
        printf("%s %s %d\n", str_vertex[e.u],str_vertex[e.v],e.w);  
    }  
    printf("最小生成树的权值之和是:%d\n",weight_sum);  
}
