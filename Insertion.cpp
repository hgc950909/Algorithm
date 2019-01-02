//2015005205_최홍규_508
#include<stdio.h>
int main(){
    int n,key,i,j;
    scanf("%d",&n);
	int arr[n];
    for(i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
    for(i=1; i<n; i++){
        key = arr[i];
        for(j=i-1; j>=0 && arr[j]<key; j--){
            arr[j+1]=arr[j];
        }
        arr[j+1]=key;
    }
    for(i=0; i<n; i++){
        printf("%d\n",arr[i]);
    }
	return 0;
}
