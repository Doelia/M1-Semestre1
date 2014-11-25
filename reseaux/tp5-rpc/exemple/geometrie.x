/* les structures de "base" des fonctions originales */
struct point { 
	int x; 
	int y; 
}; 

struct rectangle { 
	struct point p1; 
	struct point p2; 
}; 

typedef int booleen;

/* les structures utilisées dans les fonctions RPC pour concaténer plusieurs arguments */
struct coordonnees { 
	int x1; 
	int x2; 
	int y1; 
	int y2; 
}; 

struct param_inclus { 
	struct rectangle rect; 
	struct point p; 
};

/* définition du programme avec les 3 fonctions */
program GEOM_PROG { 
	version GEOM_VERSION_1 { 
		int SURFACE_RECTANGLE(rectangle) = 1; 
		rectangle CREER_RECTANGLE(coordonnees) = 2; 
		booleen INCLUS(param_inclus) = 3; 
	} = 1; 
} = 0x20000001;