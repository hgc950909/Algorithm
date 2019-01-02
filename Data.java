package Bptree;


public class Data<K,P>{
	private K key;
	private P left;
	public Data() {
		key=null;
		left=null;
	}
	public Data(K key,P left) {
		this.key =key;
		this.left =left;
	}
	public K getKey() {
		return key;
	}
	public void setKey(K key) {
		this.key = key;
	}
	public P getLeft() {
		return left;
	}
	public void setLeft(P left) {
		this.left = left;
	}
}
