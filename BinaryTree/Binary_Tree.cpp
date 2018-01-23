#include<iostream>
using namespace std;

/* Binary Tree Node - START */
class node{
		char dta;
		int ht;
		node *lc, *rc, *prnt;
	public:
		node(char d, node *lc, node *rc, node *p = NULL);
		char data();
		node* left();
		node* right();
		node* parent();
		void setHeight();
		int height();
};

node::node(char d, node *lt, node *rt, node *p){
	dta = d;
	lc = lt;
	rc = rt;
	prnt = p;
	ht = -1;
}

int node::height(){
	return ht;
}

void node::setHeight(){
	if(!lc && !rc){
		ht = 0;
	}
	else if(!lc){
		ht = rc->height() + 1;
	}
	else if(!rc){
		ht = lc->height() + 1;
	}
	else{
		ht = ((lc->height() > rc->height()) ? lc->height() : rc->height()) + 1;
	}
}

char node::data(){
	return dta;
}

node* node::left(){
	return lc;
}

node* node::right(){
	return rc;
}

node* node::parent(){
	return prnt;
}
/* Binary Tree Node - END */

/* Stack - START */
class snode{
		node *n;
		snode *nxt;

	public:
		snode(node* sn, snode *nt = NULL);
		node* data();
		snode* next();
		void setNext(snode *nt);
};

snode::snode(node *sn, snode *nt){
	n = sn;
	nxt = nt;
}

node* snode::data(){
	return n;
}

snode* snode::next(){
	return nxt;
}

void snode::setNext(snode *nt){
	nxt = nt;
}

class stack{
		snode *top;

	public:
		stack(snode *tp);
		void push(snode *nd);
		snode* pop();
};

stack::stack(snode *tp){
	top = tp;
}

void stack::push(snode *nd){
	if(!nd){
		return;
	}
	nd->setNext(top);
	top = nd;
}

snode* stack::pop(){
	if(!top){
		return NULL;
	}

	snode *temp = top;
	top = top->next();
	return temp;
}
/* Stack - END */

/* Queue - START */
class qnode{
		node *n;
		qnode *nxt;

	public:
		qnode(node *nd, qnode *nt = NULL);
		node* data();
		qnode* next();
		void setNext(qnode *nt);
};

qnode::qnode(node *nd, qnode *nt){
	n = nd;
	nxt = nt;
}

node* qnode::data(){
	return n;
}

qnode* qnode::next(){
	return nxt;
}

void qnode::setNext(qnode *nt){
	nxt = nt;
}

class queue{
		qnode *head, *tail;

	public:
		queue(qnode *nd);
		void enqueue(qnode *nd);
		qnode* dequeue();
};

queue::queue(qnode *nd){
	head = tail = nd;
}

void queue::enqueue(qnode *nd){
	if(!nd){
		return;
	}

	if(!tail){
		tail = head = nd;
		return;
	}

	tail->setNext(nd);
	tail = nd;
}

qnode* queue::dequeue(){
	if(!head){
		return NULL;
	}

	qnode *temp = head;
	head = head->next();

	if(!head){
		tail = head;
	}

	return temp;
}
/* Queue - END */

/* Binary Tree - START */
class binaryTree{
		node *root;

	public:
		binaryTree(node *rt);
		void prettyPrint(int indent = 0);
		void setRoot(node *rt);
		void preOrderRec();
		void inOrderRec();
		void postOrderRec();
		void preOrderIter();
		void inOrderIter();
		void postOrderIter();
		void levelOrder();
		void heightIter();
		void heightRec();
};

binaryTree::binaryTree(node *rt){
	root = rt;
}

void binaryTree::prettyPrint(int indent){
	if(!root){
		for(int i = 0; i < indent; ++i){
			cout<<"\t";
		}
		cout<<"nil"<<endl;
		return;
	}
	for(int i = 0; i < indent; ++i){
		cout<<"\t";
	}
	cout<<root->data()<<endl;
	binaryTree(root->left()).prettyPrint(indent+1);
	binaryTree(root->right()).prettyPrint(indent+1);
}

void binaryTree::setRoot(node *rt){
	root = rt;
}

void binaryTree::preOrderRec(){
	if(!root){
		return;
	}
	cout<<root->data()<<" ";
	binaryTree(root->left()).preOrderRec();
	binaryTree(root->right()).preOrderRec();
}

void binaryTree::postOrderRec(){
	if(!root){
		return;
	}
	binaryTree(root->left()).postOrderRec();
	binaryTree(root->right()).postOrderRec();
	cout<<root->data()<<" ";
}

void binaryTree::inOrderRec(){
	if(!root){
		return;
	}
	binaryTree(root->left()).inOrderRec();
	cout<<root->data()<<" ";
	binaryTree(root->right()).inOrderRec();
}

