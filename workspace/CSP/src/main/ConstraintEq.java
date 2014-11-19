package main;

import java.util.ArrayList;

public class ConstraintEq extends ConstraintAbstract {

	public ConstraintEq(ArrayList<String> var) {
		super(var);
	}
	
	public ConstraintEq(ArrayList<String> var, String name) {
		super(var, name);
	}

	@Override
	public boolean constraintIsRespectee(ArrayList<Object> tuples) {
		if (tuples.isEmpty()) {
			return true;
		}
		Object precedent = tuples.get(0);
		for (Object o : tuples) {
			if (o != null && precedent != null && !o.equals(precedent)) {
				return false;
			}
			precedent = o;
		}
		
		return true;
		
	}
	
	@Override
	public String toString() {
		return super.toString()+" : EQ";
	}

}