/*
This program uses fenwick tree to enable range sum queries and update queries.
Query and update indexes start from 0.
*/

#include<iostream>
using namespace std;

class FenwickTree{
	int size, *tree;
	int csum(int x);

public:

	FenwickTree(int *a, int n);
	void update(int pos, int val);
	int query(int l, int r);
	void print();
};

FenwickTree::FenwickTree(int *a, int n){
	size = n + 1;
	tree = new int[size]();

	for(int i = 0; i < n; ++i){
		update(i, a[i]);
	}
}

void FenwickTree::update(int pos, int val){
	for(int i = pos + 1; i < size; i += (i) & (-i)){
		tree[i] += val;
	}
}

int FenwickTree::query(int l, int r){
	return csum(r) - csum(l);
}

int FenwickTree::csum(int x){
	int sum = 0;

	for(int i = x; i > 0; i -= (i) & (-i)){
		sum+=tree[i];
	}

	return sum;
}

void FenwickTree::print(){
	for(int i = 1; i < size; ++i){
		cout<<tree[i]<<" ";
	}
	cout<<endl;
}

int main(){
	int a[] = {1, 3, 2, 5, 6, 3};
	int n = sizeof(a)/sizeof(int);

	FenwickTree f(a, n);
	f.print();
	cout<<f.query(5, 6)<<endl;
}
