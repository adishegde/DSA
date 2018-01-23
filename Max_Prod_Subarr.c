#include<stdio.h>

int maxProdSub(int *a, int n){
	int max = 1, min = 1, maxProd = 1, i;
	for(i = 0; i < n; ++i){
		if(a[i] > 0){
			max = max * a[i];
			min = ((min*a[i]) < 1) ? (min * a[i]) : 1;
		}

		else if(a[i] == 0){
			max = 1;
			min = 1;
		}

		else{
			int temp = max;
			max = ((min*a[i]) > 1) ? (min * a[i]) : 1;
			min = temp * a[i];
		}

		if(maxProd < max){
			maxProd = max;
		}
	}

	return maxProd;
}

int main(){
	int a[] = {1, -2, -3, 0, 7, -8, -2};
	int n = sizeof(a)/sizeof(int);

	printf("%d\n", maxProdSub(a, n));
	return 0;
}
