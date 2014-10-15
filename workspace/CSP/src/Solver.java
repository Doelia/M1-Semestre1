import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class Solver {

	public CSP problem;
	private HashMap<String, Object> assignation;

	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String, Object>();
	}

	// retourne une solution s'il en existe une, null sinon
	public HashMap<String, Object> searchSolution() {
		return this.backtrack();
	}
	
	private boolean toutesLesVariableDeLaContrainteSontAffectes(Constraint c) {
		for (String var : c.getVariables()) {
			if (!this.assignation.containsKey(var)) {
				return false;
			}
		}
		return true;
	}
	
	
	
	private boolean contrainteEstVerifiee(Constraint c) {
		
		if (!toutesLesVariableDeLaContrainteSontAffectes(c)) {
			return true;
		}
		
		for (ArrayList<Object> list : c.getValTuples()) { // Pour chaque tuple, [2, tutu]
			for (int j = 0; j < list.size(); j++) { // pour chaque valeurs du tuple
				String varTested = c.getVariables().get(j); // variable concernée
				Object valueOfVar = this.assignation.get(varTested); // valeur actuelle
				if (valueOfVar.equals(list.get(j))) { // si correspond, OK
					return true;
				}
			}
		}
		
		return false;
		
	}
	
	/**
	 * 
	 * @param var la variable modifiée à tester
	 * @param c une contrainte qui conteint la variable var
	 * @return
	 */
	private boolean contrainteEstVerifiee(String var, Constraint c) {
		
		Object valueVar = this.assignation.get(var);
		int iVar = c.getVariables().indexOf(var);
		
		for (ArrayList<Object> list : c.getValTuples()) { // Pour chaque tuple, [2, tutu]
			if (valueVar.equals(list.get(iVar))) { // Si la variable traitée répond à la contrainte
				
				// On vérifie que toutes les autres variables de la contraintes sont respectées
				boolean allAreOk = true;
				for (int j = 0; j < list.size(); j++) {
					String varTested = c.getVariables().get(j);
					if (this.assignation.containsKey(varTested)) { // Seulement si elle est affectée
						Object valueOfVar = this.assignation.get(varTested);
						if (!valueOfVar.equals(list.get(j))) {
							allAreOk = false;
						}
					}
				}
				if (allAreOk) {
					System.out.println("tuple "+list+" OK");
					return true;
				}
				
			}
		}
		
		return false;
	}
	
	private boolean isConsistant(String varAffected) {
		for (Constraint c : this.problem.getConstraintsContaining(varAffected)) { // pour toutes les contraintes concernées
			System.out.println("Contrainte "+c);
			if (!this.contrainteEstVerifiee(varAffected, c)) { // Si contrainte validée
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
		System.out.println("On choisit la variable "+chosenVar);
		
		for (Object val : this.tri(this.problem.getDom(chosenVar))) {
			this.assignation.put(chosenVar, val);
			System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.isConsistant(chosenVar)) { // Si contrainte validée
				 HashMap<String, Object> affect = backtrack();
				 if (affect.size() == this.problem.getVarNumber())
					 return affect;
			} else {
				System.out.println("Pas vérifié :(");
				this.assignation.remove(chosenVar);
			}
		}
		
		return null;
	}

	// choix d'une variable
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

	// retourne l'ensemble des solutions
	public HashSet<HashMap<String, Object>> searchAllSolutions() {

		if (this.assignation.size() == this.problem.getVarNumber()) {
			HashSet<HashMap<String, Object>> nouv = new HashSet<HashMap<String, Object>>();
			nouv.add(this.assignation.clone());
			nouv.addAll( this.searchAllSolutions());
		}
		
		// On choisit une variable non affectuée
		String chosenVar = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		System.out.println("On choisit la variable "+chosenVar);
		
		for (Object val : this.tri(this.problem.getDom(chosenVar))) {
			this.assignation.put(chosenVar, val);
			System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.isConsistant(chosenVar)) { // Si contrainte validée
				 HashMap<String, Object> affect = backtrack();
				 if (affect.size() == this.problem.getVarNumber())
					 return affect;
			} else {
				System.out.println("Pas vérifié :(");
				this.assignation.remove(chosenVar);
			}
		}
		
		return null;
	}
	
}
