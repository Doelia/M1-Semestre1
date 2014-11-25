package main;

import java.util.ArrayList;

public class Homomorphismes {

	private ArrayList<Atome> A1;
	private ArrayList<Atome> A2;
	private ArrayList<Homomorphismes> homos;
	
	private static ArrayList<Atome> strToArrayList(String s) {
		ArrayList<Atome> list = new ArrayList<Atome>();
		for (String i : s.split(";")) {
			list.add(new Atome(i));
		}
		return list;
	}
	
	public Homomorphismes(ArrayList<Atome> A1, ArrayList<Atome> A2) {
		this.A1 = A1;
		this.A2 = A2;
	}
	
	public Homomorphismes(String A1, String A2) {
		this(strToArrayList(A1), strToArrayList(A2));
	}
	
	private void toCSP() {
		CSP csp = new CSP();
		for (Atome a : A1) {
			for (Terme t : a.getListeTermes()) {
				if (t.estVariable() && !csp.getVars().contains(t.getLabel())) {
					csp.addVariable(t.getLabel());
				}
			}
		}
	}
	
	
}
