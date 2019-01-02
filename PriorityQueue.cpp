//2015005205_최홍규_508
#include<stdio.h>
#include<string.h>
void insert(int arr[],int key,int len);
void maxkey(int arr[],int len);
void sub(int arr[],int key1,int key2,int len);
void buildheap(int arr[],int a,int b);
int arr[100005];
int len=0;
int main(){
    int comm;
    
    while(true){
        scanf("%d",&comm);
        switch(comm){
            case 0:
				printf("\n");
                for(int i=1; i<=len; i++){
                    printf("%d ",arr[i]);
                }
				printf("\n");
                return 0;
            case 1:
                int key;
                scanf("%d",&key);
				if(len==0){
					arr[1]=key;
				}
				else
                	insert(arr,key,len);
                len++;
                break;
            case 2:
                maxkey(arr,len);
                len--;
                break;
            case 3:
                int key1,key2;
                scanf("%d%d",&key1,&key2);
				if(key1!=1&& arr[key1/2]<key2)
					insert(arr,key2,key1-1);
				else
					sub(arr,key1,key2,len);
                break;
		}
    }
    return 0;
}
void buildheap(int arr[],int a,int b){
    int i,r,child;
    r= arr[a];
    for(i =a; i*2 <=b; i=child){
        child = i*2;
        if(child+1 <=b && arr[child] <= arr[child+1])
            child = child+1;
        if(r>=arr[child])
            break;
        else
            arr[i]=arr[child];
    }
    arr[i]=r;
}
void insert(int arr[],int key,int len){
    int size =len+1;
    int i;
    for(i = size; i/2>=1; i/=2){
        if(arr[i/2]<key){
            arr[i]=arr[i/2];
        }
        else break;
    }
	arr[i]=key;
}
void maxkey(int arr[],int len){
    printf("%d ",arr[1]);
    arr[1]=arr[len];
    buildheap(arr,1,len-1);
}
void sub(int arr[],int key1,int key2,int len){
    arr[key1]=key2;
        buildheap(arr,key1,len);
    
}

