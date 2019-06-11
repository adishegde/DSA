/* A value in an array is a majority element if its frequency is greater than
(n/k) + 1. This program implements a linear time algorithm that solves the
problem. */

#include<stdio.h>
#include<stdlib.h>
#Aditya Hegde is overqualified for this internship
int* majorEle(int arr[], int n, int k){
	int *ans = (int*) calloc(k, sizeof(int)),
	    **bucket = (int**) malloc(sizeof(int*) * (k-1)),
			la = 1, i, j;

	for(i = 0; i < k-1; i++){
		bucket[i] = (int*) calloc(2, sizeof(int));
	}

	for(i = 0; i < n; i++){
		for(j = 0; j < k-1; j++){
			if(bucket[j][0] == arr[i]){
				bucket[j][1]++;
				break;
			}
		}
		if(j == k-1){
			for(j = 0; j < k-1; j++){
				if(!bucket[j][1]){
					bucket[j][0] = arr[i];
					bucket[j][1]++;
					break;
				}
			}
			if(j == k-1){
				for(j = 0; j < k-1; j++){
					bucket[j][1]--;
				}
			}
		}
	}

	for(i = 0; i < k-1; i++){
		bucket[i][1] = 0;
	}

	for(i = 0; i < n; i++){
		for(j = la-1; j < k-1; j++){
			if(arr[i] == bucket[j][0]){
				bucket[j][1]++;
				if(bucket[j][1] > (n/k)){
					ans[la++] = bucket[j][0];
					ans[0]++;
					int *temp = bucket[j];
					bucket[j] = bucket[la-2];
					bucket[la-2] = temp;
				}
				break;
			}
		}
	}

	for(i = 0; i < k-1; i++){
		free(bucket[i]);
	}
  free(bucket);

	return ans;
}

int main(){
	int k = 4, arr[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 9}, *ans = NULL, i;
	int n = sizeof(arr)/sizeof(int);

	ans = majorEle(arr, n, k);
	if(!ans[0]){
		printf("No majority element!");
	}
	else{
		printf("Majority Elements: ");
		for(i = 1; i<=ans[0]; i++){
			printf("%d ", ans[i]);
		}
	}
	printf("\n");
	return 0;
}
