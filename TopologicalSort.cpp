//2015005205_choihonggyu_508
#include<stdio.h>
#include<vector>
using namespace std;
int stack[1002];
int top=0;
int ck[1002];
    int map[1005][1005];
int cc;
int n;
int ck1[1002];
vector<int>vec[1002];
void dfs(int a){
    if(ck1[a]==1){
        cc=1;
        return;
    }
    if(ck[a]==1){
        return;
    }
    ck1[a]=1;
    for(int i=1; i<=n; i++){
        if(map[a][i]==1){
             dfs(i);
        }
        if(cc==1){
            return;
        }
    }
    ck1[a]=0;
    stack[top]=a;
    ck[a]=1;
    top++;
}

int main(){

    scanf("%d",&n);
    int sta,end;
    
    while(scanf("%d%d",&sta,&end) !=EOF){
        map[sta][end]=1;
    }
   
    for(int i=1; i<=n; i++){
            dfs(i);
        if(cc==1){
            break;
        }
    }
    if(cc==1){
        printf("0");
        return 0;
    }
    printf("1\n");
    while(top>0){
        printf("%d ",stack[top-1]);
        top--;
    }
    return 0;
}
