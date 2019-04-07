package Assignment2;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.io.*;
import java.util.StringTokenizer;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

public class ElectionSim{
	
	private String deppath;
	private String stupath;
	private String outpath;
	private BufferedReader br = null;
	private BufferedReader brstu = null;
	ArrayList<Department>department;
	ArrayList<Candidate>candidate;
	
	public ElectionSim(String a,String b, String c){
		deppath =a;
		stupath = b;
		outpath = c;
		try {
			department = new ArrayList<Department>();
			candidate = new ArrayList<Candidate>();

			br = new BufferedReader(new FileReader(new File(deppath)));
			String line = br.readLine();
			brstu = new BufferedReader(new FileReader(new File(stupath)));
			String linestu = brstu.readLine();
			//department input은 department id,department name 순서로 입력받는다.
			//각 입력 구분은 , 콤마표시로 구분한다.
			while((line=br.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(line,",");
				while(st.hasMoreTokens()) {
					String depid= st.nextToken();
					String dep=st.nextToken();
					Department tempdep = new Department(dep,Integer.parseInt(depid));
					department.add(tempdep);
				}
				
			}
			//student input은 identification number,department id,name,candidate여부 순서로 입력받는다.
			//각 입력 구분은 , 콤마표시로 구분한다.
			while((linestu = brstu.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(linestu,",");
				while(st.hasMoreTokens()) {
					Integer stuid = Integer.parseInt(st.nextToken());
					Integer deppid = Integer.parseInt(st.nextToken());
					String name = st.nextToken();
					String candi = st.nextToken();
					if(candi.equals("TRUE")) {
						Candidate tempcan = new Candidate(name, stuid,department.get(deppid-1));
						department.get(deppid-1).can.add(tempcan);
					}
					Student tempstu = new Student(name,stuid,department.get(deppid-1));
					department.get(deppid-1).stu.add(tempstu);
				}
			}
		}
		catch(FileNotFoundException e) {
			 e.printStackTrace();
		}
		catch(IOException e) {
			 e.printStackTrace();
		}
		finally{
			try {
				if(br != null)br.close();
				if(brstu != null)brstu.close();
			}
			catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	
	public void saveData() {
		try {
			Collections.sort(candidate);
		}
		catch(Exception e){
			e.printStackTrace();
		}
		PrintWriter outputStreamName=null; 
		try {
		
			outputStreamName = new PrintWriter(new FileOutputStream(outpath));
			
			for(int i=0; i<candidate.size(); i++) {
				
				outputStreamName.println("======== Elected Candidate========");
				outputStreamName.println("Department name: " + candidate.get(i).dep.getName());
				outputStreamName.println("name: "+ candidate.get(i).getName());
				outputStreamName.println("Student_id: "+candidate.get(i).getIdnum());
				outputStreamName.println("Votes: " + candidate.get(i).getNumOfVote());
				outputStreamName.println("==================================");
			}	
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		finally {
			outputStreamName.close();
		}
		
	}
	public void runSimulation() {
		for(Department element1 : department) {
			for(Student element2 : element1.stu) {
				element2.vote(element1);
			}
		}
		for(Department element1 : department) {
			candidate.add(element1.mostvote());
		}
		saveData();
	}
}

