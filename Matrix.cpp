
//2015005205_理쒗솉洹�_508
#include<stdio.h>
int s[103][103];
int num[103];
int min(int a,int b){
    if(a>b)return b;
    else return a;
}
void backtrack(int x,int y){
    if(y-x<=1){
        return;
    }
    if(s[x][y]-(x-1)>1){
        num[x-1]+=1;
        num[s[x][y]]+=10;
        backtrack(x,s[x][y]);
    }
    if(y-s[x][y]>1){
        num[s[x][y]]+=1;
        num[y]+=10;
        backtrack(s[x][y]+1,y);
    }
}

int main(){
    int n;
    int arr[103];
    int m[103][103];
    
    scanf("%d",&n);
    for(int i=0; i<=n; i++){
        scanf("%d",&arr[i]);
    }
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            if(i==j){
                m[i][j]=0;
            }
            else m[i][j]=0x7fffffff;
        }
    }
    for(int i=1; i<=n-1; i++){
        for(int j=1; j<=n-i; j++){
            for(int k=j; k<=j+i-1; k++){
                if(m[j][j+i]>m[j][k]+m[k+1][j+i]+arr[j-1]*arr[k]*arr[j+i]){
                    m[j][j+i]=m[j][k]+m[k+1][j+i]+arr[j-1]*arr[k]*arr[j+i];
                    s[j][j+i]=k;
                }
            }
        }
    }
    printf("%d\n",m[1][n]);
    
    backtrack(1,n);
    printf("( ");
    for(int i=0; i<=n; i++){
        if(i!=0){
            printf("%d ",i);
        }
        while(num[i]>=10 && num[i]/10!=0){
            printf(") ");
            num[i]-=10;
        }
        
        while(num[i]!=0){
            printf("( ");
            num[i]-=1;
        }
    }
    printf(") ");
    return 0;
}
