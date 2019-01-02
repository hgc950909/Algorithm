//2015005205_choihonggyu_508
#include<stdio.h>
int arr[105][2];
int temp[105][2];
int dp[3][2];
int before[105][2];
int ans=0;
int path[105];
int t;
int min(int a,int b){
    if(a>b)return b;
    else return a;
}
int main(){
    int n,e1,e2,x1,x2;
    scanf("%d",&n);
    t=n;
    scanf("%d%d%d%d",&e1,&e2,&x1,&x2);
    for(int i=1; i<=n; i++){
        scanf("%d",&arr[i][0]);
    }
    for(int i=1; i<=n; i++){
        scanf("%d",&arr[i][1]);
    }
    for(int i=1; i<n; i++){
        scanf("%d",&temp[i][0]);
    }
    for(int i=1; i<n; i++){
        scanf("%d",&temp[i][1]);
    }
    dp[1][0]=arr[1][0]+e1;
    dp[1][1]=arr[1][1]+e2;
    for(int i=2; i<=n; i++){
        
        if(dp[1][1]+temp[i-1][1]+arr[i][0]>=arr[i][0]+dp[1][0]){
            dp[2][0]=arr[i][0]+dp[1][0];
            before[i][0]=1;
        }
        else if(dp[1][1]+temp[i-1][1]+arr[i][0]<arr[i][0]+dp[1][0]){
            dp[2][0]=dp[1][1]+temp[i-1][1]+arr[i][0];
            before[i][0]=2;
        }
        if(dp[1][0]+temp[i-1][0]+arr[i][1]>arr[i][1]+dp[1][1]){
            dp[2][1]=arr[i][1]+dp[1][1];
            before[i][1]=2;
        }
        else if(dp[1][0]+temp[i-1][0]+arr[i][1]<=arr[i][1]+dp[1][1]){
            dp[2][1]=dp[1][0]+temp[i-1][0]+arr[i][1];
            before[i][1]=1;
        }
        dp[1][0]=dp[2][0];
        dp[1][1]=dp[2][1];
    }
    if(dp[2][0]+x1>dp[2][1]+x2){
        ans=dp[2][1]+x2;
        path[n]=2;
        while(n>0){
            if(path[n]==1){
                path[n-1]=before[n][0];
            }
            else{
                path[n-1]=before[n][1];
            }
            n--;
        }
        
    }
    else{
        ans=dp[2][0]+x1;
        path[n]=1;
        while(n>0){
            if(path[n]==1){
                path[n-1]=before[n][0];
            }
            else{
                path[n-1]=before[n][1];
            }
            n--;
        }
        
    }
    printf("%d\n",ans);
    for(int i=1; i<=t; i++){
        printf("%d %d\n",path[i],i);
    }
}
