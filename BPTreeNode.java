package Bptree;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class BPTreeNode {
	public int root;
	protected int size;
	protected int capacity;
	public BPTreeNode right;
	ArrayList<Data<Integer,BPTreeNode>>data;
	
	public BPTreeNode() {
		this.capacity =0;
		this.size=0;
		this.right = null;
		data = new ArrayList<Data<Integer,BPTreeNode>>();
	}
	public BPTreeNode(int capacity) {
		this.capacity = capacity;
		this.size=0;
		this.right = null;
		data = new ArrayList<Data<Integer,BPTreeNode>>();
	}
public BPTreeNode Min(BPTreeNode L, BPTreeNode R){
		if(L.size>R.size)return R;
		else return L;
	}
	public boolean IsOverflow() {
		if(capacity <size)return true;
		else return false;
	}
	public boolean IsLeaf() {
		return this instanceof LeafNode;
	}
	public boolean IsRoot() {
		if( this.root==1) return true;
		else return false;
	}
	public boolean IsUnderflow() {
		if((capacity)/2>size) return true;
		else return false;
	}
	public BPTreeNode Insert(int key,int value,BPTreeNode node,BPTreeNode root) {
		if(key>this.data.get(this.data.size()-1).getKey()) {
			root= right.Insert(key ,value ,this ,root);
			if(this.IsOverflow()) {
				root= this.split(key,value,node,root);
				return root;
			}
			else return root;
		}
		else {
			for(int i=0; i<this.data.size(); i++) {
				if(key<this.data.get(i).getKey()) {
					BPTreeNode temp = this.data.get(i).getLeft();
					root = temp.Insert(key, value, this, root);
					if(this.IsOverflow()) {
						root = this.split(key,value,node, root);
						return root;
					}
					else return root;
				}
			}
			return root;
		}
	}
	public BPTreeNode split(int key,int value,BPTreeNode node, BPTreeNode root) {
		if(this.IsRoot()) {
			BPTreeNode newnode = new BPTreeNode(this.capacity);
			BPTreeNode R = new BPTreeNode(this.capacity);
			int mid = (this.capacity+1)/2;
			int num = this.size;
			for(int i= mid+1; i<num; i++) {
				R.data.add(this.data.get(mid+1));
				R.size++;
				this.data.remove(mid+1);
				this.size--;
			}
			R.right = this.right;
			this.right = this.data.get(mid).getLeft();
			newnode.data.add(this.data.get(mid));
			newnode.data.get(0).setLeft(this);
			newnode.size++;
			this.data.remove(mid);
			this.size--;
			this.root =0;
			newnode.right=R;
			newnode.root=1;
			return newnode;	
		}
		else {
			int mid = (this.capacity+1)/2;
			BPTreeNode rightnode = new BPTreeNode(this.capacity);
			rightnode.right = this.right;
			int num = this.size;
			for(int i= mid+1; i<num; i++) {
				rightnode.data.add(this.data.get(mid+1));
				rightnode.size++;
				this.data.remove(mid+1);
				this.size--;
			}
			this.right = this.data.get(mid).getLeft();
			Data temp =new Data(this.data.get(mid).getKey(),this);
			this.data.remove(mid);
			this.size--;
			
			if((Integer)temp.getKey()>node.data.get(node.size-1).getKey()) {
				node.data.add(temp);
				node.size++;
				node.right = rightnode;
			}
			else {
				int nodesize = node.size;
				for(int i=0; i<nodesize; i++) {
					if((Integer)temp.getKey()<node.data.get(i).getKey()) {
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
    public void search(int key) {
        for(int i=0; i<this.data.size(); i++) {
            System.out.print(this.data.get(i).getKey());
            if(i!=this.data.size()-1) {
                System.out.print(",");
            }
        }
        System.out.println();
        for(int i=0; i<this.size; i++) {
            if(key<this.data.get(i).getKey()) {
                BPTreeNode next=(BPTreeNode)this.data.get(i).getLeft();
                next.search(key);
                return;
            }
            else if(key==this.data.get(i).getKey()) {
                if(i==this.size-1) {
                    this.right.search(key);
                    return;
                }
                else {
                    BPTreeNode next=(BPTreeNode)this.data.get(i+1).getLeft();
                    next.search(key);
                    return;
                }
            }
        }
        this.right.search(key);
    }
    
    public void searchrange(int key1,int key2) {
        for(int i=0; i<this.size; i++) {
            if(key1<this.data.get(i).getKey()) {
                BPTreeNode next=(BPTreeNode)this.data.get(i).getLeft();
                next.searchrange(key1,key2);
                return;
            }
            else if(key1==this.data.get(i).getKey()) {
                if(i==this.size-1) {
                    this.right.searchrange(key1,key2);
                    return;
                }
                else {
                    BPTreeNode next=(BPTreeNode)this.data.get(i+1).getLeft();
                    next.searchrange(key1,key2);
                    return;
                }
            }
        }
        this.right.searchrange(key1,key2);
    }
	
	public int findpos(BPTreeNode node,int key) {
		for(int i=0; i<node.size; i++) {
			if(key<node.data.get(i).getKey()) {
				return i;
			}
		}
		return -1;
	}
	public BPTreeNode getpos(BPTreeNode root,int key) {
		BPTreeNode node =root;
		int j=0;
		while(!node.IsLeaf()) {
			for(int i=0; i<node.size; i++) {
				if(key==node.data.get(i).getKey()) {
					return node;
				}
			}
			for(j=0; j<node.size; j++) {
				if(key<node.data.get(j).getKey()) {
					node= node.data.get(j).getLeft();
					break;
				}
			}
			if(j == node.size) {
				node=node.right;
			}
		}
		return null;
	}
	public int getkey(BPTreeNode node,int key) {
		for(int i=0; i<node.size; i++) {
			if(node.data.get(i).getKey() == key) {
				if(i==node.size-1) {
					node=node.right;
					break;
				}
				else {
					node=node.data.get(i+1).getLeft();
					break;
				}
			}
		}
		while(!node.IsLeaf()) {
			node=node.data.get(0).getLeft();
		}
		return node.data.get(0).getKey();
	}
	public BPTreeNode Merge_Node(int key,BPTreeNode L, BPTreeNode R,BPTreeNode node,BPTreeNode root) {
		int pos=0;
		BPTreeNode newnode = new BPTreeNode(this.capacity);
		if(R.size ==0) {
			pos= findpos(node,key);
		}
		else {
			pos=findpos(node,R.data.get(0).getKey());
		}
		
		if(this.IsLeaf()) {
			for(int i=0; i<R.size; i++) {
				L.data.add(R.data.get(0));
				L.size++;
				R.data.remove(0);
				R.size--;
			}
			BPTreeNode rr=R.right;
			L.right = rr;
		
			if(pos != -1) {
				node.data.get(pos).setLeft(L);
				node.data.remove(pos-1);
				node.size--;
			}
			else {
				node.right =L;
				node.data.remove(node.size-1);
				node.size--;
			}
		}
		else {
			Data temp;
			if(pos != -1) {
				temp = new Data(node.data.get(pos-1).getKey(),L.right);
			}
			else {
				temp = new Data(node.data.get(node.size-1).getKey(),L.right);
			}
			L.data.add(temp);
			L.size++;
			for(int i=0; i<R.size; i++) {
				L.data.add(R.data.get(0));
				L.size++;
				R.data.remove(0);
				R.size--;
			}
			L.right = R.right;
			if(pos != -1) {
				node.data.get(pos).setLeft(L);
				node.data.remove(pos-1);
				node.size--;
			}
			else {
				node.right = L;
				node.data.remove(node.size-1);
				node.size--;
			}
		}
		return root;
	}
	public BPTreeNode Merge(int key,BPTreeNode node, BPTreeNode root, BPTreeNode L,BPTreeNode R) {
		BPTreeNode min,newnode;
		int pos;
		if(R==null) {
			min=L;
			root= Merge_Node(key,min,this,node,root);
		}
		else if(L==null){
			min=R;
			root = Merge_Node(key,this,min,node,root);
		}
		else if(R != null && L!=null) {
			if(L.size <= R.size) {
				min=L;
				root= Merge_Node(key,min,this,node,root);
			}
			else {
				min=R;
				root = Merge_Node(key,this,min,node,root);
			}
		}
		if(root.size ==0) {
			root.right.root =1;
			return root.right;
		}
		else {
			return root;
		}
	}
	public BPTreeNode dealUnderflow(int key,BPTreeNode node, BPTreeNode root, BPTreeNode L,BPTreeNode R) {
	
		if(L==null) {
			if(R.size>(this.capacity)/2) {
				Data temp1;
				int pos = findpos(node,key);
				temp1 = new Data(node.data.get(pos).getKey(),this.right);
				this.data.add(temp1);
				this.size++;
				node.data.get(pos).setKey(R.data.get(0).getKey());
				this.right = R.data.get(0).getLeft();
				R.data.remove(0);
				R.size--;
				return root;
			}
			else {
				root=Merge(key,node,root,L,R);
				return root;
			}
		}
		else if(R==null) {
			if(L.size>(this.capacity)/2) {
				Data temp1;
				int pos = findpos(node,L.data.get(L.size-1).getKey());
				temp1 = new Data(node.data.get(pos).getKey(),L.right);
				this.data.add(0,temp1);
				this.size++;
				node.data.get(pos).setKey(L.data.get(L.size-1).getKey());
				L.right =L.data.get(L.size-1).getLeft();
				L.data.remove(L.size-1);
				L.size--;
				return root;
			}
			else {
				root=Merge(key,node,root,L,R);
				return root;
			}
		}
		else if(Min(L,R).size>(this.capacity)/2) {
			if(Min(L,R)==L) {
				Data temp1;
				int pos = findpos(node,key);
				temp1 = new Data(node.data.get(pos).getKey(),this.right);
				this.data.add(temp1);
				this.size++;
				node.data.get(pos).setKey(R.data.get(0).getKey());
				this.right = R.data.get(0).getLeft();
				R.data.remove(0);
				R.size--;
				return root;
			}
			else {
				Data temp1;
				int pos = findpos(node,key);
				temp1 = new Data(node.data.get(pos-1).getKey(),L.right);
				this.data.add(0,temp1);
				this.size++;
				node.data.get(pos-1).setKey(L.data.get(L.size-1).getKey());
				L.right =L.data.get(L.size-1).getLeft();
				L.data.remove(L.size-1);
				L.size--;
				return root;
			}
			
		}
		else {
			root=Merge(key,node,root,L,R);
			return root;
		}
	}
	public BPTreeNode Delete(int key,BPTreeNode node,BPTreeNode root,BPTreeNode L, BPTreeNode R) {
	
		
			for(int i=0; i<this.data.size(); i++) {
				if(key< this.data.get(i).getKey()) {
					if(i==0) {
						BPTreeNode temp = this.data.get(i).getLeft();
						if(this.size==1) {
							root=temp.Delete(key,this,root,null,this.right);
							if(L ==null && R== null) {
								return root;
							}
							if(this.IsUnderflow()) {
								root=this.dealUnderflow(key,node, root, L, R);
							}
							
							return root;
						}
						else {
							BPTreeNode temp1 = this.data.get(1).getLeft();
							root=temp.Delete(key,this, root, null, temp1);
							if(L ==null && R== null) {
								return root;
							}
							if(this.IsUnderflow()) {
								root=this.dealUnderflow(key,node, root, L, R);
							}
						
							return root;
						}
					}
					else if(i==this.data.size()-1){
						BPTreeNode temp = this.data.get(i).getLeft();
						BPTreeNode temp1 = this.data.get(i-1).getLeft();
						root=temp.Delete(key,this, root, temp1, this.right);
						if(L ==null && R== null) {
							return root;
						}
						if(this.IsUnderflow()) {
							root=this.dealUnderflow(key,node, root, L, R);
						}
					
						return root;
					}
					else {
						BPTreeNode temp = this.data.get(i).getLeft();
						BPTreeNode temp1 = this.data.get(i-1).getLeft();
						BPTreeNode temp2 = this.data.get(i+1).getLeft();
						root=temp.Delete(key,this, root, temp1, temp2);
						if(L ==null && R== null) {
							return root;
						}
						if(this.IsUnderflow()) {
							root=this.dealUnderflow(key,node, root, L, R);
						}
					
						return root;
					}
				} 
			}
			if(key>=this.data.get(this.data.size()-1).getKey()) {
				BPTreeNode temp = this.right;
				BPTreeNode temp1 = this.data.get(this.size-1).getLeft();
				root=temp.Delete(key,this,root,temp1,null);
				if(L ==null && R== null) {
					return root;
				}
				if(this.IsUnderflow()) {
					root=this.dealUnderflow(key,node, root, L, R);
				}
			
				return root;
			}
		return root;
	}
	public void write(PrintWriter output) {
		for(int i=0; i<this.size; i++) {
			if(this.data.get(i).getLeft().IsLeaf()) {
				output.print("Leaf ");
			}
			output.print(this.data.get(i).getKey()+" ");
			this.data.get(i).getLeft().write(output);
		}
		if(this.right.IsLeaf()) {
			output.print("Leaf ");
		}
		output.print("right ");
		this.right.write(output);
	}
	public LeafNode read(Scanner S,LeafNode L) {
		String word;
		while(true) {
			word = S.next();
			if(word.equals("Leaf")) {
				LeafNode temp = new LeafNode(this.capacity);
				String next = S.next();
				if(next.equals("right")) {
					this.right=temp;
					L = temp.read(S, L);
					break;
				}
				else {
					Data d = new Data(Integer.parseInt(next),temp);
					this.data.add(d);
					this.size++;
					L = temp.read(S, L);
				}
			}
			else if(word.equals("right")) {
				BPTreeNode temp = new BPTreeNode(this.capacity);
				this.right =temp;
				L = temp.read(S, L);
				break;
			}
			else {
				BPTreeNode temp = new BPTreeNode(this.capacity);
				Data d= new Data(Integer.parseInt(word),temp);
				this.data.add(d);
				this.size++;
				L = temp.read(S, L);
			}
		}
		return L;
	}
}

