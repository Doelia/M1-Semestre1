#ifndef CLIENT_CONNEXION
#define CLIENT_CONNEXION

#include "header-serveur.h"


void* client_listeMessages(void* c);

class ClientConnexion {

private:
	int sock;
public:
	ClientConnexion(int);
	void listenMessages();
	void start_listenMessages();
	int sendPaquet(string s);

};

#endif
