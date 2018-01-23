/* This program implements the quick select algorithm using randomized pivot
selection. The rank is defined as number of elements greater than the given
element + 1 i.e. the greatest element has rank 1. */ 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *p, int *q){
	if(p!=q){
		*p ^= *q;
		*q ^= *p;
		*p ^= *q;
	}
}

int randPivot(int i, int j){
	return i + (rand() % (j-i));
}

int partition(int s[], int i, int j, int p){
	int l, r;
	int x = s[p];

	if(p != j-1){
		swap(&s[p], &s[j-1]);
	}

	for (l = i-1, r = i; r < j-1; r++){
		if(s[r] <= x){
			swap(&s[r], &s[++l]);
		}
	}

	swap(&s[++l], &s[j-1]);
	return l;
}

int quickSelect(int arr[], int rank, int st, int ed){
	if(st == ed-1){
		return arr[st];
	}

	int pivot = randPivot(st, ed);
	int pospiv = partition(arr, st, ed, pivot);

	if(pospiv == ed - rank){
		return arr[pospiv];
	}

	else if(pospiv < ed - rank){
		return quickSelect(arr, rank, pospiv, ed);
	}

	else{
		return quickSelect(arr, rank - ed + pospiv, st, pospiv);
	}
	return -1;
}

int main(int argc, char const *argv[]){
	srand(time(NULL));
	int const n = 10;
	int rank;
	sscanf(argv[1], "%d", &rank);
	int arr[n] = {5,1,2,3,7,4,6,9,8,10};
	printf("%d\n",quickSelect(arr, rank, 0, 10));
	return 0;
}
