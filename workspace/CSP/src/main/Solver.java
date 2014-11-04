package main;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class Solver {

	public CSP problem;
	private HashMap<String, Object> assignation;
	HashSet<HashMap<String, Object>> solutions;

	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String, Object>();
		this.solutions = new HashSet<HashMap<String, Object>>();
	}

	// retourne une solution s'il en existe une, null sinon
	public HashMap<String, Object> searchSolution() {
		return this.backtrack();
	}
	
	private ArrayList<Object> createTupleFromAssignation(ArrayList<String> varOfContraint) {
		ArrayList<Object> list = new ArrayList<Object>();
		for (String var : varOfContraint) {
			list.add(this.assignation.get(var));
		}
		return list;
	}
	
	private boolean isConsistant(String varAffected) {
		for (ConstraintAbstract c : this.problem.getConstraintsContaining(varAffected)) { // pour toutes les contraintes concernées
			/*if (!this.contrainteEstVerifiee(varAffected, c)) { // Si contrainte validée
				return false;
			}*/
			
			ArrayList<Object> tuple = this.createTupleFromAssignation(c.getVariables());
			if (!c.constraintIsRespectee(tuple)) {
				return false;
			}
		}
		return true;
	}

	private HashMap<String, Object> backtrack() {
		
		if (this.assignation.size() == this.problem.getVarNumber()) {
			return this.assignation;
		}
		
		// On choisit une variable non affectuée
		String chosenVar = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		//System.out.println("On choisit la variable "+chosenVar);
		
		for (Object val : this.tri(this.problem.getDom(chosenVar))){
			this.assignation.put(chosenVar, val);
			//System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.isConsistant(chosenVar)) { // Si contrainte validée
				 HashMap<String, Object> affect = backtrack();
				 if (affect != null && affect.size() == this.problem.getVarNumber())
					 return affect;
			} else {
				//System.out.println("Pas vérifié :(");
				this.assignation.remove(chosenVar);
			}
		}
		
		return null;
	}

	private String chooseVar(Set<String> allVar, Set<String> assignedVar) {
		for (String v : allVar) {
			if (!assignedVar.contains(v)) {
				return v;
			}
		}
		return null;
	}

	private TreeSet<Object> tri(TreeSet<Object> values) {
		return values;
	}

	/**
	 * @return L'ensemble des solutions
	 */
	@SuppressWarnings("unchecked")
	public HashSet<HashMap<String, Object>> searchAllSolutions() {

		if (this.assignation.size() == this.problem.getVarNumber()) {
			this.solutions.add((HashMap<String, Object>) this.assignation.clone());
			return this.solutions;
		}
		
		// On choisit une variable non affectuée
		String chosenVar = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		//System.out.println("On choisit la variable "+chosenVar);
		
		for (Object val : this.tri(this.problem.getDom(chosenVar))) {
			this.assignation.put(chosenVar, val);
			//System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.isConsistant(chosenVar)) { // Si contrainte validée
				this.searchAllSolutions();
			}
			this.assignation.remove(chosenVar);
		}
		
		return this.solutions;
	}
	
}

