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
				ArrayList<Atome> H = r.getLeftSide();
				Atome C = r.getConclusion();
				Homomorphismes h = new Homomorphismes(H, this.BF);
				
				for (HashMap<String, Object> S : h.getHomomorphismes()) {
					Atome Sc = new Atome(C.getLabel(), null);
					for (Terme t : C.getListeTermes()) {
						Sc.ajoutTerme(new Terme((String) S.get(t.getLabel())));
					}
					
					boolean contain = false;
					for (Atome x : this.BF) {
						if (x.equalsA(Sc)) {
							contain = true;
							break;
						}
					}
					for (Atome x : newFaits) {
						if (x.equalsA(Sc)) {
							contain = true;
							break;
						}
					}
					
					if (!contain) {
						newFaits.add(Sc);
					}
					
				}
			}
			if (newFaits.size() == 0) {
				fin = true;
			} else {
				this.BF.addAll(newFaits);
			}
		}
		System.out.println(this.BF);
	}
	
	
	
}

