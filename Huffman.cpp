//2015005205_理쒗솉洹�_508
#include<stdio.h>
struct str{
    char code[5];
    int num;
    int left;
    int right;
};
void insert(str arr[],str key,int len);
str minkey(str arr[],int len);
void buildheap(str arr[],int a,int b);
void search(str tree[],int now,int height);
str arr[30005];
int len=0;
int ans;
int main(){
    int n,total;
    int count=1;
    int temp=1;
    scanf("%d",&n);
    str str1[n];
    for(int i=1; i<=n; i++){
        scanf("%s%d",str1[i].code,&str1[i].num);
        str1[i].left=0;
        str1[i].right=0;
    }
    scanf("%d",&total);
    while(n>temp){
        temp*=2;
        count++;
    }
    printf("%d\n",(count-1)*total);
    for(int i=1; i<=n; i++){
        if(len==0){
            arr[1]=str1[i];
        }
        else{
            insert(arr,str1[i],len);
        }
        len++;
    }
    str tree[100000];
    int ck=0;
    while(len >0){
        
        ck++;
        tree[ck]= minkey(arr, len);
        len--;
        ck++;
        tree[ck] = minkey(arr,len);
        len--;
        ck++;
        tree[ck].num = tree[ck-2].num+tree[ck-1].num;
        tree[ck].left = ck-2;
        tree[ck].right = ck-1;
        if(len==0){
            break;
        }
        insert(arr,tree[ck],len);
        len++;
    }
    search(tree,ck,0);
    printf("%d",ans);
    return 0;
}

void buildheap(str arr[],int a,int b){
    int i,r,child;
    str temp;
    r=arr[a].num;
    temp= arr[a];
    for(i =a; i*2 <=b; i=child){
        child = i*2;
        if(child+1 <=b && arr[child].num >= arr[child+1].num)
            child = child+1;
        if(r<=arr[child].num)
            break;
        else
            arr[i]=arr[child];
    }
    arr[i]=temp;
}
void insert(str arr[],str key,int len){
    int size =len+1;
    int i;
    for(i = size; i/2>=1; i/=2){
        if(arr[i/2].num>key.num){
            arr[i]=arr[i/2];
        }
        else break;
    }
    arr[i]=key;
}
str minkey(str arr[],int len){
    str temp = arr[1];
    arr[1]=arr[len];
    buildheap(arr,1,len-1);
    
    return temp;
}
void search(str tree[],int now,int height){
    if(tree[now].left==0 && tree[now].right ==0){
        ans+=tree[now].num*height;
        return;
    }
    search(tree,tree[now].left,height+1);
    search(tree,tree[now].right,height+1);
}

