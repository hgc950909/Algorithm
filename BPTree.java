package Bptree;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.StringTokenizer;

public class BPTree{
	
	static void create(String filename, BPTreeNode root) {
		PrintWriter output =null;
		try {
			String file = System.getProperty("user.dir");
			output = new PrintWriter(new BufferedOutputStream(new FileOutputStream(file+ "\\" + filename)));
			output.print("1" + " " + root.capacity + " q\n" );
			output.close();
		}
		catch(IOException e) {
			 e.printStackTrace();
		}
	}
	static BPTreeNode read(String datafile,String input,String mode) {
		BPTreeNode node = null;
		try {
			String file = System.getProperty("user.dir");
			
			Scanner S = new Scanner(new BufferedInputStream(new FileInputStream(file + "\\" + datafile)));
			String leaf = S.next();
			String size = S.next();
			if(leaf.equals("1")) {
				node = new LeafNode(Integer.parseInt(size));
				node.root=1;
				node.read(S,null);
			}
			else {
				node = new BPTreeNode(Integer.parseInt(size));
				node.root=1;
				node.read(S,null);
			}
			if(mode.equals("i")) {
				node=insertNode(node,input);
				
			}
			else if(mode.equals("d")) {
				node=deleteNode(node,input);
			}
			
			S.close();	
		}
		catch(FileNotFoundException e) {
			 e.printStackTrace();
			
		}
		catch(Exception e){
			System.out.println(e.getMessage());
		
		}
	
		return node;
	}
	static BPTreeNode insertNode(BPTreeNode root, String input) {
		BufferedReader br = null;
		FileReader fr =null;
		try {
			fr = new FileReader(input);
			br = new BufferedReader(fr);
			String line = br.readLine();
 			while(line !=null) {
				StringTokenizer st = new StringTokenizer(line,",");
				while(st.hasMoreTokens()) {
					int key = Integer.parseInt(st.nextToken());
					int value = Integer.parseInt(st.nextToken());
					root = root.Insert(key, value,root, root );
				}
				line=br.readLine();
			}
		}
		catch(IOException e) {
			System.out.println(e.getMessage());
		}
		finally {
			try {
				fr.close();
				br.close();
			}
			catch(IOException e) {
				 e.printStackTrace();
			}
		}
		return root;
	}
	static BPTreeNode deleteNode(BPTreeNode root,String delete) {
		BufferedReader br = null;
		FileReader fr =null;
		try {
			fr = new FileReader(delete);
			br = new BufferedReader(fr);
			String line = br.readLine();
 			while(line !=null) {
					int key = Integer.parseInt(line);
					if(root.size!=0) {
						root = root.Delete(key,root,root,null,null);
						BPTreeNode tt = root.getpos(root,key);
						if(tt!=null) {
							for(int j=0; j<tt.size; j++) {
								if(key == tt.data.get(j).getKey()) {
									int min = tt.getkey(tt,key);
									tt.data.get(j).setKey(min);
								}
							}
						}
					}
					
				line=br.readLine();
			}
		}
		catch(IOException e) {
			System.out.println(e.getMessage());
		}
		finally {
			try {
				fr.close();
				br.close();	
			}
			catch(IOException e) {
				 e.printStackTrace();
			}
		}
		return root;
	}
	static void searchKey(String datafile,int key) {
		BPTreeNode root = null;
		try {
			String file = System.getProperty("user.dir");
			Scanner S = new Scanner(new BufferedInputStream(new FileInputStream(file + "\\" + datafile)));
			String leaf = S.next();
			String size = S.next();
			if(leaf.equals("1")) {
				root = new LeafNode(Integer.parseInt(size));
				root.root=1;
				root.read(S,null);
			}
			else {
				root = new BPTreeNode(Integer.parseInt(size));
				root.root=1;
				root.read(S,null);
			}
			root.search(key);
			S.close();	
		}
		catch(FileNotFoundException e) {
			 e.printStackTrace();
		}
		catch(Exception e){
			System.out.println(e.getMessage());
		}
	}
	static void searchRange(String datafile, int key1,int key2) {
		BPTreeNode root = null;
		try {
			String file = System.getProperty("user.dir");
			Scanner S = new Scanner(new BufferedInputStream(new FileInputStream(file + "\\" + datafile)));
			String leaf = S.next();
			String size = S.next();
			if(leaf.equals("1")) {
				root = new LeafNode(Integer.parseInt(size));
				root.root=1;
				root.read(S,null);
			}
			else {
				root = new BPTreeNode(Integer.parseInt(size));
				root.root=1;
				root.read(S,null);
			}
			root.searchrange(key1, key2);
			S.close();	
		}
		catch(FileNotFoundException e) {
			 e.printStackTrace();
		}
		catch(Exception e){
			System.out.println(e.getMessage());
		}
	}
	public static void main(String[] args) {
		String com = args[0];
		String file = System.getProperty("user.dir");
		PrintWriter output = null;
		if(com.equals("-c")) {
			String datafile = args[1];
			int capacity = Integer.parseInt(args[2]);
			LeafNode root = new LeafNode(capacity-1);
			root.root =1;
			create(datafile,root);
		}
		else if(com.equals("-i")) {
			String datafile = args[1];
			String inputfile = args[2];
			BPTreeNode temp=read(datafile,inputfile,"i");
			try {
				output =new PrintWriter(new BufferedOutputStream(new FileOutputStream(file+ "\\" + datafile)));
				if(temp instanceof LeafNode) {
					output.print("1" + " " + temp.capacity + " ");
				}
				else {
					output.print("0" + " " + temp.capacity + " ");
				}
				
				temp.write(output);
				output.close();
			}
			catch(IOException e) {
				System.out.println(e.getMessage());
			}
			
		}
		else if(com.equals("-d")) {
			String datafile = args[1];
			String deletefile = args[2];
			BPTreeNode temp=read(datafile,deletefile,"d");
			try {
				output =new PrintWriter(new BufferedOutputStream(new FileOutputStream(file+ "\\" + datafile)));
				if(temp instanceof LeafNode) {
					output.print("1" + " " + temp.capacity + " ");
				}
				else {
					output.print("0" + " " + temp.capacity + " ");
				}
				temp.write(output);
				output.close();
			}
			catch(IOException e) {
				System.out.println(e.getMessage());
			}
			
			
		}
		else if(com.equals("-s")) {
			String datafile = args[1];
			int searchkey = Integer.parseInt(args[2]);
			searchKey(datafile, searchkey);
		}
		else if(com.equals("-r")) {
			String datafile = args[1];
			int searchkey1 = Integer.parseInt(args[2]);
			int searchkey2 =Integer.parseInt(args[3]);
			searchRange(datafile ,searchkey1,searchkey2);
		}
	}
}
	
