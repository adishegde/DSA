#include<iostream>
#include<stdlib.h>
using namespace std;

class AVL{
	struct node{
		int data, height;
		node *left, *right;

		node(int d, node *l = NULL, node *r = NULL){
			height = 0;
			data = d;
			left = l;
			right = r;
		}
	} *root;

	int get_height(node *x){
		if(!x) return -1;
		else return x->height;
	}

	void set_height(node *x){
		x->height = AVL::max(get_height(x->left), get_height(x->right)) + 1;
	}

	int balance_factor(node *x){
		return get_height(x->left) - get_height(x->right);
	}

	static int max(int x, int y){
		return ((x > y) ? x : y);
	}

	void right_rotate(node *&x){
		node *newParent = x->left;
		node *moveSubTree = newParent->right;

		newParent->right = x;
		x->left = moveSubTree;
		set_height(x);

		x = newParent;
	}

	void left_rotate(node *&x){
		node *newParent = x->right;
		node *moveSubTree = newParent->left;

		newParent->left = x;
		x->right = moveSubTree;
		set_height(x);

		x = newParent;
	}

	void rebalance(node *&x);
	bool insert(node *&x, int k);
	bool delete_node(node *&x, int k);
	AVL::node* inorder_predecessor(node *x);
	void pretty_print(node *x, int indent);
	void inorder_traversal(node *x);

public:

	AVL(node *rt = NULL){
		root = rt;
	}

	bool insert(int k){
		return insert(root, k);
	}

	bool search(int k);

	bool delete_node(int k){
		return delete_node(root, k);
	}

	void pretty_print(){
		pretty_print(root, 0);
	}

	void inorder_traversal(){
		inorder_traversal(root);
	}
};

bool AVL::search(int k){
	node *temp = root;
	while(temp){
		if(k > temp->data) temp = temp->right;
		else if(k < temp->data) temp = temp->left;
		else return true;
	}
	return false;
}

void AVL::rebalance(node *&x){
	node *&heavyChild = (get_height(x->left) > get_height(x->right)) ? x->left : x->right;

	int bfhc = balance_factor(heavyChild), bfx = balance_factor(x);

	//zig-zag : rotation  of child
	if(bfhc * bfx < 0){
		(bfhc == -1) ? left_rotate(heavyChild) : right_rotate(heavyChild);
	}

	//zig-zag : rotation of parent
	//zig-zig
	(bfx < 0) ? left_rotate(x) : right_rotate(x);
}

bool AVL::insert(node *&x, int k){
	if(!x){
		x = new node(k);
		//Overflow
		if(!x) return false;
		return true;
	}

	bool retVal;

	if(k > x->data) retVal = insert(x->right, k);
	else if(k < x->data) retVal = insert(x->left, k);
	else return false;

	if(abs(balance_factor(x)) > 1) rebalance(x);
	set_height(x);

	return retVal;
}

bool AVL::delete_node(node *&x, int k){
	if(!x) return false;

	bool retVal;

	if(k > x->data) retVal = delete_node(x->right, k);
	else if(k < x->data) retVal = delete_node(x->left, k);
	else{
		//1 or 0 children
		if(!x->left || !x->right){
            node *temp = x->left ? x->left : x->right;

			delete x;
			x = NULL;
			//1 child
            if(temp) x = temp;
			return true;
        }
		//2 children
        else{
            node *temp = inorder_predecessor(x);
            x->data = temp->data;
            retVal = delete_node(x->left, temp->data);
        }
	}

	if(abs(balance_factor(x)) > 1)	rebalance(x);
	set_height(x);

	return retVal;
}

AVL::node* AVL::inorder_predecessor(node *x){
	x = x->left;

	while(x->right){
		x = x->right;
	}

	return x;
}

void AVL::inorder_traversal(node *x){
	if(!x){
		return;
	}

	inorder_traversal(x->left);
	cout<<x->data<<" ";
	inorder_traversal(x->right);
}

void AVL::pretty_print(node *x, int indent){
	if(!x){
		return;
	}
	for(int i = 0; i < indent; ++i){
		cout<<"\t";
	}
	cout<<x->data<<endl;
	pretty_print(x->left, indent+1);
	pretty_print(x->right, indent+1);
}

int main(){
	AVL t;
	int n, k;
	while(true){
		cout<<"1 - Insert \n2 - Delete \n3 - Search \n4 - In-order traversal \n5 - Exit \nChoice: ";
		cin>>n;
		cout<<endl;

		switch(n){
			case 1:
				cout<<"Number to insert: ";
				cin>>k;
				if(t.insert(k)) cout<<"Insertion successful!\n";
				else cout<<"Insertion unsuccessful!\n";
				break;

			case 2:
				cout<<"Number to delete: ";
				cin>>k;
				if(t.delete_node(k)) cout<<"Deletion successful!\n";
				else cout<<"Deletion unsuccessful!\n";
				break;

			case 3:
				cout<<"Number to search: ";
				cin>>k;
				if(t.search(k)) cout<<"Found number!\n";
				else cout<<"Number not present in tree!\n";
				break;

			case 4:
				t.inorder_traversal();
				cout<<endl;
				break;

			case 5:
				exit(0);

			default:
				cout<<"Invalid choice!";
		}
		cout<<"\nTree:\n";
		t.pretty_print();
		cout<<endl<<endl;
	}
	return 0;
}
