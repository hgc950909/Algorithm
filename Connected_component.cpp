//2015005205_choihonggyu_A
#include <stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int rankk[1002];
int parent[1002];
int connect[1002];
int find(int a){
    if(parent[a]==a){
        return a;
    }
    return parent[a] = find(parent[a]);
}
void Union(int a,int b){
    if(rankk[a] > rankk[b]){
        parent[b] = a;
    }
    else{
        parent[a] = b;
        if(rankk[a] == rankk[b]){
            rankk[b]++;
        }
    }
}
int main(){
    int ans=0;
    int cnt=1;
    int n,e,r;
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        parent[i]=i;
    }
    while(scanf("%d%d",&e,&r)!=EOF){
        int a= find(e);
        int b = find(r);
        if(a != b){
             Union(a,b);
        }
    }
    for(int i=1; i<=n; i++){
        int temp = find(i);
        if(connect[parent[temp]]==0){
            connect[parent[temp]]=cnt;
            cnt+=1;
            ans++;
        }
    }
    printf("%d\n",ans);
    for(int i=1; i<=n; i++){
        printf("%d\n",connect[parent[i]]);
    }
    
    
}
