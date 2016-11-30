#include<iostream>
#include<string>
using namespace std;
enum COLOR { RED, BLACK};

class Node {

public:
	int nValue;
	Node *pParent;
	Node *lChild;
	Node *rChild;
	COLOR color;
	friend class BRT;

public:
	Node(int value = 0) : nValue(value) {
		this->pParent = NULL;
		this->lChild = NULL;
		this->rChild = NULL;
		this->color = BLACK;
	}
};

class BRT {
	
public:
	Node *pRoot;
	Node *pNil;
	BRT();
	void LeftRotate(Node *x);
	void RightRotate(Node *x);
	void Insert(int nValue);
	void InsertFixUp(Node *z);
	void RBTransplant(Node *u, Node *v);
	void Delete(Node *z);
	void DeleteFixUp(Node *x);
	Node* TreeMin(Node *x);
};

BRT::BRT() {
	pNil = new Node();
	pRoot = NULL;
}

/*	
---------------------------
	|			    |	  |
    x			    y	  |
   / \			   / \	  |
  a	  y	   ===>	  x	  c	  |
	 / \		 / \	  |
	b	c		a	b	  |
						  |
	     左旋图示		  |
---------------------------
*/
void BRT::LeftRotate(Node *x) {
	Node *y = x->rChild;
	x->rChild = y->lChild;
	if(y->lChild != pNil) {
		y->lChild->pParent = x;
	}
	y->pParent = x->pParent;
	if(x->pParent == pNil) {
		pRoot = y;
	} else if(x == x->pParent->lChild) {
		x->pParent->lChild = y;
	} else {
		x->pParent->rChild = y;
	}
	y->lChild = x;
	x->pParent = y;
}

/*	
---------------------------
	|			    |	  |
    y			    x	  |
   / \			   / \	  |
  a	  x	   <===	  y	  c	  |
	 / \		 / \	  |
	b	c		a	b	  |
						  |
	     右旋图示		  |
---------------------------
*/
void BRT::RightRotate(Node *x) {
	Node *y = x->lChild;
	x->lChild = y->rChild;
	if(y->rChild != pNil) {
		y->rChild->pParent = x;
	}
	y->pParent = x->pParent;
	if(x->pParent == pNil) {
		pRoot = y;
	} else if(x == x->pParent->lChild) {
		x->pParent->lChild = y;
	} else {
		x->pParent->rChild = y;
	}
	y->rChild = x;
	x->pParent = y;
}

	/*----------插入结点操作----------
	 RB-INSERT(T, z)				|
	1  y = T.nil					|
	2  x = T.root					|
	3  while x != T.nil				|
	4	 y = x						|
	5	 if z.key < x.key			|
	6		 x = x.left				|
	7	 else						|
	8		 x = x.right			|
	9  z.p = y						|
	10 if y == T.nil				|
	11		T.root = z				|
	12 else if z.key < y.key		|
	13		y.left = z				|
	14 else							|
	15		y.right = z				|
	16 z.left = T.nil				|
	17 z.right = T.nil				|
	18 z.color = RED				|
	19 RB-INSERT-FIXUP(T, z)		|
	---------------------------------
	*/
void BRT::Insert(int nValue) {

	Node *z = new Node(nValue);
	Node *y = pNil;
	Node *x = pRoot;

	while(x != pNil) {
		y = x;
		if(z->nValue < x->nValue) {
			x = x->lChild;
		} else {
			x = x->rChild;
		}
	}
	z->pParent = y;
	if(y == pNil) {
		pRoot = z;
	} else if(z->nValue < y->nValue) {
		y->lChild = z;
	} else {
		y->rChild = z;
	}

	z->lChild = pNil;
	z->rChild = pNil;
	z->color = RED;
	InsertFixUp(z);
}



	//---------------------插入结点性质修复--------------------------------    
    //3种插入情况，都在下面的伪代码中(未涉及到所有全部的插入情况)。    
    /* 
    RB-INSERT-FIXUP(T, z) 
    1 while color[p[z]] = RED 
    2     do if p[z] = left[p[p[z]]] 
    3           then y ← right[p[p[z]]] 
    4                if color[y] = RED 
    5                   then color[p[z]] ← BLACK                     ? Case 1 
    6                        color[y] ← BLACK                        ? Case 1 
    7                        color[p[p[z]]] ← RED                    ? Case 1 
    8                        z ← p[p[z]]                             ? Case 1 
    9                   else if z = right[p[z]] 
    10                           then z ← p[z]                       ? Case 2 
    11                                LEFT-ROTATE(T, z)              ? Case 2 
    12                           color[p[z]] ← BLACK                 ? Case 3 
    13                           color[p[p[z]]] ← RED                ? Case 3 
    14                           RIGHT-ROTATE(T, p[p[z]])            ? Case 3 
    15           else (same as then clause with "right" and "left" exchanged) 
    16 color[root[T]] ← BLACK 
    */  

