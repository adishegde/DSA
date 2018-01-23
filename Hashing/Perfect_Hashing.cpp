#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

const int p = 1e9 + 7;	//Prime that is greater than |U| (U is universe of keys)

struct node{
	int k;
	char data[100];
};

class SecondaryHash{
	int m, a, b;
	node *t;

	int hash(int k){
		//type cast reqd to prevent overflow
		return ((a * ((long long int)k) + b) % p) % m;
	}

public:

	void set_univ_hash(){
		a = 1 + rand() % (p - 1);
		b = rand() % p;
	}

	void set_table(int n){
		m = n * n;
		t = new node[m];
	}

	void insert(node x){
		t[hash(x.k)] = x;
	}

	node search(int k){
		return t[hash(k)];
	}

	bool check(int *ind, node *arr);
};

bool SecondaryHash::check(int *ind, node *arr){
	bool *temp = new bool[m]();
	int h;

	for(int i = 1; i <= ind[0]; ++i){
		h = hash(arr[ind[i]].k);

		if(!temp[h]){
			temp[h] = true;
		}
		else{
			delete []temp;
			return false;
		}
	}

	for(int i = 1; i <= ind[0]; ++i){
		insert(arr[ind[i]]);
	}

	delete []temp;

	return true;
};

class PerfectHash{
	int m, a, b;
	SecondaryHash *t;

	int hash(int k){
		//type cast reqd to prevent overflow
		return ((a * ((long long int)k) + b) % p) % m;
	}

	void insert_elements(node *arr);

public:

	PerfectHash(node *arr, int n);

	node search(int k){
		return t[hash(k)].search(k);
	}
};

PerfectHash::PerfectHash(node *arr, int n){
	a = 1 + (rand() % (p - 1));
	b = rand() % p;
	m = n;
	t = new SecondaryHash[m];

	insert_elements(arr);
}

void PerfectHash::insert_elements(node *arr){
	//To compute the slot in which each key goes to. First column stores length.
	int **temp = new int*[m](), h;

	for(int i = 0; i < m; ++i){
		h = hash(arr[i].k);

		if(!temp[h]){
			temp[h] = new int[m - i + 1];
			temp[h][0] = 0;
		}

		temp[h][++temp[h][0]] = i;
	}

	for(int i = 0; i < m; ++i){
	    if(!temp[i]) continue;

		t[i].set_table(temp[i][0]);

		do{
			t[i].set_univ_hash();
		}while(!t[i].check(temp[i], arr));

		delete []temp[i];
	}

	delete []temp;
}

int main(){
	srand(time(NULL));

	int n;
	node *arr;

	cout<<"Number of keys: ";
	cin>>n;
	cout<<endl;

	arr = new node[n];

	for(int i = 0; i < n; ++i){
		cout<<"Key: ";
		cin>>arr[i].k;
		cout<<"Data: ";
		cin>>arr[i].data;
		cout<<endl;
	}

	PerfectHash dict(arr, n);

	int key;
	while(true){
		cout<<"Key to search: ";
		cin>>key;
		if(key < 0) break;
		cout<<"Data: "<<dict.search(key).data<<endl<<endl;
	}

	return 0;
}
