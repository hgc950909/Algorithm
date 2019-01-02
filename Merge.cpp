//2015005205_최홍규_508
#include<stdio.h>
int arr[100005];
int ans[100005];
void merge_sort(int L,int R,int arr[]);
void merge(int L,int M,int R,int arr[]);

int main(){
    int n,i;
    scanf("%d",&n);
    for(i=1; i<=n; i++){
        scanf("%d",&arr[i]);
    }
    merge_sort(1,n,arr);
    for(i=n; i>=1; i--){
        printf("%d\n",arr[i]);
    }
}


void merge_sort(int L,int R,int arr[]){
    if(L<R){
        int M=(L+R)/2;
        merge_sort(L,M,arr);
        merge_sort(M+1,R,arr);
        merge(L,M,R,arr);
    }
}
void merge(int L,int M,int R,int arr[]){
    int Ltemp=L;
    int st=L;
    int Mtemp=M+1;
    while(Mtemp<=R && Ltemp<=M){
        if(arr[Ltemp]<arr[Mtemp]){
            ans[st++]=arr[Ltemp++];
        }
        else ans[st++]=arr[Mtemp++];
    }
    while(Mtemp <= R){
        ans[st++]=arr[Mtemp++];
    }
    while(Ltemp <= M){
        ans[st++]=arr[Ltemp++];
    }
    for(int i=L; i<=R; i++){
        arr[i]=ans[i];
    }
}
