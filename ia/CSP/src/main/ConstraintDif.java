package main;

import java.util.ArrayList;

public class ConstraintDif extends ConstraintAbstract {

	public ConstraintDif(ArrayList<String> var) {
		super(var);
	}
	
	public ConstraintDif(ArrayList<String> var, String name) {
		super(var, name);
	}

	@Override
	public boolean constraintIsRespectee(ArrayList<Object> tuples) {
		if (tuples.isEmpty()) {
			return true;
		}
		for (Object o : tuples) {
			if (o != null)
			for (Object other : tuples) {
				if (other != o && o.equals(other)) {
					return false;
				}
			}
		}
		return true;
		
	}
	
	@Override
	public String toString() {
		return super.toString()+" : DIF";
	}

}
