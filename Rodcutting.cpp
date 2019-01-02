//2015005205_choihonggyu_508
#include<stdio.h>
int arr[105],dp[105],len[105];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&arr[i]);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            if(arr[j]+dp[i-j]>dp[i]){
                dp[i]=arr[j]+dp[i-j];
                len[i]=j;
            }
            
        }
    }
    printf("%d\n",dp[n]);
    while(n>0){
        printf("%d ",len[n]);
        n=n-len[n];
    }
}
