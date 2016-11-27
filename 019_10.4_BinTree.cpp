#include<stdio.h>
#include<stdlib.h>


typedef struct BinTreeNode {

	int nValue;
	struct BinTreeNode *pLChild;
	struct BinTreeNode *pRChild;
}BinTreeNode, *PBinTreeNode;

PBinTreeNode Create() {

	int nValue;
	PBinTreeNode pRoot;
	scanf("%d", &nValue);
	
	if(nValue == 0) {

		pRoot = NULL;
		return pRoot;
	} else {

		pRoot = (PBinTreeNode)malloc(sizeof(BinTreeNode));
		
		if(NULL == pRoot) {
			printf("分配内存失败!\n");
		} else {
			
			pRoot->nValue = nValue;
			printf("请输入%d结点的左子结点:", pRoot->nValue);
			pRoot->pLChild = Create();
			printf("请输入%d结点的右子结点:", pRoot->nValue);
			pRoot->pRChild = Create();
		}
	}

	return pRoot;
}

void Visit(PBinTreeNode p) {
	if(p == NULL) {
		return;
	}
	printf("%d	", p->nValue);
}

void PreOrder(PBinTreeNode pRoot) {

	if(NULL == pRoot) {
		return;
	}
	Visit(pRoot);
	PreOrder(pRoot->pLChild);
	PreOrder(pRoot->pRChild);
}

void InOrder(PBinTreeNode pRoot) {

	if(NULL == pRoot) {
		return;
	}
	
	InOrder(pRoot->pLChild);
	Visit(pRoot);
	InOrder(pRoot->pRChild);
}

void PostOrder(PBinTreeNode pRoot)
{
    if (NULL == pRoot)
    {
        return;
    }
    PostOrder(pRoot->pLChild);
    PostOrder(pRoot->pRChild);
    Visit(pRoot);
}

//叶子节点数
int	TreeLeaf(PBinTreeNode pRoot) {

	int nLChild, nRChild;
	
	if(pRoot == NULL) {
		return 0;
	}

	if(pRoot->pLChild == NULL && pRoot->pRChild == NULL) {
		return 1;
	}

	nLChild = TreeLeaf(pRoot->pLChild);
	nRChild = TreeLeaf(pRoot->pRChild);

	return nLChild + nRChild; 
}

int FindParent(PBinTreeNode pRoot, int nValue) {

	if(pRoot == NULL) {
		return 0;
	}

	if(pRoot->pLChild && pRoot->pLChild->nValue == nValue) {
		return pRoot->nValue;
	}

	if(pRoot->pRChild && pRoot->pRChild->nValue == nValue) {
		return pRoot->nValue;
	}

	FindParent(pRoot->pLChild, nValue);
	FindParent(pRoot->pRChild, nValue);

	int l = FindParent(pRoot->pLChild, nValue);
	int r = FindParent(pRoot->pRChild, nValue);
	return l >= r ? l : r;
}

int LeftBro(PBinTreeNode pRoot, int nValue) {

	if(pRoot == NULL) {
		return 0;
	}

	if(pRoot->pRChild && pRoot->pRChild->nValue == nValue) {
		
		if(pRoot->pLChild) {
			return pRoot->pLChild->nValue;
		}
	}
	
	int l = LeftBro(pRoot->pLChild, nValue);
	int r = LeftBro(pRoot->pRChild, nValue);
	return l >= r ? l : r;
}

int RightBro(PBinTreeNode pRoot, int nValue) {

	if(pRoot == NULL) {
		return 0;
	}

	if(pRoot->pLChild && pRoot->pLChild->nValue == nValue) {
		
		if(pRoot->pRChild) {
			return pRoot->pRChild->nValue;
		}
	}

	int l = RightBro(pRoot->pLChild, nValue);
	int r = RightBro(pRoot->pRChild, nValue);
	return l >= r ? l : r;
}

int TreeHight(PBinTreeNode pRoot) {
	
	int nCount;
	int nLChild, nRChild;
	if(NULL == pRoot) {
		return 0;
	}

	nLChild = TreeHight(pRoot->pLChild);
	nRChild = TreeHight(pRoot->pRChild);
	nCount = nLChild >= nRChild ? nLChild : nRChild;
	return nCount + 1;
}

void main() {


	printf("请输入根结点的值:");
    PBinTreeNode pRoot = Create();

    printf("前序遍历:");
    PreOrder(pRoot);
    puts("");

    printf("中序遍历:");
    InOrder(pRoot);
	puts("");

    printf("后序遍历:");
    PostOrder(pRoot);
    puts("");

  

    printf("二叉树的高度为:%d\n", TreeHight(pRoot));
	puts("");

    printf("二叉树的叶子个数为:%d\n", TreeLeaf(pRoot));
	puts("");

	printf("%d的父亲是:%d\n", 8, FindParent(pRoot, 8));
	puts("");

	printf("%d的右兄弟是:%d\n", 2, RightBro(pRoot, 2));
	printf("%d的右兄弟是:%d\n", 4, RightBro(pRoot, 4));
	puts("");

	printf("%d的左兄弟是:%d\n", 7, LeftBro(pRoot, 7));
	printf("%d的左兄弟是:%d\n", 6, LeftBro(pRoot, 6));
	puts("");
}
