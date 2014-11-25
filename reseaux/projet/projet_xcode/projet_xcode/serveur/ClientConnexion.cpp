#include "ClientConnexion.h"

ClientConnexion::ClientConnexion(int socket) {
	this->sock = socket;
}

void* client_listeMessages(void* c) {
	ClientConnexion* cc = (ClientConnexion*) c;
	cc->listenMessages();
    return NULL;
}

void ClientConnexion::start_listenMessages() {
	pthread_t* id = (pthread_t*) malloc(sizeof(int)*2);
	pthread_create(id, NULL, client_listeMessages, (void *) this);
	ThreadManager::getInstance()->add(id);
}


void ClientConnexion::listenMessages() {
	char* buff;
	initBuffer(&buff, 32);

	Interface::log("En attente de messages...");
	int retour;
	while ((retour = recv(this->sock, buff, MAX_SIZE_PAQUETS, 0)) > 0) {
		cout << "Message reçu : " << buff << endl;
		initBuffer(&buff, 32);
		Interface::log("En attente de messages...");
	}
    Interface::log("Fin d'attende de message.");

}

