package main;

import java.util.HashMap;

                                                                                                                    

// exemple de main pour le test de l'algorithme de backtrack


public class TP {

	public static void main(String args[]) {
		String fileName = "hom.txt";
		
		try {    
			System.out.println("Chargement du fichier : "+new java.io.File( "." ).getCanonicalPath()+"/"+fileName);
			CSP myProblem = new CSP(fileName);
			System.out.println("Recherche d'une solution au probleme :\n" + myProblem);
			
			Solver mySolver = new Solver(myProblem);
			HashMap<String,Object> mySolution = mySolver.searchSolution();
			if (mySolution == null) System.out.println("Pas de solution !");
			else System.out.println("Une solution est " + mySolution);
			
			Solver mySolverMultiple = new Solver(myProblem);
			System.out.println("Ensemble de solutions : "+mySolverMultiple.searchAllSolutions());
			
		} catch(Exception e) {
			System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		
		
		Homomorphismes h = new Homomorphismes("p(x,y);p(y,z);p(x,u);p(z,z);r(x);r(u)", "p(a,b);p(a,c);p(b,c);p(b,d);p(b,e);p(d,e);p(e,e);r(a);r(b);r(c)");
		Solver mySolverMultiple = new Solver(h.toCSP());
		System.out.println("Ensemble de solutions : "+mySolverMultiple.searchAllSolutions());
		
	}
}