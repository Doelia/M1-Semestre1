package main;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;
import java.util.TreeSet;
import java.util.Collections;
import java.util.Comparator;

public class Solver {

	public CSP problem;
	private HashMap<String, Object> assignation;
	HashSet<HashMap<String, Object>> solutions;


	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String, Object>();
		this.solutions = new HashSet<HashMap<String, Object>>();
		this.varDom.push(p.getDom());
	}

	// retourne une solution s'il en existe une, null sinon
	public HashMap<String, Object> searchSolution() {
		return this.backtrack();
		//return this.fowardChecking();
	}

	private boolean isOk(String var) {
		return this.isConsistant(var);
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

	@SuppressWarnings("unused")
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



	private boolean propager(String var) {
		@SuppressWarnings("unchecked")
		HashMap<String,TreeSet<Object>> oldDom = (HashMap<String, TreeSet<Object>>) this.varDom.firstElement().clone();
		for (ConstraintAbstract c : this.problem.getConstraintsContaining(var)) {
			for (String v : c.getVariables()) {
				oldDom.get(v).remove(var);
				if (oldDom.get(v).isEmpty()) {
					return false;
				}
			}
		}
		this.varDom.push(oldDom);
		return this.isOk(var);
	}

	private Stack<HashMap<String,TreeSet<Object>>> varDom = new Stack<HashMap<String,TreeSet<Object>>>();

	public HashMap<String, Object> fowardChecking() {

		if (this.assignation.size() == this.problem.getVarNumber()) {
			return this.assignation;
		}

		// On choisit une variable non affectuée
		String chosenVar = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		//System.out.println("On choisit la variable "+chosenVar);

		for (Object val : this.tri(this.problem.getDom(chosenVar))){
			this.assignation.put(chosenVar, val);
			//System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.propager(chosenVar)) { // Si contrainte validée
				HashMap<String, Object> affect = fowardChecking();
				if (affect != null && affect.size() == this.problem.getVarNumber())
					return affect;
			} else {
				//System.out.println("Pas vérifié :(");
				this.assignation.remove(chosenVar);
				this.varDom.pop();
			}
		}

		return null;
	}

	private ArrayList<String> getVariablesOrdered(Set<String> variables) {
		ArrayList<String> list = new ArrayList<String>();
		list.addAll(variables);
		final CSP pb = this.problem;
		Collections.sort(list, new Comparator<String>() {
			@Override
			public int compare(String  v1, String  v2) {
				return pb.getConstraintsContaining(v1).size() - pb.getConstraintsContaining(v2).size();
			}
		});
		return list;
	}

	private String chooseVar(Set<String> allVar, Set<String> assignedVar) {
		for (String v : this.getVariablesOrdered(allVar)) {
			if (!assignedVar.contains(v)) {
				return v;
			}
		}
		return null;
	}

	private ArrayList<Object> tri(TreeSet<Object> values) {
		ArrayList<Object> list = new ArrayList<Object>();
		list.addAll(values);
		return list;
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
