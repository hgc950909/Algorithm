package Assignment2;


public class Candidate extends Student{
	private Integer numOfVote;
	
	public Candidate(String name, Integer id, Department dep) {
		super(name,id,dep);
		this.numOfVote=0;
	}
	public int compareTo(Object obj) {
		if(obj == null)throw new NullPointerException("Object is null");
		if(!this.getClass().equals(obj.getClass()))throw new ClassCastException("Object not of the same type");
		Candidate toCompare = (Candidate)obj;
		if(this.dep.getDepid() > toCompare.dep.getDepid())return 1;
		else if(this.dep.getDepid() == toCompare.dep.getDepid())return 0;
		else return -1;
	}
	
	public Integer getNumOfVote() {
		return numOfVote;
	}
	public void setNumOfVote(Integer numOfVote) {
		this.numOfVote = numOfVote;
	}
}