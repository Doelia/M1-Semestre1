package main;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

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
		this.toCSP();
	}
	
	private Set<String> getLabelsOfVar(String var, ArrayList<Atome> atomes) {
		// On cherche les labels ou "var" apparait dans A1
		Set<String> list = new HashSet<String>();
		for (Atome a : atomes) {
			if (a.containTerme(var) && !list.contains(a.getLabel())) { // var apparait dans cet atome
				list.add(a.getLabel());
			}
		}
		return list;
	}
	
	public ArrayList<Atome> getAtomesForLabel(String label, ArrayList<Atome> atomes) {
		ArrayList<Atome> list = new ArrayList<Atome>();
		for (Atome a : atomes) {
			if (label.equals(a.getLabel())) { // var apparait dans cet atome
				list.add(a);
			}
		}
		return list;
	}
	
	public CSP toCSP() {
		CSP csp = new CSP();
		
		// Recherche des variables
		for (Atome a : A1) {
			for (Terme t : a.getListeTermes()) {
				if (t.estVariable() && !csp.getVars().contains(t.getLabel())) {
					csp.addVariable(t.getLabel());
				}
			}
		}
		
		// Recherche des valeurs possibles
		ArrayList<String> valeurs = new ArrayList<String>();
		for (Atome a : A2) {
			for (Terme t : a.getListeTermes()) {
				if (t.estVariable() && !valeurs.contains(t.getLabel())) {
					valeurs.add(t.getLabel());
				}
			}
		}
		
		// Calcul des ensembles de définition
		for (String var : csp.getVars()) {
			Set<String> labelsDeA1 = getLabelsOfVar(var, A1);
			for (String valeur : valeurs) {
				boolean ok = true;
				for (String label : labelsDeA1) {
					if (!getLabelsOfVar(valeur, A2).contains(label))
						ok = false;
				}
				if (ok) {
					csp.addValue(var, valeur);
				}
			}
		}
		
		// Calcul des contraintes
		for (Atome atome : A1) { // p(x,y)
			
			// On récupère x,y
			ArrayList<String> vars = new ArrayList<String>();
			for (Terme t : atome.getListeTermes()) {
				vars.add(t.getLabel());
			}
			
			ConstraintExt c = new ConstraintExt(vars);
			
			// p(a,b), p(a,c)...
			for (Atome a : this.getAtomesForLabel(atome.getLabel(), A2)) {
				ArrayList<Object> tuple = new ArrayList<Object>();
				for (Terme t : a.getListeTermes()) {
					tuple.add(t.getLabel());
				}
				c.addTuple(tuple);
			}
			
			csp.addConstraint(c);
		}
		
		return csp;
	}
	
	
}
