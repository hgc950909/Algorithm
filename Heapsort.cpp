//2015005205_최홍규_508
#include<stdio.h>

void buildheap(int arr[],int a,int b);
void heapsort(int arr[]);
int n,k;

int main(){
    scanf("%d%d",&n,&k);
    int arr[n+2];
     for(int i=1; i<=n; i++){
        scanf("%d",&arr[i]);
    }
    heapsort(arr);
    for(int i=1; i<=k; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    for(int i=k+1; i<=n; i++){
        printf("%d ",arr[i]);
    }
    return 0;
}
void buildheap(int arr[],int a,int b){
    int i,r,child;
    r = arr[a];
    for(i=a; i*2<=b; i=child){
        child = i*2;
        if(child+1 <=b && arr[child]> arr[child+1])
            child= child+1;
        if(r<arr[child])
            break;
        else
            arr[i]=arr[child];
    }
    arr[i]=r;
}
void heapsort(int arr[]){
    for(int i=n/2; i>=1; i--){
        buildheap(arr,i,n);
    }

    for(int i=n; i>=2; i--){
     
            int temp = arr[1];
            arr[1]=arr[i];
            arr[i]=temp;
        
        buildheap(arr,1,i-1);
    }
    
}

