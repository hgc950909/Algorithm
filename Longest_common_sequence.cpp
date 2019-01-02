//2015005205_choihonggyu_508
#include <stdio.h>
#include<string.h>
void swap(char a[],char b[]){
    char temp[505];
    strcpy(temp,b);
    strcpy(b,a);
    strcpy(a,temp);
}
int main(){
    char a[505],b[505];
    char ans[505];
    int cnt=0;
    scanf("%s%s",a,b);
    int dp[505][505];
    int way[505][505];
    if(strlen(a)>strlen(b)){
        swap(a,b);
    }
    for(int i=1; i<=strlen(a); i++){
        for(int j=1; j<=strlen(b); j++){
            if(a[i-1]==b[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
                way[i][j]=2;
            }
            else{
                if(dp[i][j-1]<=dp[i-1][j]){
                    dp[i][j]=dp[i-1][j];
                    way[i][j]=3;
                }
                else if(dp[i][j-1]>dp[i-1][j]){
                    dp[i][j]=dp[i][j-1];
                    way[i][j]=1;
                }
            }
        }
    }
    int x=strlen(b);
    int y=strlen(a);
    while(x>0 && y>0){
        if(way[y][x]==1){
            x-=1;
        }
        else if(way[y][x]==2){
            ans[cnt]= b[x-1];
            cnt++;
            x-=1;
            y-=1;
        }
        else{
            y-=1;
        }
    }
    for(int i=cnt-1; i>=0; i--){
        printf("%c",ans[i]);
    }
    return 0;
}
