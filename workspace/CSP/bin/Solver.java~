import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class Solver {

	public CSP problem; // l'instance de CSP
	private HashMap<String, Object> assignation; // codage d'une solution
													// partielle ou totale

	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String, Object>();
	}

	// retourne une solution s'il en existe une, null sinon
	public HashMap<String, Object> searchSolution() {
		return this.backtrack();
	}
	
	private boolean contrainteEstVerifiee(String var, Constraint c) {
		
		Object valueVar = this.assignation.get(var);
		
		int iVar = 0;
		for (int i = 0; i < c.getArity(); i++) {
			if (c.getVariables().get(i).equals(var)) {
				iVar = i;
			}
		}
		
		for (ArrayList<Object> list : c.getValTuples()) { // Pour chaque tuple, [2, tutu]
			if (valueVar.equals(list.get(iVar))) { // Si la variable traitée répond à la contrainte
				
				// On vérifie que toutes les autres variables de la contraintes sont respectées
				for (int j = 0; j < list.size(); j++) {
					String varTested = c.getVariables().get(j);
					if (this.assignation.containsKey(varTested)) { // Seulement si elle est affectée
						Object valueOfVar = this.assignation.get(varTested);
						if (valueOfVar.equals(list.get(j))) {
							return true;
						}
					}
				}
			}
		}
		
		return false;
	}
	
	private boolean isConsistant(String varAffected) {
		for (Constraint c : this.problem.getConstraintsContaining(varAffected)) { // pour toutes les contraintes concernées
			if (!this.contrainteEstVerifiee(varAffected, c)) { // Si contrainte validée
				return false;
			}
		}
		return true;
	}

	// l'algo r�cursif
	private HashMap<String, Object> backtrack() {
		
		if (this.assignation.size() == this.problem.getVarNumber()) {
			return this.assignation;
		}
		
		// On choisit une variable non affectuée
		String chosenVar = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		System.out.println("On choisit la variable "+chosenVar);
		
		// On essai de l'affecter avec toutes les variables possibles
		for (Object val : this.tri(this.problem.getDom(chosenVar))) {
			this.assignation.put(chosenVar, val);
			System.out.println("On asigne "+chosenVar+" = "+val+";");
			if (this.isConsistant(chosenVar)) { // Si contrainte validée
				System.out.println("Contrainte vérifiée!");
				HashMap<String, Object> retour = backtrack();
				if (retour != null) {
					return retour;
				}
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
		// TO DO
		return null;
	}
}
