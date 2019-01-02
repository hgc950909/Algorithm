//2015005205_choihonggyu_508
#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int n,node[5001];
    int ck[5001]={0};
    scanf("%d",&n);
    vector<pair<int,int> >vec[5001];
    int max=0;
    for(int i=0; i<n; i++){
        int ver,edge;
        scanf("%d%d",&ver,&edge);
        for(int j=0; j<edge; j++){
            int end,weight;
            scanf("%d%d",&end,&weight);
            vec[ver].push_back(make_pair(end,weight));
        }
    }
    priority_queue<pair<int,int> >q;
    q.push(make_pair(0,1));
    node[1] =0;
    for(int i=2; i<=n; i++){
        node[i]=0x7fffffff;
    }
    int now,nowweight;
    while(!q.empty()){
        now = q.top().second;
        nowweight = -q.top().first;
        q.pop();
        ck[now]=1;
        for(int i=0; i<vec[now].size(); i++){
            if(nowweight+vec[now][i].second<node[vec[now][i].first]){
                q.push(make_pair(-(nowweight+vec[now][i].second),vec[now][i].first));
                node[vec[now][i].first]=nowweight+vec[now][i].second;
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(node[i]>max){
            max=node[i];
        }
    }
    printf("%d",max);
    return 0;
}

