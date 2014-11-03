package main;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;

// Choix de codage 
//		Variable = String
//      Valeur = Object
//		un domaine = TreeSet<Object>
//		les couples (variable, domaine) = HashMap<String,TreeSet<Object>>
//		les contraintes = ArrayList<Constraint>

public class CSP {
	
	private HashMap<String,TreeSet<Object>> varDom; // table de hachage associant � chaque variable son domaine
	private ArrayList<Constraint> constraints; // liste des contraintes
	
	// initialise un CSP avec des structures vides
	public CSP() {
		varDom = new HashMap<String,TreeSet<Object>>();
		constraints = new ArrayList<Constraint>();
	}

	// initialise un CSP � partir d'un fichier texte
	public CSP(String fileName) {
		
		this();
		
		try {
			BufferedReader bufRead = new BufferedReader(new FileReader("example.txt"));
			int nVariables = Integer.parseInt(bufRead.readLine());
			
			for (int i=0; i < nVariables; i++) { // Pour chaque variable
				String[] parts = bufRead.readLine().split(";");
				String var = parts[0];
				this.addVariable(var);
				for (int v=1; v < parts.length; v++) {
					this.addValue(var, parts[v]);
				}
			}
			
			int nContraintes = Integer.parseInt(bufRead.readLine());
			for (int i=0; i < nContraintes; i++) { // Pour chaque contrainte
				
				// Récupuération liste des variables (x;y)
				Constraint c = new Constraint(new ArrayList<String>(Arrays.asList(bufRead.readLine().split(";"))));
				
				//System.out.println("line = "+bufRead.readLine());
				int nbrTuples = Integer.parseInt(bufRead.readLine());
				for (int nTuple=0; nTuple < nbrTuples; nTuple++) {
					System.out.println("tuple num "+nTuple);
					c.addTuple(new ArrayList<Object>(Arrays.asList(bufRead.readLine().split(";"))));
				}
				
				this.addConstraint(c);
			}
			
			bufRead.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	// ajoute une variable
	public void addVariable(String var) {
		if(varDom.get(var)==null) varDom.put(var, new TreeSet<Object>());
		else System.err.println("Variable " + var + " deja existante");
	}

	// ajoute une valeur au domaine d'une variable
	public void addValue(String var, Object val) {
		if(varDom.get(var)==null) System.err.println("Variable " + var + " non existante");
		else {
			TreeSet<Object> dom = varDom.get(var);
			if (!dom.add(val)) /*varDom.put(var, dom);
			else */System.err.println("La valeur " + val + " est deja dans le domaine de la variable " + var); 
		}
	}
	
	// ajoute une contrainte
	public void addConstraint(Constraint c) {		
		// on ne verifie pas que les valeurs des contraintes sont "compatibles" avec les domaines
		if(!varDom.keySet().containsAll(c.getVariables())) System.err.println("La contrainte "+ c.getName() + " contient des variables ("+ c.getVariables() +") non declarees dans le CSP dont les variables sont " + varDom.keySet());
		else constraints.add(c);
	}
	
	public int getVarNumber() {
		return varDom.size();
	}

	public int getDomSize(String var) {
		return varDom.values().size();
	}
	
	public int getConstraintNumber(){
		return constraints.size();
	}
	
	public Set<String> getVars() {
		return varDom.keySet();
	}

	public TreeSet<Object> getDom(String var) {
		return varDom.get(var);
	}
	
	public HashMap<String,TreeSet<Object>> getDom() {
		return varDom;
	}

	public ArrayList<Constraint> getConstraints() {
		return constraints;
	}
	
	// retourne l'ensemble des contraintes contenant la variable pass�e en param�tre
	public ArrayList<Constraint> getConstraintsContaining(String var) {
		ArrayList<Constraint> selected = new ArrayList<Constraint>();
		for(Constraint c : constraints) {
			if(c.getVariables().contains(var)) selected.add(c);
		}
		return selected;
	}
		
	public String toString() {
		return "Var et Dom : " + varDom + "\nConstraints :" + constraints;
	}
	
	
}

