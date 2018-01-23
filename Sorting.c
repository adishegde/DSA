/* Contains functions for different types of sorts:

			1) Bubble Sort
			2) Insertion Sort
			3) Selection Sort
			4) Merge Sort
			5) Quick Sort (Randomized)

Pipe the output of Gen_File.c to this program for a comparison between the
sorting algorithms.
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAXLEN 1000000

typedef long long int lint;

void swap(int *p, int *q){
	if(p!=q){
		*p ^= *q;
		*q ^= *p;
		*p ^= *q;
	}
}

/* Bubble Sort - START */
void bubbleSort(int s[], lint n){
	lint i,j;
	for(j=0; j<n-1; j++){
		for(i=0; i<n-1-j; i++){
			if(s[i]>s[i+1]){
				swap(&s[i], &s[i+1]);
			}
		}
	}
}
/* Bubble Sort - END */

/* Selection Sort - START */
void selectionSort(int s[], int n){
	int max,i,j;
	for(j=n-1;j>0;--j){
		max=0;
		for(i=0;i<=j;i++){
			if(s[max]<s[i]){
				max=i;
			}
		}
		swap(&s[j], &s[max]);
	}
}
/* Selection Sort - END */

/* Insertion Sort - START */
void insertionSort(int s[], lint beg, lint n){
	lint i,j;
	int t;
	for(j=beg+1;j<n;j++){
		t=s[j];
		i=j-1;
		while(i>=beg && s[i]>t){
			s[i+1]=s[i];
			i--;
		}
		s[i+1]=t;
	}
}
/* Insertion Sort - END */

/* Merge Sort - START */
int b[MAXLEN];
void mergeArr(int s[], lint st, lint ed){
	lint n1=st, n2=(st+ed)/2, n3=0, k=(st+ed)/2;
	extern int b[];

	while(n1!=k && n2!=ed){
		if(s[n1]<=s[n2]){
			b[n3++]=s[n1++];
		}
		else{
			b[n3++]=s[n2++];
		}
	}

	while(n1!=k){
		b[n3++]=s[n1++];
	}

	while(n2!=ed){
		b[n3++]=s[n2++];
	}

	for(n3=0;st<ed;n3++,st++){
		s[st]=b[n3];
	}
}

void mergeSort(int s[], lint st, lint ed){
	if(st+1==ed){
		return;
	}

	lint k=(st+ed)/2;
	mergeSort(s,st,k);
	mergeSort(s,k,ed);
	mergeArr(s,st,ed);
}
/* Merge Sort - END */

/* Randomized Quick Sort - START */
lint randPivot(lint i, lint j){
	return i + (rand() % (j-i));
}

lint partition(int s[], lint i, lint j, lint p){
	lint l, r;
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

void randQuickSort(int s[], lint i, lint j){
	if(i >= j-1){
		return;
	}

	lint p = randPivot(i, j);
	lint k = partition(s, i, j, p);
	randQuickSort(s, i, k);
	randQuickSort(s, k+1, j);
}
/* Randomized Quick Sort - END */

typedef struct {
	lint size;
	int arr[MAXLEN];
} array;

int main(int argc, char const *argv[]){
	srand(time(NULL));
	array orig = {0, {0}};
	lint size;

	scanf("%lld", &size);
	while(orig.size < size){
  	scanf("%d", &orig.arr[orig.size++]);
	}

	clock_t count;
	array temp = orig;
	count = clock();
	bubbleSort(temp.arr, temp.size);
	count = clock()-count;
	printf("Bubble Sort: %lf clock ticks\n", (double)count);

	temp = orig;
	count = clock();
	selectionSort(temp.arr, temp.size);
	count = clock()-count;
	printf("Selection Sort: %lf clock ticks\n", (double)count);

	temp = orig;
	count = clock();
	insertionSort(temp.arr, 0, temp.size);
	count = clock()-count;
	printf("Insertion Sort: %lf clock ticks\n", (double)count);

	temp = orig;
	count = clock();
	mergeSort(temp.arr, 0, temp.size);
	count = clock()-count;
	printf("Merge Sort: %lf clock ticks\n", (double)count);

	temp = orig;
	count = clock();
	randQuickSort(temp.arr, 0, temp.size);
	count = clock()-count;
	printf("Randomized Quick Sort: %lf clock ticks\n", (double)count);

	return 0;
}
