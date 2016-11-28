#include<iostream>
using namespace std;

class Node {
public:
	int nValue;
	Node *pParent;
	Node *lChild;
	Node *rChild;
	friend class BST;

public:
	Node(int value = 0) : nValue(value) {
		this->pParent = NULL;
		this->lChild = NULL;
		this->rChild = NULL;
	}
};

class BST {

public:
	Node *pRoot;
	BST();
	void InOrder(Node* x);							
	Node* Search(Node *x, int nValue);				
	Node* Search_Interative(Node *x, int nValue);	
	Node* TreeMin(Node *x);							
	Node* TreeSuccessor(Node *x);					
	void Insert(int nValue);						
	Node* Insert2(Node *x, int nValue);				
	void Transplant(Node *u, Node *v);				
	void TreeDelete(Node *z);
};

BST::BST() {
	pRoot = NULL;
}

void BST::InOrder(Node* x) {

	if(x != NULL) {
		
		InOrder(x->lChild);
		cout << x->nValue << " ";
		InOrder(x->rChild);
		
	}
}

Node* BST::Search(Node *x, int nValue) {

	if(x == NULL || x->nValue == nValue) {
		return x;
	}

	if(nValue < x->nValue) {
		return Search(x->lChild, nValue);
	} else {
		return Search(x->rChild, nValue);
	}
}

Node* BST::Search_Interative(Node *x, int nValue) {

	while(x != NULL && x->nValue != nValue) {
		if(nValue < x->nValue) {
			x = x->lChild;
		} else {
			x = x->rChild;
		}
	}
	return x;
}

Node* BST::TreeMin(Node *x) {

	while(x->lChild != NULL) {
		x = x->lChild;
	}
	return x;
}

Node* BST::TreeSuccessor(Node *x) {

	if(x->rChild != NULL) {
		return TreeMin(x->rChild);
	}

	Node *y = x->pParent;

	while(y != NULL && x == y->rChild) {
		x = y;
		y = y->pParent;
	}

	return y;
}

Node* BST::Insert2(Node *x, int nValue) {
	
	if(x == NULL) {
		Node *z = new Node(nValue);
		x = z;
	} else {
		
		if(x->nValue > nValue) {
			x->lChild = Insert2(x->lChild, nValue);
		} else if(x->nValue < nValue) {
			x->rChild = Insert2(x->rChild, nValue);
		}
	}
	return x;
}

void BST::Insert(int nValue) {

	Node *z = new Node(nValue);
	Node *y = NULL;
	Node *x = pRoot;

	while(x != NULL) {
		y = x;
		if(z->nValue < x->nValue) {
			x = x->lChild;
		} else {
			x = x->rChild;
		}
	}

	z->pParent = y;

	if(y == NULL) {
		pRoot = z;
	} else if(z->nValue < y->nValue) {
		y->lChild = z;
	} else {
		y->rChild = z;
	}
}

void BST::Transplant(Node *u, Node *v) {

	if(u->pParent == NULL) {
		pRoot = v;
	} else if(u == u->pParent->lChild) {
		u->pParent->lChild = v;
	} else {
		u->pParent->rChild = v;
	}

	if(v != NULL) {
		v->pParent = u->pParent;
	}
}

void BST::TreeDelete(Node *z) {

	if(z->lChild == NULL) {
		Transplant(z, z->rChild);
	} else if(z->rChild == NULL) {
		Transplant(z, z->lChild);
	} else {

		Node *y = TreeMin(z->rChild);
		if(y->pParent != z) {
			Transplant(y, y->rChild);
			y->rChild = z->rChild;
			y->rChild->pParent = y;
		}
		Transplant(z, y);
		y->lChild = z->lChild;
		y->lChild->pParent = y;	
	}
}


void main() {

	BST b;
	BST b2;
	int a[] = {4,2,6,1,3,5,7}; 
	for(int i = 0; i < sizeof(a)/sizeof(int); i++) {
		b.Insert(a[i]);
		//b2.pRoot = b2.Insert2(b2.pRoot, a[i]);
	}
	b.InOrder(b.pRoot);
	puts("");
	//cout <<	"4->" << b.pRoot->rChild->nValue << endl;
	//Node *p = b.TreeSuccessor(b.pRoot->lChild->lChild);
	b.TreeDelete(b.pRoot->rChild->rChild);
	//cout <<	"4->" << b.pRoot->rChild->nValue << endl;
	//b.TreeDelete(b.pRoot->lChild);
	b.InOrder(b.pRoot);
	//puts("");
	//b2.InOrder(b2.pRoot);


}
