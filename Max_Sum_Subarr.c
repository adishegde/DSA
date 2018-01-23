#include<stdio.h>

int maxSumSubarr(int arr[], int len){
	int j, msum, temp;
	for(j = 0, msum = 0, temp = 0; j < len; j++){
		temp += arr[j];
		if(temp < 0){
			temp = 0;
		}
		if(temp > msum){
		  msum = temp;
	  }
	}
	return msum;
}

int main(){
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
	int n = sizeof(a)/sizeof(int);
	printf("%d\n", maxSumSubarr(a, n));
}
