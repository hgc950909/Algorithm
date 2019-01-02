//2015005205_최홍규_508
#include<stdio.h>
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int a[k+1],b[k+1];
    for(int i=0; i<k; i++){
        scanf("%d%d",&a[i],&b[i]);
    }
    int arr[n+1];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    int count[m+1];
    for(int i=0; i<=m; i++)
        count[i]=0;
    for(int i=0;i<n; i++)
        count[arr[i]]++;
    for(int i=1; i<=m; i++)
        count[i]=count[i]+count[i-1];
    for(int i=0; i<k; i++)
        printf("%d\n",count[b[i]]-count[a[i]-1]);
    return 0;
}

