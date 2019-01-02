package Bptree;
import java.io.PrintWriter;
import java.util.Scanner;

public class LeafNode extends BPTreeNode{
	
	public LeafNode(int capacity) {
		this.capacity = capacity;
		this.size=0;	
	}
	public BPTreeNode Insert(int key,int value,BPTreeNode node, BPTreeNode root) {
		
		Data temp = new Data(key,value);
		int i;
		
		for(i=0; i<data.size(); i++) {
			if(key<data.get(i).getKey()) {
				break;
			}
		}
		data.add(i,temp);
		this.size++;
	
		if(this.IsOverflow()) {
			root = this.split(key,value,node,root);
		}
		return root;
	}
	public BPTreeNode split(int key,int value,BPTreeNode node,BPTreeNode root){
		if(this.IsRoot()){
			BPTreeNode newnode = new BPTreeNode(this.capacity);
			LeafNode R = new LeafNode(this.capacity);
			int mid = (this.capacity+1)/2;
			Data D = new Data(this.data.get(mid).getKey(),this);
			
			int num =this.data.size();
			for(int i= mid; i<num; i++) {
				R.data.add(this.data.get(mid));
				R.size++;
				this.data.remove(mid);
				this.size--;
			}
			R.right = this.right;
			this.right = R;
			this.root=0;
			newnode.data.add(D);
			newnode.size++;
			newnode.right=R;
			newnode.root =1;
			return newnode;
		}
		else {
			int mid = (this.capacity+1)/2;
			LeafNode rightnode = new LeafNode(this.capacity);
			rightnode.right = this.right;
			this.right = rightnode;
			int num = this.data.size();
			for(int i=mid; i<num; i++) {
				rightnode.data.add(this.data.get(mid));
				rightnode.size++;
				this.data.remove(mid);
				this.size--;
			}
			int tempkey = rightnode.data.get(0).getKey();
			
			if(tempkey>node.data.get(node.data.size()-1).getKey()) {
				Data temp = new Data(tempkey,this);
				node.data.add(temp);
				node.size++;
				node.right = rightnode;
			}
			else {
				num = node.data.size();
				for(int i=0; i<num; i++) {
					if(tempkey<node.data.get(i).getKey()) {
						Data temp = new Data(tempkey,this);
						node.data.add(i,temp);
						node.size++;
						node.data.get(i+1).setLeft(rightnode);
						break;
					}
				}
			}
			return root;
		}
	
	}
	public BPTreeNode Delete(int key,BPTreeNode node,BPTreeNode root,BPTreeNode L, BPTreeNode R) {
	if(this.IsRoot()){
		for(int i=0; i<this.size; i++) {
			int tempkey = this.data.get(i).getKey();
			if(tempkey == key) {
				this.data.remove(i);
				this.size--;
				return root;
			}
		}
	}
	if(this.IsLeaf()) {
			
			for(int i=0; i<this.size; i++) {
				int tempkey = this.data.get(i).getKey();
				if(tempkey == key) {
					this.data.remove(i);
					this.size--;
				
					
					if(!this.IsRoot() && this.IsUnderflow()) {
						if(R==null) {
							if(L.size > capacity/2) {
								int maxkey = L.data.get(L.size-1).getKey();
								node.data.get(node.size-1).setKey(maxkey);
								Data dd = L.data.get(L.size-1);
								this.data.add(0, dd);
								this.size++;
								L.data.remove(L.size-1);
								L.size--;
								return root;
							}
							else {
								root=this.Merge(key,node,root,L,R);
								return root;
							}
						}
						else if(L==null){
							if(R.size > capacity/2) {
								Data dd =R.data.get(0);
								this.data.add(dd);
								this.size++;
								R.data.remove(0);
								R.size--;
								node.data.get(0).setKey(R.data.get(0).getKey());
								return root;
							}
							else {
								root=this.Merge(key,node,root,L,R);
								return root;
							}
							
						}
						else {
							if(R.size>L.size &&L.size > capacity/2) {
								int pos = findpos(node,key);
								node.data.get(pos-1).setKey(L.data.get(L.size-1).getKey());
								Data dd =L.data.get(L.size-1);
								this.data.add(0, dd);
								this.size++;
								L.data.remove(L.size-1);
								L.size--;
								return root;
							}
							else if( L.size>R.size && R.size>capacity/2) {
								int pos = findpos(node,key);
								Data dd =R.data.get(0);
								this.data.add(dd);
								this.size++;
								R.data.remove(0);
								R.size--;
								node.data.get(pos).setKey(R.data.get(0).getKey());
								return root;
							}
							else {
								root=this.Merge(key,node,root,L,R);
								return root;
							}
						}
					}
				}
			}
		}
		return root;
	}
	public void write(PrintWriter output) {
		for(int i=0; i<this.data.size(); i++) {
			output.print(this.data.get(i).getKey() + " " + this.data.get(i).getLeft() + " ");
		}
		output.println("q");
	}
	public LeafNode read(Scanner S,LeafNode L) {
		String word;
		while(true) {
			word = S.next();
			if(word.equals("q"))break;
			String value = S.next();
			Data d= new Data(Integer.parseInt(word),Integer.parseInt(value));
			this.data.add(d);
			this.size++;
		}
		if(L != null) {
			L.right = this;
		}
		return this;
	}
    public void search(int key) {
        int j;
        LeafNode now= this;
        for(j=0; j<now.data.size(); j++) {
            if(key == now.data.get(j).getKey()) {
                System.out.println(now.data.get(j).getLeft());
                break;
            }
        }
        if(j==now.data.size()) {
            System.out.println("NOT FOUND");
        }
    }
    public void searchrange(int key1,int key2) {
        int j=0;
        BPTreeNode now = this;
        BPTreeNode next = now.right;
        while(now!=null) {
            for(j=0; j<now.data.size(); j++) {
                if(key1<= now.data.get(j).getKey() && key2>= now.data.get(j).getKey()) {
                    System.out.print(now.data.get(j).getKey());
                    System.out.print(",");
                    System.out.println(now.data.get(j).getLeft());
                }
                else return;
            }
            now=next;
            if(now!=null) {
                next=now.right;
            }
        }
    }
}
