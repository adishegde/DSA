#include<iostream>
#include<vector>
using namespace std;

// Using int as elements of set instead of generics to avoid overhead
// in CP problems. Use Map externally for other data types.

// Elements are numbered from 0
class UnionFind {
	// Maintains parent of each node, -1 indicates node is root
	vector<int> tree;
	// Maintains rank for subtrees
	vector<int> rank;
	// Maintains size of subtrees
	vector<int> sizes;
	// Number of subsets
	int count;
public:
	UnionFind(int size = 0);
	int add(); // Add new element, return value is new elements number
	int unite(int x, int y); // Union of set containing element x and y
	int find(int x); // Find set number of element number x
	int sizeOf(int x); // Find size of set containg element x
	int numSets(); // Number of sets
};

UnionFind::UnionFind(int size) : tree(size, -1), rank(size, 1), sizes(size, 1) {
	count = size;
}

int UnionFind::add() {
	tree.push_back(-1);
	rank.push_back(1);
	sizes.push_back(1);
	count++;

	return tree.size() - 1;
}

int UnionFind::unite(int x, int y) {
	int a = find(x), b = find(y);
	if(a == b) return a;

	int rl = a, rg = b;
	if(rank[rl] > rank[rg]) rg = a, rl = b;
	else if(rank[rl] == rank[rg]) rank[rg]++;

	tree[rl] = rg;
	count--;
	sizes[rg] += sizes[rl];
	return rg;
}

int UnionFind::find(int x) {
	if(tree[x] == -1) return x;

	if(tree[x] != tree[tree[x]]) tree[x] = find(tree[x]);
	return tree[x];
}

int UnionFind::sizeOf(int x) {
	return sizes[find(x)];
}

int UnionFind::numSets() {
	return count;
}

int main() {
	UnionFind uf(5);
	cout<<uf.numSets()<<endl;

	uf.unite(0,1);
	uf.unite(2,3);
	uf.unite(3,4);

	cout<<uf.numSets()<<endl;
	cout<<uf.find(0)<<' '<<uf.find(1)<<endl; // 1
	cout<<uf.find(2)<<' '<<uf.find(3)<<endl; // 1
	cout<<uf.find(3)<<' '<<uf.find(4)<<endl; // 1
	cout<<uf.find(2)<<' '<<uf.find(4)<<endl; // 1

	cout<<endl<<endl;

	cout<<uf.find(0)<<' '<<uf.find(4)<<endl; // 0
	cout<<uf.find(1)<<' '<<uf.find(4)<<endl; // 0
	cout<<uf.find(0)<<' '<<uf.find(3)<<endl; // 0
	cout<<uf.find(1)<<' '<<uf.find(3)<<endl; // 0
	cout<<uf.find(0)<<' '<<uf.find(2)<<endl; // 0
	cout<<uf.find(1)<<' '<<uf.find(2)<<endl; // 0

	uf.add();
	cout<<uf.numSets()<<endl;
	cout<<uf.find(0)<<' '<<uf.find(5)<<endl; // 0
	cout<<uf.find(1)<<' '<<uf.find(5)<<endl; // 0
	cout<<uf.find(2)<<' '<<uf.find(5)<<endl; // 0
	cout<<uf.find(3)<<' '<<uf.find(5)<<endl; // 0
	cout<<uf.find(4)<<' '<<uf.find(5)<<endl; // 0

	return 0;
}
