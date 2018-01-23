#include<iostream>
using namespace std;

void swap(int &x, int &y){
	int t = x;
	x = y;
	y = t;
}

class MaxHeap{
		int *a, size, maxSize;

	public:

		MaxHeap(int l);
		MaxHeap(int *arr, int l);
		void topDownHeapify(int i);
		void bottomUpHeapify(int i);
		void buildHeap();
		void insert(int val);
		void changeKey(int i, int k);
		void extractMax();

		int parent(int i){
			return (i-1)/2;
		}

		int left(int i){
			return 2*i + 1;
		}

		int right(int i){
			return 2*i + 2;
		}

		int maximum(){
			return a[0];
		}
};

MaxHeap::MaxHeap(int *arr, int l){
	a = arr;
	size = l;
	maxSize = sizeof(a)/sizeof(int);
	buildHeap();
}

MaxHeap::MaxHeap(int l){
	size = 0;
	maxSize = l;
	a = new int[maxSize];
}

void MaxHeap::topDownHeapify(int i){
	int l = left(i), r = right(i);
	int j = i;
	while(r < size){
		if(a[l] > a[r]){
			j = l;
		}
		else{
			j = r;
		}

		if(a[i] > a[j]){
			break;
		}
		else{
			swap(a[i], a[j]);
			i = j;
			l = left(i);
			r = right(i);
		}
	}

	if(l == size-1 && a[l] > a[j]){
		swap(a[l], a[j]);
	}
}

void MaxHeap::bottomUpHeapify(int i){
	int p = parent(i);
	while(p > 0){
		if(a[p] < a[i]){
			swap(a[p], a[i]);
			i = p;
			p = parent(i);
		}
		else{
			break;
		}
	}

	if(a[p] < a[i]){		//If p == 0
		swap(a[p], a[i]);
	}
}

void MaxHeap::buildHeap(){
	for(int i = size/2 - 1; i >= 0; --i){
		topDownHeapify(i);
	}
}

void MaxHeap::insert(int val){
	if(size == maxSize){
		cout<<"\nOverflow!\n";
		return;
	}
	a[size++] = val;
	bottomUpHeapify(size-1);
}

void MaxHeap::changeKey(int i, int k){
	if(k < a[i]){
		a[i] = k;
		topDownHeapify(i);
	}
	else{
		a[i] = k;
		bottomUpHeapify(i);
	}
}

void MaxHeap::extractMax(){
	if(size == 0){
		cout<<"\nUnderflow!\n";
		return;
	}
	swap(a[0], a[--size]);
	topDownHeapify(0);
}

void heapSort(int *a, int n){
	MaxHeap h(a, n);
	for(int i = n; i > 0; --i){
		h.extractMax();
	}
}

int main(){
	int n;
	cin>>n;
	int *a = new int[n];

	for(int i = 0; i < n; ++i){
		cin>>a[i];
	}

	heapSort(a, n);

	for(int i = 0; i < n; ++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
