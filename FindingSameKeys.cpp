//2015005205_choihonggyu_508
#include<stdio.h>

int main(){
    int n,m,ck,cnt=0,nn[100002];
    scanf("%d%d",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%d",&ck);
        nn[ck]++;
    }
    for(int i=0; i<m; i++){
        scanf("%d",&ck);
        if(nn[ck]==1)
            cnt++;
    }
    printf("%d",cnt);
}