void binaryTree::preOrderIter(){
	if(!root){		//In case of empty tree
		return;
	}
	snode *temp = new snode(root);
	stack s(temp);
	while((temp = s.pop())){
		if(temp->data()->right()){
			s.push(new snode(temp->data()->right()));
		}
		if(temp->data()->left()){
			s.push(new snode(temp->data()->left()));
		}
		cout<<temp->data()->data()<<" ";
		delete temp;
	}
}

void binaryTree::inOrderIter(){
	if(!root){		//In case of empty tree
		return;
	}
	stack s(new snode(root));
	node *temp = root->left();
	snode *temp1 = NULL;
	while(1){
		if(temp){
			s.push(new snode(temp));
			temp = temp->left();
		}
		else if((temp1 = s.pop())){
			cout<<temp1->data()->data()<<" ";
			temp = temp1->data()->right();
			delete temp1;
		}
		else{
			break;
		}
	}
}

void binaryTree::postOrderIter(){
	if(!root){		//In case of empty tree
		return;
	}
	stack s(NULL);
	snode *temp1 = NULL, *temp2 = NULL;
	node *temp = root;
	while(1){
		if(temp){
			if(temp->right())
				s.push(new snode(temp->right()));
			s.push(new snode(temp));
			temp = temp->left();
		}
		else if((temp1 = s.pop())){
			if((temp2 = s.pop()) && temp2 && (temp2->data() == temp1->data()->right())){
				s.push(temp1);
				temp = temp2->data();
			}
			else{
				s.push(temp2);
				cout<<temp1->data()->data()<<" ";
				delete temp1;
			}
		}
		else{
			break;
		}
	}
}

void binaryTree::levelOrder(){
	queue q(new qnode(root));
	qnode *temp = NULL;
	while((temp = q.dequeue())){
		cout<<temp->data()->data()<<" ";
		if(temp->data()->left()){
			q.enqueue(new qnode(temp->data()->left()));
		}
		if(temp->data()->right()){
			q.enqueue(new qnode(temp->data()->right()));
		}
	}
}

void binaryTree::heightIter(){
	if(!root){		//In case of empty tree
		return;
	}

	stack s(NULL);
	snode *temp1 = NULL, *temp2 = NULL;
	node *temp = root;
	while(1){
		if(temp){
			if(temp->right())
				s.push(new snode(temp->right()));
			s.push(new snode(temp));
			temp = temp->left();
		}
		else if((temp1 = s.pop())){
			if((temp2 = s.pop()) && temp2 && (temp2->data() == temp1->data()->right())){
				s.push(temp1);
				temp = temp2->data();
			}
			else{
				s.push(temp2);
				temp1->data()->setHeight();
				cout<<temp1->data()->data()<<" : "<<temp1->data()->height()<<endl;
				delete temp1;
			}
		}
		else{
			break;
		}
	}
}

void binaryTree::heightRec(){
	if(!root){
		return;
	}
	binaryTree(root->left()).heightRec();
	binaryTree(root->right()).heightRec();
	root->setHeight();
	cout<<root->data()<<" : "<<root->height()<<endl;
}
/* Binary Tree - START */

int main(){
	// Binary Tree
	node I('I', NULL, NULL);
	node H('H', NULL, NULL);
	node G('G', NULL, &H);
	node F('F', &I, NULL);
	node C('C', &G, &F);
	node E('E', NULL, NULL);
	node D('D', NULL, NULL);
	node B('B', &D, &E);
	node A('A', &B, &C);

	binaryTree bt(&A);
	cout<<"Binary Tree:"<<endl;
	bt.prettyPrint();
	cout<<endl<<"Pre-order Traversal Recursive: ";
	bt.preOrderRec();
	cout<<endl<<"Pre-order Traversal Iterative: ";
	bt.preOrderIter();
	cout<<endl<<endl<<"In-order Traversal Recursive: ";
	bt.inOrderRec();
	cout<<endl<<"In-order Traversal Iterative: ";
	bt.inOrderIter();
	cout<<endl<<endl<<"Post-order Traversal Recursive: ";
	bt.postOrderRec();
	cout<<endl<<"Post-order Traversal Iterative: ";
	bt.postOrderIter();
	cout<<endl<<endl<<"Level-order Traversal: ";
	bt.levelOrder();
	cout<<endl<<endl<<"Height - Recursive:\n";
	bt.heightRec();
	cout<<endl<<"Height - Iterative:\n";
	bt.heightIter();
	cout<<endl<<"Height - Iterative (non stack - using parent pointer):\n"
	bt.heightIterNS();
	cout<<endl;
	return 0;
}
