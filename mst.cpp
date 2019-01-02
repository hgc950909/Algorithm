//2015005205_choihonggyu_A
#include <stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int rankk[1002];
int parent[1002];
struct weight{
    int w;
    int st;
    int end;
}edges[1002];
priority_queue<pair<int,pair<int,int> > >q;
int find(int a){
    if(parent[a]==a){
         return a;
    }
    return parent[a] = find(parent[a]);
}
void Link(int a,int b){
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
void Union(int a,int b){
    Link(find(a),find(b));
}
int main(){
    int ans=0;
    int cnt=0;
    int n,e,r,w;
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        parent[i]=i;
    }
    while(scanf("%d%d%d",&e,&r,&w)!=EOF){
        if(e>r){
            q.push(make_pair(-w,make_pair(-r,-e)));
        }
        else{
            q.push(make_pair(-w,make_pair(-e,-r)));
        }
    }
    while(!q.empty()){
        int weight =-q.top().first;
        int ee = -q.top().second.first;
        int rr = -q.top().second.second;
        q.pop();
        if(cnt ==n-1){
            break;
        }
        if(find(ee) != find(rr)){
            ans++;
            Union(ee,rr);
            edges[cnt].w=weight;
            edges[cnt].st =ee;
            edges[cnt].end =rr;
            cnt++;
        }
    }
    printf("%d\n",ans);
    for(int i=0; i<n-1; i++){
        printf("%d %d %d\n",edges[i].st,edges[i].end,edges[i].w);
    }
}
