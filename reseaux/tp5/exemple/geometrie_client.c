/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "geometrie.h"


void
geom_prog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	rectangle  surface_rectangle_1_arg;
	rectangle  *result_2;
	coordonnees  creer_rectangle_1_arg;
	booleen  *result_3;
	param_inclus  inclus_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, GEOM_PROG, GEOM_VERSION_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = surface_rectangle_1(&surface_rectangle_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = creer_rectangle_1(&creer_rectangle_1_arg, clnt);
	if (result_2 == (rectangle *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = inclus_1(&inclus_1_arg, clnt);
	if (result_3 == (booleen *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	geom_prog_1 (host);
exit (0);
}