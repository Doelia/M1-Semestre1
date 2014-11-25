package main;
// classe Atome

import java.util.ArrayList;

public class Atome
{
	private String label; //le predicat de l'atome
	private ArrayList<Terme> listeTermes; //la liste de termes de cet atome
		
	/**
	 * Constructeur de la classe Atome
	 * Cree un atome, avec ou sans termes
	 * @param n l'atome, soit reduit a un nom de predicat, soit de la forme
	 * predicat(liste de termes), ou les termes sont separes par des points virgules
	 */
	public Atome (String s)
	{
		
   		listeTermes = new ArrayList<Terme>();
   		if (s.charAt(s.length()-1)!=')') // c'est donc un atome sans termes
   			label = s;
   		else
   		{
   	  		int cpt = 0;
   	   	   	String nomAtome = "";//pour construire le label de l'atome
   	   	   	String nomTerme = "";//pour construire le terme courant
   			boolean constanteTerme;//le terme courant-il est une constante ou non ?
   	   		
   	   		while(s.charAt(cpt) != ')')
   	   		{
   	   			while(s.charAt(cpt) != '(')//On recupere le label de l'atome
   	   			{
   	   				nomAtome += s.charAt(cpt);
   	   				cpt++;
   	   			}
   	   			label = nomAtome;
   	   			cpt++;//Pour sauter le '('
   	   			while(s.charAt(cpt) != ')')//On va desormais s'interesser aux termes de l'atome
   	   			{
   					while(s.charAt(cpt) != ',' && s.charAt(cpt) != ')')//On recupere le label du terme
   					{
   						nomTerme += s.charAt(cpt);
   						cpt++;					
   					}
   					if(nomTerme.charAt(0) == '\'')//On teste si le terme est une constante
   					{
   						constanteTerme = true;
   						nomTerme = nomTerme.substring(1,nomTerme.length()-1);
   	                    //Si c'est une constante alors on supprime les "'"
   					}
   					else {
   						constanteTerme = false;
   					}
   					Terme t = new Terme(nomTerme,constanteTerme);//On cree un nouveau terme
   					listeTermes.add(t); //On ajoute le terme cree s'il n'existait pas deja
   					nomTerme = "";
   					if(s.charAt(cpt) == ',') cpt++; //Pour sauter le ','
   	   			}
   	 
   	   		}
   		}
	}
	
	/**
	 * Ajoute le terme 't' a la liste de termes de l'atome, sans autre verification
	 * @param t le terme a ajouter
	 */
	public void ajoutTerme(Terme t)
	{
		listeTermes.add(t);
	}
	
	public ArrayList<Terme> getListeTermes() {
		return listeTermes;
	}

	public void setListeTermes(ArrayList<Terme> listeTermes) {
		this.listeTermes = listeTermes;
	}

	public String getLabel()
	{
		return label;
	}	
	

	/**
	 * Teste l'egalite des predicats de deux atomes avec le label et l'arite
	 * de l'atome
	 * @param r l'atome e tester par rapport e l'atome courant
	 * @return vrai si les deux atomes ont meme predicat, faux sinon
	 */
	public boolean equalsP(Atome r)
	{
		return (this.label.equals(r.label) && listeTermes.size()==r.listeTermes.size());
	}

/**
	 * Teste l'egalite de deux atomes (meme label et meme liste de termes)
	 * @param r l'atome a tester par rapport a l'atome courant
	 * @return vrai si les deux atomes sont egaux, faux sinon
	 */
	public boolean equalsA(Atome r)
	{
		if (!equalsP(r)) return false;
		for (int i=0; i < listeTermes.size(); i++) 
			if (!listeTermes.get(i).equalsT(r.listeTermes.get(i))) return false;
		return true; 
	}


	
	/**
	 * Affiche l'atome selon le format logique habituel
	 */
	public void afficherAvecTermes()
	{
		System.out.print(this); // appel de toString
	}
	
	/**
	 * Retourne la chaine de caracteres de cet atome
	 * @return la chaine decrivant l'atome (suivant l'ecriture logique habituelle)
	 */
	public String toString()
	{
		String s = label + "(";
		for(int i=0;i<listeTermes.size();i++)
		{
			s+=listeTermes.get(i);
			if(i<listeTermes.size()-1) s+=",";
		}
		s+=")";
	return s;
	}
	
	public boolean containTerme(String var) {
		for (Terme t : this.getListeTermes()) {
			if (t.getLabel().equals(var))
				return true;
		}
		return false;
	}
	
	// juste pour une d�mo de la classe
	public static void main(String[] args)
	{
		Atome a = new Atome("mange('Loup'),x)");
		System.out.println(a); // appel a.toString()
		Atome b = new Atome("mange(x,y)");
		System.out.println(b); // appel b.toString()
		Atome c = new Atome("animal"); // on donne juste le nom du pr�dicat
		c.ajoutTerme(new Terme("x")); //puis on ajoute un terme
		System.out.println(c); // appel c.toString()
		System.out.println(a.equalsA(b));
	}
}

