#ifndef CLIENT_CONNEXION
#define CLIENT_CONNEXION

#include "includes-serveur.h"


void* client_listeMessages(void* c);

class ClientConnexion {

private:
	int sock;
public:
	ClientConnexion(int);
	void listenMessages();

};

#endif
