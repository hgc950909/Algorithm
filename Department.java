package Assignment2;

import java.util.ArrayList;


public class Department {
	private String name;
	private Integer depid;
	ArrayList<Candidate>can;
	ArrayList<Student>stu;
	
	public Department(String name,Integer depid){
		this.name=name;
		this.depid = depid;
		can = new ArrayList<Candidate>();
		stu = new ArrayList<Student>();
	}

	public Candidate mostvote() {
		Candidate most;
		most= can.get(0);
		for(int i=1; i<can.size(); i++) {
			if(most.getNumOfVote() < can.get(i).getNumOfVote() ) {
				most=can.get(i);
			}
		}
		return most;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public Integer getDepid() {
		return depid;
	}
	public void setDepid(Integer depid) {
		this.depid = depid;
	}
}

