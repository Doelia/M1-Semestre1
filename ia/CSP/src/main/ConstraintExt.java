package main;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;


public class ConstraintExt extends ConstraintAbstract {
	
	private Set<ArrayList<Object>> valTuples; // ensemble de tuples de la contrainte
	
	public ConstraintExt(ArrayList<String> var) {
		super(var);
		valTuples = new HashSet<ArrayList<Object>>();
	}
	
	/**
	 * Object Tuple avec les variables le même ordre que la contrainte
	 * Si Object=null, c'est que la variable n'est pas affectée
	 * @return
	 */
	public boolean constraintIsRespectee(ArrayList<Object> tuple) {
		for (ArrayList<Object> tupleAVerifier : this.valTuples) {
			
			boolean allAreOk = true;
			for (int i = 0; i < tuple.size(); i++) {
				if (tuple.get(i) != null) {
					if (!tuple.get(i).equals(tupleAVerifier.get(i))) {
						allAreOk = false;
						break;
					}
				}
			}
			
			if (allAreOk) {
				return true;
			}
		}
		
		return false;
		
	}
	
	public ConstraintExt(ArrayList<String> var, String name) {
		super(var, name);
		valTuples = new HashSet<ArrayList<Object>>();
	}

	public void addTuple(ArrayList<Object> valTuple) {
		if (valTuple.size() != varTuple.size())
			System.err.println("Le tuple " + valTuple + " n'a pas l'arite " + varTuple.size() + " de la contrainte " + name);
		else if (!valTuples.add(valTuple))
			System.err.println("Le tuple " + valTuple + " est deja present dans la contrainte "+ name);
	}
	
	public Set<ArrayList<Object>> getValTuples() {
		return valTuples;
	}
	
	public String toString() {
		return super.toString()+" : EXT : "+this.valTuples;
	}
	
}
