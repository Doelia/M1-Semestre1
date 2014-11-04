package main;

import java.util.ArrayList;

public abstract class ConstraintAbstract {

	protected static int num=0; //pour donner un numéro unique à chaque contrainte
	protected String name; // nom de la contrainte
	protected ArrayList<String> varTuple; // ensemble ordonné de variables
	
	public ConstraintAbstract(ArrayList<String> var) {
		num++;
		this.name = "C"+num;
		varTuple = var; 
	}
	
	public ConstraintAbstract(ArrayList<String> var, String name) {
		num++;
		this.name = name;
		varTuple = var; 
	}
	
	public int getArity() {
		return varTuple.size();
	}
	
	public String getName() {
		return name;
	}
	
	public ArrayList<String> getVariables() {
		return varTuple;
	}
	
	
	public String toString() {
		return "\n\t"+ name + " = " + varTuple; 
	}

	public abstract boolean constraintIsRespectee(ArrayList<Object> tuple);
	
	

	
}
