//2015005205_최홍규_508
#include<stdio.h>

int main(){
    int n,m,min,pos=0,temp;
    scanf("%d%d",&n,&m);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
   
    for(int i=0; i<m; i++){
         min =0x7fffffff;
        for(int j=i; j<n; j++){
            if(min>arr[j]){
                min = arr[j];
                pos = j;
            }
        }
        temp=arr[i];
        arr[i]=min;
        arr[pos]=temp;
    }
    for(int i=0;i<n;i++){
        printf("%d\n",arr[i]);
    }
    return 0;
}