void BRT::InsertFixUp(Node *z) {

	while(z->pParent->color == RED) {
		
		if(z->pParent == z->pParent->pParent->lChild) {
			Node *y = z->pParent->pParent->rChild;
			
			if(y->color == RED) {
				z->pParent->color = BLACK;
				y->color = BLACK;
				z->pParent->pParent->color = RED;
				z = z->pParent->pParent;

			} else if(z == z->pParent->rChild) {
				z = z->pParent;
				LeftRotate(z);	
			}
			
			z->pParent->color = BLACK;
			z->pParent->pParent->color = RED;
			RightRotate(z->pParent->pParent);

		} else {
			
			Node *y = z->pParent->pParent->lChild;

			if(y->color == RED) {
				z->pParent->color == BLACK;
				y->color = BLACK;
				z->pParent->pParent->color = RED;
				z = z->pParent->pParent;

			} else if(z == z->pParent->lChild) {
				z = z->pParent;
				RightRotate(z);
			}

			z->pParent->color = BLACK;
			z->pParent->pParent->color = RED;
			LeftRotate(z->pParent->pParent);
		}
	}

	pRoot->color = BLACK;
}

/*
------------------------
		node	
		/
	   u  <====	v
	  / \	   / \
	 a   b    c   d 
------------------------
*/

void BRT::RBTransplant(Node *u, Node *v) {

	if(u->pParent == pNil) {
		pRoot = v;
	} else if(u = u->pParent->lChild) {
		u->pParent->lChild = v;
	} else {
		u->pParent->rChild = v;
	}

	v->pParent = u->pParent;
}

Node* BRT::TreeMin(Node *x) {

	while(x->lChild != pNil) {
		x = x->lChild;
	}
	return x;
}

void BRT::Delete(Node *z) {
	Node *x = NULL;
	Node *y = z;
	COLOR y_origin_color = y->color;

	if(z->lChild == pNil) {
		 x = z->rChild;
		RBTransplant(z, z->rChild);
	} else if(z->rChild == pNil) {
		x = z->lChild;
		RBTransplant(z, z->lChild);
	} else {
		y = TreeMin(z->rChild);
		y_origin_color = y->color;
		x = y->rChild;

		if(y->pParent == z) {
			x->pParent = y;
		} else {
			RBTransplant(y, y->rChild);
			y->rChild = z->rChild;
			y->rChild->pParent = y;
		}
		RBTransplant(z, y);
		y->lChild = z->lChild;
		y->lChild->pParent = y;
		y->color = z->color;
	}

	if(y_origin_color == RED) {
		DeleteFixUp(x);
	}
}

 //---------------------删除结点性质修复-----------------------------------    
    //所有的工作，都在下述23行伪代码中：    
    /* 
    RB-DELETE-FIXUP(T, x) 
    1 while x ≠ root[T] and color[x] = BLACK 
    2     do if x = left[p[x]] 
    3           then w ← right[p[x]] 
    4                if color[w] = RED 
    5                   then color[w] ← BLACK                         ?  Case 1 
    6                        color[p[x]] ← RED                        ?  Case 1 
    7                        LEFT-ROTATE(T, p[x])                     ?  Case 1 
    8                        w ← right[p[x]]                          ?  Case 1 
    9                if color[left[w]] = BLACK and color[right[w]] = BLACK 
    10                   then color[w] ← RED                          ?  Case 2 
    11                        x p[x]                                  ?  Case 2 
    12                   else if color[right[w]] = BLACK 
    13                           then color[left[w]] ← BLACK          ?  Case 3 
    14                                color[w] ← RED                  ?  Case 3 
    15                                RIGHT-ROTATE(T, w)              ?  Case 3 
    16                                w ← right[p[x]]                 ?  Case 3 
    17                         color[w] ← color[p[x]]                 ?  Case 4 
    18                         color[p[x]] ← BLACK                    ?  Case 4 
    19                         color[right[w]] ← BLACK                ?  Case 4 
    20                         LEFT-ROTATE(T, p[x])                   ?  Case 4 
    21                         x ← root[T]                            ?  Case 4 
    22        else (same as then clause with "right" and "left" exchanged) 
    23 color[x] ← BLACK 
    */ 

void BRT::DeleteFixUp(Node *x) {

	Node *w = NULL;

	while (x != pNil && x->color == BLACK) {
		
		if(x == x->pParent->lChild) {
			w = x->pParent->rChild;

			if(w->color == RED) {
				w->color = BLACK;
				x->pParent->color = RED;
				LeftRotate(x->pParent);
				w = x->pParent->rChild;
			}

			if(w->lChild->color == BLACK && w->rChild->color == BLACK) {
				w->color = RED;
				x = x->pParent;
			} else if(w->rChild->color == BLACK) {
				w->lChild->color = BLACK;
				w->color =RED;
				RightRotate(w);
				w = x->pParent->rChild;
			}

			w->color = x->pParent->color;
			x->pParent->color = BLACK;
			w->rChild->color = BLACK;
			LeftRotate(x->pParent);
			x = pRoot; 
		}

		else {
		
			w = x->pParent->lChild;

			if(w->color == RED) {
				w->color = BLACK;
				x->pParent->color = RED;
				RightRotate(x->pParent);
				w = x->pParent->lChild;
			}

			if(w->rChild->color == BLACK && w->lChild->color == BLACK) {
				w->color = RED;
				x = x->pParent;
			} else if(w->lChild->color == BLACK) {
				w->rChild->color = BLACK;
				w->color =RED;
				LeftRotate(w);
				w = x->pParent->lChild;
			}

			w->color = x->pParent->color;
			x->pParent->color = BLACK;
			w->lChild->color = BLACK;
			RightRotate(x->pParent);
			x = pRoot; 
		}
	}

	x->color = BLACK;
}
