package main;

import java.util.ArrayList;

public class Rule {

	ArrayList<Atome> hyp;
	Atome clc;
	
	public Rule() {
		this.hyp = new ArrayList<Atome>();
	}
	
	public Rule(String s) {
		this();
		String[] list = s.split(";");
		for (int i=0; i < list.length -1; i++) {
			this.hyp.add(new Atome(list[i]));
		}
		this.clc = new Atome(list[list.length-1]);
	}
	
	@Override
	public String toString() {
		String s = "";
		for (Atome a : hyp) {
			s += a + " ^ ";
		}
		s = s.substring(0, s.length()-2);
		s += " => " + this.clc;
		return s;
	}

	@SuppressWarnings("unchecked")
	public ArrayList<Atome> getLeftSide() {
		return (ArrayList<Atome>) this.hyp.clone();
	}
	
}
