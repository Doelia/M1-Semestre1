package main;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;

public class KnowledgeBase {

	ArrayList<Atome> BF;
	ArrayList<Rule> rules;

	public KnowledgeBase() {
		this.BF = new ArrayList<Atome>();
		this.rules = new ArrayList<Rule>();
	}
	
	public KnowledgeBase(String fileName) {
		this();
		
		try {
			BufferedReader bufRead = new BufferedReader(new FileReader(fileName));
			int nFaits = Integer.parseInt(bufRead.readLine());
			
			for (int i=0; i < nFaits; i++) { 
				this.BF.add(new Atome(bufRead.readLine()));
			}
			
			int nRules = Integer.parseInt(bufRead.readLine());
			for (int i=0; i < nRules; i++) {
				this.rules.add(new Rule(bufRead.readLine()));
			}
			
			bufRead.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public String toString() {
		String s = "";
		s += "BF = "+this.BF + "\n";
		s += "Règles = "+this.rules; 
		return s;
	}
	
	public void saturer() {
		boolean fin = false;
		ArrayList<Atome> newFaits;
		while (!fin) {
			newFaits = new ArrayList<Atome>();
			for (Rule r : this.rules) {
				Homomorphismes h = new Homomorphismes(r.getLeftSide(), this.BF);
				for (HashMap<String, Object> s : h.getHomomorphismes()) {
					
				}
			}
		}
	}
	
	
	
}

